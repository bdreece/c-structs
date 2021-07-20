/*! \file cbuf.h
 *  \brief The circular buffer header file.
 *  \author Brian Reece
 *  \version 0.1.0
 */

#ifndef CBUF_H
#define CBUF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

//! \brief The circular buffer error codes
#define CBUF_SUCCESS 0
#define CBUF_FAILURE -1
#define CBUF_EMPTY -2

/*! \brief The circular buffer structure
 *  \details This structure is used to hold the circular buffer.
 */
typedef struct cbuf
{
    unsigned long head; //!< The head index of the buffer (read end)
    unsigned long tail; //!< The tail index of the buffer (write end)
    unsigned long size; //!< The size of the buffer
    size_t element_size; //!< The size of the element
    void *elements; //!< The buffer elements
} cbuf_t;

/*! \brief The circular buffer constructor function
 *  \details This function initializes a circular buffer.
 *  \param[in] cbuf The circular buffer to be initialized.
 *  \param[in] element_size The size of the element.
 *  \param[in] size The size of the buffer.
 *  \return CBUF_SUCCESS if successful, CBUF_FAILURE otherwise.
 */
int cbuf_init(cbuf_t *cbuf, size_t element_size, size_t size);

/*! \brief The circular buffer destructor function
 *  \details This function releases the circular buffer.
 *  \param[in] cbuf The circular buffer to be released.
 *  \return CBUF_SUCCESS if successful, CBUF_FAILURE otherwise.
 */
int cbuf_deinit(cbuf_t *cbuf);

/*! \brief The circular buffer writer function
 *  \details This function writes the element to the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \param[in] element The element to be written.
 *  \return CBUF_SUCCESS if successful, CBUF_FAILURE otherwise.
 */
int cbuf_read(cbuf_t *cbuf, void *element);

/*! \brief The circular buffer reader function
 *  \details This function reads the element from the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \param[out] element The element to be read.
 *  \return CBUF_SUCCESS if successful, CBUF_FAILURE otherwise.
 */
int cbuf_write(cbuf_t *cbuf, void *element);

/*! \brief The circular buffer writer function
 *  \details This function writes the element to the circular buffer.
 *  \param[in] cbuf The circular buffer.
 *  \param[in] element The element to be written.
 *  \return CBUF_SUCCESS if successful, CBUF_FAILURE otherwise.
 */
int cbuf_clear(cbuf_t *cbuf);

#ifdef __cplusplus
}
#endif

#endif // CBUF_H