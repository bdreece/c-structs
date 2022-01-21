/*! \file       vla.h
 *  \brief      VLA definition and manipulation functions.
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 */

#ifndef STRUCTS_VLA_H
#define STRUCTS_VLA_H

#ifndef STRUCTS_DEF
#define STRUCTS_DEF static inline
#endif  // STRUCTS_DEF

#ifdef STRUCTS_NO_STRING_H
#include "structs/util.h"
#endif

// TODO: VLA printf macros

#include <stddef.h>

//! \brief VLA struct definition.
typedef struct vla {
  size_t size;          //!< VLA size.
  size_t capacity;      //!< VLA capacity.
  size_t element_size;  //!< VLA element size.
  void *elements;       //!< VLA elements.
} vla_t;

/*! \brief VLA construction function.
 *  \details This function creates a VLA of a given size and element size.
 *  \param[in] vla VLA to create.
 *  \param[in] size VLA size.
 *  \param[in] element_size VLA element size.
 *  \param[in] initial_capacity VLA initial capacity.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_init(vla_t *const vla, const size_t element_size,
                         const size_t initial_capacity);

/*! \brief VLA destruction function.
 *  \details This function destroys a VLA.
 *  \param[in] vla VLA to destroy.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_deinit(vla_t *const vla);

/*! \brief VLA push function.
 *  \details This function pushes an element onto the VLA.
 *           Time complexity on the order of O(n).
 *  \param[in] vla VLA to push to.
 *  \param[in] element Element to push.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_push(vla_t *const vla, const void *restrict element);

/*! \brief VLA pop function.
 *  \details This function pops an element from the VLA.
 *           Time complexity on the order of O(n).
 *  \param[in] vla VLA to pop from.
 *  \param[out] element Element to pop.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_pop(vla_t *const vla, void *restrict element);

/*! \func vla_enq
 *  \brief VLA enqueue function.
 *  \details This function enqueues an element onto the VLA.
 *           Time complexity on the order of O(1).
 *  \param[in] vla VLA to resize.
 *  \param[in] size New VLA size.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_enq(vla_t *const vla, const void *restrict element);

/*! \brief VLA get function.
 *  \details This function gets an element from the VLA.
 *  \param[in] vla VLA to get from.
 *  \param[in] index Index of element to get.
 *  \param[out] element Element to get.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_get(const vla_t *const vla, const size_t index,
                        void *restrict element);

/*! \brief VLA get pointer function
 *  \details This function gets the pointer to an element in the VLA.
 *  \param[in] vla VLA to get from
 *  \param[in] index Index of element to get.
 *  \param[out] element Element to get
 *  \return Zero on success, non-zero on failure
 */
STRUCTS_DEF int vla_getp(const vla_t *const vla, const size_t index,
                         void **const element);

/*! \brief VLA set function.
 *  \details This function sets an element in the VLA.
 *  \param[in] vla VLA to set in.
 *  \param[in] index Index of element to set.
 *  \param[in] element Element to set.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_set(vla_t *const vla, const size_t index,
                        const void *restrict element);

/*! \brief VLA insert function.
 *  \details This function inserts an element into the VLA.
 *           Time complexity on the order of O(n).
 *  \param[in] vla VLA to insert into.
 *  \param[in] index Index to insert at.
 *  \param[in] element Element to insert.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_ins(vla_t *const vla, const size_t index,
                        const void *restrict element);

/*! \brief VLA delete function.
 *  \details This function deletes an element from the VLA. Time complexity on
 * the order of O(n).
 * \param[in] vla VLA to delete from.
 * \param[in] index Index
 * of element to delete. \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_del(vla_t *const vla, const size_t index);

/*! \brief VLA clear function.
 *  \details This function clears the VLA.
 *  \param[in] vla VLA to clear.
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_clear(vla_t *const vla);

/*! \brief VLA extend function
 *  \details This function appends the element of VLA src to dest.
 *  \param[out] dest The destination VLA
 *  \param[in] src The source VLA
 *  \return Zero on success, non-zero on failure.
 */
