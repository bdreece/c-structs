/**
 * MIT License
 *
 * Copyright (c) 2022 Brian Reece
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*! \file       ringbuf.h
 *  \brief      Ring buffer structure definition and manipulation functions.
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       2022-04-06
 */
#ifndef RINGBUF_H
#define RINGBUF_H

#ifndef STRUCTS_DEF
#define STRUCTS_DEF static inline
#endif  // STRUCTS_DEF

#include <stddef.h>

//! \brief Ring buffer structure
typedef struct ringbuf {
    size_t head;      //!< The head index of the buffer (read end)
    size_t tail;      //!< The tail index of the buffer (write end)
    size_t length;    //!< The number of elements in the buffer
    size_t capacity;  //!< The size of the buffer
    size_t size;      //!< The size of the element
    void *elements;   //!< The buffer elements
} ringbuf_t;

/*! \brief Ring buffer constructor function
 *  \details This function initializes a ring buffer.
 *  \param[in] size The size of the element.
 *  \param[in] capacity The capacity of the buffer.
 *  \return The new ringbuf.
 */
STRUCTS_DEF ringbuf_t ringbuf_init(const size_t size, const size_t capacity);

/*! \brief Ring buffer destructor function
 *  \details This function releases the ring buffer.
 *  \param[in] ringbuf The ring buffer to be released.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int ringbuf_deinit(ringbuf_t *const ringbuf);

/*! \brief Ring buffer writer function
 *  \details This function writes the element to the ring buffer.
 *  \param[in] ringbuf The ring buffer.
 *  \param[in] element The element to be written.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int ringbuf_read(ringbuf_t *const ringbuf, void *restrict element);

/*! \brief Ring buffer reader function
 *  \details This function reads the element from the ring buffer.
 *  \param[in] ringbuf The ring buffer.
 *  \param[out] element The element to be read.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int ringbuf_write(ringbuf_t *const ringbuf,
                              const void *restrict element);

/*! \brief Ring buffer get function
 *  \details This function retrieves an element from the ring buffer
 *           without removing it.
 *  \param[in] ringbuf The ring buffer.
 *  \param[out] element The element to be read.
 *  \return Zero if successful, non-zero otherwise
 */
STRUCTS_DEF int ringbuf_get(const ringbuf_t *const ringbuf,
                            void *restrict element);

/*! \brief Ring buffer get pointer function
 *  \details This function retrieves a pointer to an element from the
 *           ring buffer without removing it.
 *  \param[in] ringbuf The ring buffer
 *  \param[out] element The element to be read
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int ringbuf_getp(const ringbuf_t *const ringbuf,
                             void **const element);

/*! \brief Ring buffer clear function
 *  \details This function zeroes all elements in the ring buffer.
 *  \param[in] ringbuf The ring buffer.
 *  \return Zero if successful, non-zero otherwise.
 */
STRUCTS_DEF int ringbuf_clear(ringbuf_t *const ringbuf);

/*! \brief Ring buffer length function
 * 	\details This function returns the length of a ring buffer.
 * 	\param[in] ringbuf The ring buffer
 * 	\return The length of the ring buffer
 */
STRUCTS_DEF long ringbuf_length(const ringbuf_t *const ringbuf);

/*! \brief Ring buffer size function
 * 	\details This function returns the element size of a ring buffer.
 * 	\param[in] ringbuf The ring buffer
 * 	\return The element size of the ring buffer
 */
STRUCTS_DEF long ringbuf_size(const ringbuf_t *const ringbuf);

/*! \brief Ring buffer capacity function
 * 	\details This function returns the capacity of a ring buffer.
 * 	\param[in] ringbuf The ring buffer
 * 	\return The capacity of the ring buffer
 */
STRUCTS_DEF long ringbuf_capacity(const ringbuf_t *const ringbuf);

#ifdef STRUCTS_RINGBUF_IMPL

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"

