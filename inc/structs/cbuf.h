/*! \file       cbuf.h
 *  \brief      The circular buffer header file.
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       12/28/2021
 */

#ifndef CBUF_H
#define CBUF_H

#ifndef STRUCTS_DEF
#define STRUCTS_DEF static inline
#endif  // STRUCTS_DEF

#include <stddef.h>

//! \brief The circular buffer structure
typedef struct cbuf {
  long head;  //!< The head index of the buffer (read end)
  long tail;  //!< The tail index of the buffer (write end)
  long size;
  size_t capacity;      //!< The size of the buffer
  size_t element_size;  //!< The size of the element
  void *elements;       //!< The buffer elements
} cbuf_t;

/*! \brief The circular buffer constructor function
 *  \details This function initializes a circular buffer.
 *  \param[in] cbuf The circular buffer to be initialized.
 *  \param[in] element_size The size of the element.
 *  \param[in] size The size of the buffer.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int cbuf_init(cbuf_t *cbuf, const size_t element_size,
                          const size_t capacity);

/*! \brief The circular buffer destructor function
 *  \details This function releases the circular buffer.
 *  \param[in] cbuf The circular buffer to be released.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int cbuf_deinit(cbuf_t *cbuf);

/*! \brief The circular buffer writer function
 *  \details This function writes the element to the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \param[in] element The element to be written.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int cbuf_read(cbuf_t *cbuf, void *element);

/*! \brief The circular buffer reader function
 *  \details This function reads the element from the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \param[out] element The element to be read.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int cbuf_write(cbuf_t *cbuf, const void *element);

/*! \brief The circular buffer get function
 *  \details This function retrieves an element from the circular buffer
 *           without removing it.
 *  \param[in] cbuf The circular buffer.
 *  \param[out] element The element to be read.
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int cbuf_get(const cbuf_t *cbuf, void *element);

/*! \brief The circular buffer get pointer function
 *  \details This function retrieves a pointer to an element from the
 *           circular buffer without removing it.
 *  \param[in] cbuf The circular buffer
 *  \param[out] element The element to be read
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int cbuf_getp(const cbuf_t *cbuf, void **element);

/*! \brief The circular buffer clear function
 *  \details This function zeroes all elements in the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int cbuf_clear(cbuf_t *cbuf);

STRUCTS_DEF long cbuf_size(const cbuf_t *cbuf);

STRUCTS_DEF long cbuf_capacity(const cbuf_t *cbuf);

#ifdef STRUCTS_CBUF_IMPL

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

long cbuf_size(const cbuf_t *cbuf) {
  return (!cbuf || !cbuf->elements) ? ERR_NULL : cbuf->size;
}

long cbuf_capacity(const cbuf_t *cbuf) {
  return (!cbuf || !cbuf->elements) ? ERR_NULL : cbuf->capacity;
}

#endif  // STRUCTS_CBUF_IMPL

#endif  // CBUF_H
