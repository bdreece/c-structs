/*! \file cbuf.c
 *  \brief The circular buffer implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include "structs/cbuf.h"

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"

int cbuf_init(cbuf_t *cbuf, const size_t element_size, const size_t capacity) {
  if (!cbuf) return ERR_NULL;

  if (capacity < 1 || element_size < 1) return ERR_INVALID_ARGUMENT;

  cbuf->capacity = capacity;
  cbuf->element_size = element_size;
  cbuf->size = 0;
  cbuf->head = 0;
  cbuf->tail = 0;
  cbuf->elements = malloc(capacity * element_size);
  if (!cbuf->elements) return ERR_FAILURE;

  return ERR_NONE;
}

int cbuf_deinit(cbuf_t *cbuf) {
  if (!cbuf) return ERR_NULL;

  if (cbuf->elements != NULL) free(cbuf->elements);

  cbuf->elements = NULL;
  cbuf->element_size = 0;
  cbuf->capacity = 0;
  cbuf->size = 0;
  cbuf->head = 0;
  cbuf->tail = 0;
  return ERR_NONE;
}

int cbuf_read(cbuf_t *cbuf, void *element) {
  if (!cbuf || !cbuf->elements) return ERR_NULL;

  if (cbuf->capacity == 0 || cbuf->size == 0) return ERR_EMPTY;

  if (cbuf->capacity == 1) {
    memcpy(element, cbuf->elements, cbuf->element_size);
    return ERR_NONE;
  } else {
    memcpy(element, cbuf->elements + cbuf->head * cbuf->element_size,
           cbuf->element_size);
    cbuf->head = (cbuf->head + 1) % cbuf->capacity;
    cbuf->size--;
    return ERR_NONE;
  }
}

int cbuf_write(cbuf_t *cbuf, const void *element) {
  if (!cbuf || !cbuf->elements) return ERR_NULL;

  if (cbuf->capacity == 0) return ERR_EMPTY;

  if (cbuf->capacity == 1) {
    memcpy(cbuf->elements, element, cbuf->element_size);
    return ERR_NONE;
  } else {
    memcpy(cbuf->elements + cbuf->tail * cbuf->element_size, element,
           cbuf->element_size);
    cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
    cbuf->size++;
    return ERR_NONE;
  }
}

int cbuf_get(const cbuf_t *cbuf, void *element) {
  if (!cbuf || !cbuf->elements) return ERR_NULL;

  if (cbuf->size == 0) return ERR_EMPTY;

  if (cbuf->capacity == 1) {
    if (memcpy(element, cbuf->elements, cbuf->element_size) == NULL)
      return ERR_FAILURE;
    else
      return ERR_NONE;
  } else {
    if (memcpy(element, cbuf->elements + cbuf->tail * cbuf->element_size,
               cbuf->element_size) == NULL)
      return ERR_FAILURE;
    else
      return ERR_NONE;
  }
}

int cbuf_getp(const cbuf_t *cbuf, void **element) {
  if (!cbuf || !cbuf->elements) return ERR_NULL;

  if (cbuf->size == 0) return ERR_EMPTY;

  if (cbuf->capacity == 1) {
    *element = cbuf->elements;
    return ERR_NONE;
  } else {
    *element = cbuf->elements + cbuf->tail * cbuf->element_size;
    return ERR_NONE;
  }
}

int cbuf_clear(cbuf_t *cbuf) {
  if (!cbuf || !cbuf->elements) return ERR_NULL;

  if (memset(cbuf->elements, 0, cbuf->element_size * cbuf->capacity) ==
      (void *)NULL)
    return ERR_FAILURE;
  cbuf->head = 0;
  cbuf->tail = 0;
  cbuf->size = 0;
  return ERR_NONE;
}

inline long cbuf_size(const cbuf_t *cbuf) {
  return (!cbuf || !cbuf->elements) ? ERR_NULL : cbuf->size;
}

inline long cbuf_capacity(const cbuf_t *cbuf) {
  return (!cbuf || !cbuf->elements) ? ERR_NULL : cbuf->capacity;
}