ringbuf_t ringbuf_init(const size_t size, const size_t capacity) {
    ringbuf_t ringbuf = {
        .capacity = capacity,
        .size = size,
        .length = 0,
        .head = 0,
        .tail = 0,
        .elements = calloc(capacity, size),
    };

    ASSERT(ringbuf.elements);

    return ringbuf;
}

int ringbuf_deinit(ringbuf_t *const ringbuf) {
    if (!ringbuf) return ERR_NULL;

    free(ringbuf->elements);
    ASSERT(memset((void *)ringbuf, 0, sizeof(ringbuf_t)));

    return ERR_NONE;
}

int ringbuf_read(ringbuf_t *const ringbuf, void *element) {
    if (!ringbuf || !ringbuf->elements) return ERR_NULL;
    if (ringbuf->capacity == 0 || ringbuf->length == 0) return ERR_EMPTY;

    if (ringbuf->capacity == 1) {
        ASSERT(memcpy(element, ringbuf->elements, ringbuf->size));
    } else {
        ASSERT(memcpy(element,
                      ringbuf->elements + ringbuf->head * ringbuf->size,
                      ringbuf->size));
        ringbuf->head = (ringbuf->head + 1) % ringbuf->capacity;
        ringbuf->length--;
    }
    return ERR_NONE;
}

int ringbuf_write(ringbuf_t *const ringbuf, const void *element) {
    if (!ringbuf || !ringbuf->elements) return ERR_NULL;
    if (ringbuf->capacity == 0) return ERR_EMPTY;

    if (ringbuf->capacity == 1) {
        ASSERT(memcpy(ringbuf->elements, element, ringbuf->size));
        ringbuf->length = 1;
    } else {
        ASSERT(memcpy(ringbuf->elements + ringbuf->tail * ringbuf->size,
                      element, ringbuf->size));
        ringbuf->tail = (ringbuf->tail + 1) % ringbuf->capacity;
        ringbuf->length++;
    }
    return ERR_NONE;
}

int ringbuf_get(const ringbuf_t *const ringbuf, void *element) {
    if (!ringbuf || !ringbuf->elements) return ERR_NULL;
    if (ringbuf->length == 0) return ERR_EMPTY;

    if (ringbuf->capacity == 1) {
        ASSERT(memcpy(element, ringbuf->elements, ringbuf->size));
    } else {
        ASSERT(memcpy(element,
                      ringbuf->elements + ringbuf->tail * ringbuf->size,
                      ringbuf->size));
    }
    return ERR_NONE;
}

int ringbuf_getp(const ringbuf_t *const ringbuf, void **const element) {
    if (!ringbuf || !ringbuf->elements) return ERR_NULL;
    if (ringbuf->length == 0) return ERR_EMPTY;

    if (ringbuf->capacity == 1) {
        *element = ringbuf->elements;
    } else {
        *element = ringbuf->elements + ringbuf->tail * ringbuf->size;
    }

    return ERR_NONE;
}

int ringbuf_clear(ringbuf_t *const ringbuf) {
    if (!ringbuf || !ringbuf->elements) return ERR_NULL;

    ASSERT(memset(ringbuf->elements, 0, ringbuf->size * ringbuf->capacity));
    ringbuf->head = 0;
    ringbuf->tail = 0;
    ringbuf->length = 0;
    return ERR_NONE;
}

long ringbuf_length(const ringbuf_t *const ringbuf) {
    return (!ringbuf || !ringbuf->elements) ? ERR_NULL : ringbuf->length;
}

long ringbuf_size(const ringbuf_t *const ringbuf) {
    return (!ringbuf || !ringbuf->elements) ? ERR_NULL : ringbuf->size;
}

long ringbuf_capacity(const ringbuf_t *const ringbuf) {
    return (!ringbuf || !ringbuf->elements) ? ERR_NULL : ringbuf->capacity;
}

#endif  // STRUCTS_RINGBUF_IMPL

#endif  // RINGBUF_H
