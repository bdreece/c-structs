/*! \file       cbuf.h
 *  \brief      The circular buffer header file.
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       12/28/2021
 */

#ifndef CBUF_H
#define CBUF_H

#ifdef __cplusplus
extern "C" {
#endif

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
int cbuf_init(cbuf_t *cbuf, const size_t element_size, const size_t capacity);

/*! \brief The circular buffer destructor function
 *  \details This function releases the circular buffer.
 *  \param[in] cbuf The circular buffer to be released.
 *  \return Zero if successful, non-zero otherwise.
 */
int cbuf_deinit(cbuf_t *cbuf);

/*! \brief The circular buffer writer function
 *  \details This function writes the element to the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \param[in] element The element to be written.
 *  \return Zero if successful, non-zero otherwise.
 */
int cbuf_read(cbuf_t *cbuf, void *element);

/*! \brief The circular buffer reader function
 *  \details This function reads the element from the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \param[out] element The element to be read.
 *  \return Zero if successful, non-zero otherwise.
 */
int cbuf_write(cbuf_t *cbuf, const void *element);

/*! \brief The circular buffer get function
 *  \details This function retrieves an element from the circular buffer
 *           without removing it.
 *  \param[in] cbuf The circular buffer.
 *  \param[out] element The element to be read.
 *  \return Zero if successful, non-zero otherwise
 */
int cbuf_get(const cbuf_t *cbuf, void *element);

/*! \brief The circular buffer get pointer function
 *  \details This function retrieves a pointer to an element from the
 *           circular buffer without removing it.
 *  \param[in] cbuf The circular buffer
 *  \param[out] element The element to be read
 *  \return Zero if successful, non-zero otherwise.
 */
int cbuf_getp(const cbuf_t *cbuf, void **element);

/*! \brief The circular buffer clear function
 *  \details This function zeroes all elements in the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \return Zero if successful, non-zero otherwise.
 */
int cbuf_clear(cbuf_t *cbuf);

// TODO: cbuf_size
extern long cbuf_size(const cbuf_t *cbuf);

// TODO: cbuf_capacity
extern long cbuf_capacity(const cbuf_t *cbuf);

#ifdef __cplusplus
}
#endif

#endif  // CBUF_H
