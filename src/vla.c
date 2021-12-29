/*! \file vla.c
 *  \brief Variable length array implementation.
 *  \author Brian Reece
 *  \version 0.3
 *  \date 12/28/2021
 */

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"
#include "structs/vla.h"

/*! \brief Resize a variable length array.
 *  \details The new size is calculated by multiplying the element size by the
 * new capacity \param[in] vla Pointer to the variable length array. \param[in]
 * capacity The new capacity of the array. \returns Zero on success, non-zero on
 * failure.
 */
static int vla_resize(vla_t *vla, unsigned long capacity) {
  if (!vla)
    return ERR_NULL;

  void *p = realloc(vla->elements, vla->element_size * capacity);

  if (p == NULL)
    return ERR_FAILURE;

  vla->elements = p;
  vla->capacity = capacity;

  return ERR_NONE;
}

int vla_init(vla_t *vla, const size_t element_size,
             const long initial_capacity) {
  if (!vla)
    return ERR_NULL;

  if (element_size <= 0 || initial_capacity <= 0)
    return ERR_INVALID_ARGUMENT;

  vla->element_size = element_size;
  vla->size = 0;
  vla->capacity = initial_capacity;

  vla->elements = malloc(element_size * initial_capacity);

  if (vla->elements == NULL)
    return ERR_FAILURE;

  ASSERT(memset(vla->elements, 0, element_size * initial_capacity) != NULL);

  return ERR_NONE;
}

int vla_deinit(vla_t *vla) {
  if (!vla)
    return ERR_NULL;

  if (vla->elements != NULL)
    free(vla->elements);

  vla->elements = NULL;
  vla->element_size = 0;
  vla->size = 0;
  vla->capacity = 0;

  return ERR_NONE;
}

int vla_push(vla_t *vla, const void *restrict element) {
  if (!vla)
    return ERR_NULL;

  if (vla->size >= vla->capacity) {
    if (vla_resize(vla, vla->capacity * 2) == ERR_FAILURE)
      return ERR_FAILURE;
  }

  memmove(vla->elements + vla->element_size, vla->elements,
          vla->element_size * vla->size);
  memcpy(vla->elements, element, vla->element_size);

  vla->size++;

  return ERR_NONE;
}

int vla_pop(vla_t *vla, void *restrict element) {
  int i;
  if (!vla)
    return ERR_NULL;

  if (vla->size == 0)
    return ERR_EMPTY;

  // Get first element
  memcpy(element, vla->elements, vla->element_size);

  // Shift memory block "left" by size of one element
  memmove(vla->elements, vla->elements + vla->element_size,
          vla->element_size * vla->size);

  vla->size--;

  return ERR_NONE;
}

int vla_enq(vla_t *vla, const void *restrict element) {
  if (!vla)
    return ERR_NULL;

  // Resize if necessary
  if (vla->size == vla->capacity) {
    if (vla_resize(vla, vla->capacity * 2) == ERR_FAILURE)
      return ERR_FAILURE;
  }

  // Append element to list
  memcpy(vla->elements + (vla->size * vla->element_size), element,
         vla->element_size);
  vla->size++;

  return ERR_NONE;
}

int vla_get(const vla_t *vla, const long index, void *restrict element) {
  if (!vla)
    return ERR_NULL;

  if (index >= vla->size)
    return ERR_INDEX_OUT_OF_BOUNDS;

  if ((char *)(vla->elements + (index * vla->element_size)) != NULL)
    memcpy(element, vla->elements + (index * vla->element_size),
           vla->element_size);

  return ERR_NONE;
}

int vla_getp(const vla_t *vla, const long index, void **restrict element) {
  if (!vla)
    return ERR_NULL;

  if (index >= vla->size)
    return ERR_INDEX_OUT_OF_BOUNDS;

  *element = vla->elements + (index * vla->element_size);
  return ERR_NONE;
}

int vla_set(vla_t *vla, const long index, const void *restrict element) {
  if (!vla)

    if (index >= vla->size)
      return ERR_INDEX_OUT_OF_BOUNDS;

  memcpy(vla->elements + (index * vla->element_size), element,
         vla->element_size);

  return ERR_NONE;
}

int vla_ins(vla_t *vla, const long index, const void *restrict element) {
  if (!vla)
    return ERR_NULL;

  if (index > vla->size)
    return ERR_INDEX_OUT_OF_BOUNDS;

  if (vla->size == vla->capacity) {
    if (vla_resize(vla, vla->capacity * 2) == ERR_FAILURE)
      return ERR_FAILURE;
  }

  // Make an empty slot at index by shifting index + 1 block right
  memmove(vla->elements + (index * vla->element_size) + vla->element_size,
          vla->elements + (index * vla->element_size),
          (vla->size - index) * vla->element_size);

  memcpy(vla->elements + (index * vla->element_size), element,
         vla->element_size);
  vla->size++;

  return ERR_NONE;
}

int vla_del(vla_t *vla, const long index) {
  if (!vla)
    return ERR_NULL;

  if (index >= vla->size)
    return ERR_INDEX_OUT_OF_BOUNDS;

  // Move block at index + 1 to index
  if (memmove(vla->elements + (index * vla->element_size),
              vla->elements + ((index + 1) * vla->element_size),
              (vla->size - index - 1) * vla->element_size) == NULL)
    return ERR_FAILURE;

  vla->size--;

  return ERR_NONE;
}

int vla_clear(vla_t *vla) {
  if (!vla)
    return ERR_NULL;

  memset(vla->elements, 0, vla->element_size * vla->capacity);

  vla->size = 0;
  return ERR_NONE;
}

int vla_ext(vla_t *dest, const vla_t *restrict src) {
  if (!dest || !src)
    return ERR_NULL;

  if (dest->element_size != src->element_size)
    return ERR_INVALID_ARGUMENT;

  size_t new_size = dest->element_size * (dest->size + src->size);
  dest->elements = realloc(dest->elements, new_size);

  // Copy src into dest
  if (memcpy(dest->elements + (dest->element_size * dest->size), src->elements,
             src->element_size * src->size) == NULL)
    return ERR_FAILURE;

  dest->size += src->size;
  dest->capacity = dest->size;

  return ERR_NONE;
}

inline long vla_size(const vla_t *vla) { return (!vla) ? ERR_NULL : vla->size; }

inline long vla_capacity(const vla_t *vla) {
  return (!vla) ? ERR_NONE : vla->capacity;
}