STRUCTS_DEF int vla_ext(vla_t *const dest, const vla_t *restrict src);

/*! \brief VLA size function.
 *  \details This function returns the VLA size.
 *  \param[in] vla VLA to get size of.
 *  \return VLA size.
 */
STRUCTS_DEF size_t vla_size(const vla_t *const vla);

/*! \brief VLA capacity function.
 *  \details This function returns the VLA capacity.
 *  \param[in] vla VLA to get capacity of.
 *  \return VLA capacity.
 */
STRUCTS_DEF size_t vla_capacity(const vla_t *const vla);

#ifdef STRUCTS_VLA_IMPL

#include <stdlib.h>

#ifndef STRUCTS_NO_STRING_H

#ifndef STRUCTS_STRING_H
#define STRUCTS_STRING_H

#include <string.h>
#define STRUCTS_MEMCPY(d, s, n) memcpy((d), (s), (n))
#define STRUCTS_MEMMOVE(d, s, n) memmove((d), (s), (n))
#define STRUCTS_MEMSET(d, c, n) memset((d), (c), (n))

#endif  // STRUCTS_STRING_H

#endif  // STRUCTS_NO_STRING_H

#include "structs/error.h"

/*! \brief Resize a variable length array.
 *  \details The new size is calculated by multiplying the element size by the
 * new capacity \param[in] vla Pointer to the variable length array. \param[in]
 * capacity The new capacity of the array. \returns Zero on success, non-zero on
 * failure.
 */
static int vla_resize(vla_t *const vla, const size_t capacity) {
  if (!vla) return ERR_NULL;

  void *p = realloc(vla->elements, capacity * vla->element_size);

  if (p == NULL) return ERR_FAILURE;

  vla->elements = p;
  vla->capacity = capacity;

  return ERR_NONE;
}

int vla_init(vla_t *const vla, const size_t element_size,
             const size_t initial_capacity) {
  if (!vla) return ERR_NULL;

  if (element_size <= 0 || initial_capacity <= 0) return ERR_INVALID_ARGUMENT;

  vla->element_size = element_size;
  vla->size = 0;
  vla->capacity = initial_capacity;

  vla->elements = calloc(initial_capacity, element_size);

  if (vla->elements == NULL) return ERR_FAILURE;

  ASSERT(STRUCTS_MEMSET(vla->elements, 0, element_size * initial_capacity) !=
         NULL);

  return ERR_NONE;
}

int vla_deinit(vla_t *const vla) {
  if (!vla) return ERR_NULL;

  if (vla->elements != NULL) free(vla->elements);

  vla->elements = NULL;
  vla->element_size = 0;
  vla->size = 0;
  vla->capacity = 0;

  return ERR_NONE;
}

int vla_push(vla_t *const vla, const void *element) {
  if (!vla) return ERR_NULL;

  if (vla->size >= vla->capacity) {
    if (vla_resize(vla, vla->capacity * 2) == ERR_FAILURE) return ERR_FAILURE;
  }

  STRUCTS_MEMMOVE(vla->elements + vla->element_size, vla->elements,
                  vla->element_size * vla->size);
  STRUCTS_MEMCPY(vla->elements, element, vla->element_size);

  vla->size++;

  return ERR_NONE;
}

int vla_pop(vla_t *const vla, void *element) {
  int i;
  if (!vla) return ERR_NULL;

  if (vla->size == 0) return ERR_EMPTY;

  // Get first element
  STRUCTS_MEMCPY(element, vla->elements, vla->element_size);

  // Shift memory block "left" by size of one element
  STRUCTS_MEMMOVE(vla->elements, vla->elements + vla->element_size,
                  vla->element_size * vla->size);

  vla->size--;

  return ERR_NONE;
}

int vla_enq(vla_t *const vla, const void *element) {
  if (!vla) return ERR_NULL;

  // Resize if necessary
  if (vla->size == vla->capacity) {
    if (vla_resize(vla, vla->capacity * 2) == ERR_FAILURE) return ERR_FAILURE;
  }

  // Append element to list
  STRUCTS_MEMCPY(vla->elements + (vla->size * vla->element_size), element,
                 vla->element_size);
  vla->size++;

  return ERR_NONE;
}

int vla_get(const vla_t *const vla, const size_t index, void *element) {
  if (!vla) return ERR_NULL;

  if (index >= vla->size) return ERR_INDEX_OUT_OF_BOUNDS;

  if ((char *)(vla->elements + (index * vla->element_size)) != NULL)
    STRUCTS_MEMCPY(element, vla->elements + (index * vla->element_size),
                   vla->element_size);

  return ERR_NONE;
}

int vla_getp(const vla_t *const vla, const size_t index, void **const element) {
  if (!vla) return ERR_NULL;

  if (index >= vla->size) return ERR_INDEX_OUT_OF_BOUNDS;

  *element = vla->elements + (index * vla->element_size);
  return ERR_NONE;
}

int vla_set(vla_t *const vla, const size_t index, const void *element) {
  if (!vla)

    if (index >= vla->size) return ERR_INDEX_OUT_OF_BOUNDS;

  STRUCTS_MEMCPY(vla->elements + (index * vla->element_size), element,
                 vla->element_size);

  return ERR_NONE;
}

int vla_ins(vla_t *const vla, const size_t index, const void *element) {
  if (!vla) return ERR_NULL;

  if (index > vla->size) return ERR_INDEX_OUT_OF_BOUNDS;

  if (vla->size == vla->capacity) {
    if (vla_resize(vla, vla->capacity * 2) == ERR_FAILURE) return ERR_FAILURE;
  }

  // Make an empty slot at index by shifting index + 1 block right
  STRUCTS_MEMMOVE(
      vla->elements + (index * vla->element_size) + vla->element_size,
      vla->elements + (index * vla->element_size),
      (vla->size - index) * vla->element_size);

  STRUCTS_MEMCPY(vla->elements + (index * vla->element_size), element,
                 vla->element_size);
  vla->size++;

  return ERR_NONE;
}

int vla_del(vla_t *const vla, const size_t index) {
  if (!vla) return ERR_NULL;

  if (index >= vla->size) return ERR_INDEX_OUT_OF_BOUNDS;

  // Move block at index + 1 to index
  STRUCTS_MEMMOVE(vla->elements + (index * vla->element_size),
                  vla->elements + ((index + 1) * vla->element_size),
                  (vla->size - index - 1) * vla->element_size);

  vla->size--;

  return ERR_NONE;
}

int vla_clear(vla_t *const vla) {
  if (!vla) return ERR_NULL;

  STRUCTS_MEMSET(vla->elements, 0, vla->element_size * vla->capacity);

  vla->size = 0;
  return ERR_NONE;
}

int vla_ext(vla_t *const dest, const vla_t *restrict src) {
  if (!dest || !src) return ERR_NULL;

  if (dest->element_size != src->element_size) return ERR_INVALID_ARGUMENT;

  int ret;
  size_t i;
  void *p;
  for (i = 0; i < src->size; i++) {
    if ((ret = vla_getp(src, i, (void **)&p)) < 0) return ret;
    if ((ret = vla_enq(dest, p)) < 0) return ret;
  }

  return ERR_NONE;
}

size_t vla_size(const vla_t *const vla) {
  return (!vla) ? ERR_NULL : vla->size;
}

size_t vla_capacity(const vla_t *const vla) {
  return (!vla) ? ERR_NONE : vla->capacity;
}

#endif  // STRUCTS_VLA_IMPL

#endif  // STRUCTS_VLA_H
