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

/*! \file       vla.h
 *  \brief      Variable-length array definition and manipulation functions.
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 */
#ifndef STRUCTS_VLA_H
#define STRUCTS_VLA_H

#ifndef STRUCTS_DEF
#define STRUCTS_DEF static inline
#endif  // STRUCTS_DEF

#include <stddef.h>

//! \brief VLA struct definition.
typedef struct vla {
    size_t length;    //!< VLA length.
    size_t capacity;  //!< VLA capacity.
    size_t size;      //!< VLA element size.
    void *elements;   //!< VLA elements.
} vla_t;

/*! \brief VLA construction function.
 *  \details This function creates a VLA of a given size and element size.
 *  \param[in] size VLA size.
 *  \param[in] size VLA element size.
 *  \param[in] capacity VLA initial capacity.
 *  \return The new VLA.
 */
STRUCTS_DEF vla_t vla_init(const size_t size, const size_t capacity);

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
STRUCTS_DEF int vla_extend(vla_t *const dest, const vla_t *restrict src);

/*! \brief VLA shrink function
 * 	\details This function shrinks the VLA capacity to the current length
 * 	\param[out] vla The VLA to shrink
 * 	\return Zero on success, non-zero on failure
 */
STRUCTS_DEF int vla_shrink(vla_t *const vla);

/*! \brief VLA truncate function
 * 	\details This function truncates the VLA to the specified length
 * 	\param[out] vla The VLA to truncate
 * 	\param[in] length The new VLA length
 * 	\return Zero on success, non-zero on failure
 */
STRUCTS_DEF int vla_trunc(vla_t *const vla, size_t length);

/*! \brief VLA length function.
 *  \details This function returns the VLA length.
 *  \param[in] vla VLA to get length of.
 *  \return VLA length.
 */
STRUCTS_DEF long vla_length(const vla_t *const vla);

/*! \brief VLA size function.
 *  \details This function returns the VLA element size.
 *  \param[in] vla VLA to get element size of.
 *  \return VLA element size.
 */
STRUCTS_DEF long vla_size(const vla_t *const vla);

/*! \brief VLA capacity function.
 *  \details This function returns the VLA capacity.
 *  \param[in] vla VLA to get capacity of.
 *  \return VLA capacity.
 */
STRUCTS_DEF long vla_capacity(const vla_t *const vla);

#ifdef STRUCTS_VLA_IMPL

#include <stdlib.h>
#include <string.h>

#include "structs/error.h"

/*! \brief Resize a variable length array.
 *  \details The new size is calculated by multiplying the element size by the
 * 			 new capacity
 * 	\param[in] vla Pointer to the variable length array.
 * 	\param[in] capacity The new capacity of the array.
 * 	\returns Zero on success, non-zero on failure.
 */
static int vla_resize(vla_t *const vla, const size_t capacity) {
    if (!vla || !vla->elements) return ERR_NULL;

    void *p;
    ASSERT(p = reallocarray(vla->elements, capacity, vla->size));

    vla->elements = p;
    vla->capacity = capacity;

    return ERR_NONE;
}

vla_t vla_init(const size_t size, const size_t capacity) {
    vla_t vla = {
        .size = size,
        .length = 0,
        .capacity = capacity,
        .elements = calloc(capacity, size),
    };

    ASSERT(vla.elements);

    return vla;
}

int vla_deinit(vla_t *const vla) {
    if (!vla || !vla->elements) return ERR_NULL;

    free(vla->elements);
    ASSERT(memset((void *)vla, 0, sizeof(vla_t)));

    return ERR_NONE;
}

int vla_push(vla_t *const vla, const void *element) {
    if (!vla || !vla->elements) return ERR_NULL;

    if (vla->length >= vla->capacity) {
        int ret;
        ERR_PROP(ret, vla_resize(vla, vla->capacity * 2));
    }

    // Shift elements right by one element size
    ASSERT(memmove(vla->elements + vla->size, vla->elements,
                   vla->length * vla->size));

    // Copy new element into index 0
    ASSERT(memcpy(vla->elements, element, vla->size));

    vla->length++;

    return ERR_NONE;
}

int vla_pop(vla_t *const vla, void *element) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (vla->length == 0) return ERR_EMPTY;

    int i;

    // Get first element
    ASSERT(memcpy(element, vla->elements, vla->size));

    // Shift memory block left by size of one element
    ASSERT(memmove(vla->elements, vla->elements + vla->size,
                   vla->length * vla->size));

    vla->length--;

    return ERR_NONE;
}

int vla_enq(vla_t *const vla, const void *element) {
    if (!vla || !vla->elements) return ERR_NULL;

    // Resize if necessary
    if (vla->length == vla->capacity) {
        int ret;
        ERR_PROP(ret, vla_resize(vla, vla->capacity * 2) == ERR_FAILURE);
    }

    // Append element to list
    ASSERT(
        memcpy(vla->elements + (vla->length * vla->size), element, vla->size));
    vla->length++;

    return ERR_NONE;
}

int vla_get(const vla_t *const vla, const size_t index, void *element) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (index >= vla->length) return ERR_INDEX_OUT_OF_BOUNDS;

    ASSERT(memcpy(element, vla->elements + (index * vla->size), vla->size));

    return ERR_NONE;
}

int vla_getp(const vla_t *const vla, const size_t index, void **const element) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (index >= vla->length) return ERR_INDEX_OUT_OF_BOUNDS;

    *element = vla->elements + (index * vla->size);

    return ERR_NONE;
}

int vla_set(vla_t *const vla, const size_t index, const void *element) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (index > vla->length) return ERR_INDEX_OUT_OF_BOUNDS;

    if (vla->length == vla->capacity) {
        int ret;
        ERR_PROP(ret, vla_resize(vla, vla->capacity * 2));
    }

    ASSERT(memcpy(vla->elements + (index * vla->size), element, vla->size));

    return ERR_NONE;
}

int vla_ins(vla_t *const vla, const size_t index, const void *element) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (index > vla->length) return ERR_INDEX_OUT_OF_BOUNDS;

    if (vla->length == vla->capacity) {
        int ret;
        ERR_PROP(ret, vla_resize(vla, vla->capacity * 2));
    }

    // Make an empty slot at index by shifting [index, n) block right
    ASSERT(memmove(vla->elements + ((index + 1) * vla->size),
                   vla->elements + (index * vla->size),
                   (vla->length - index) * vla->size));

    // Copy element into slot
    ASSERT(memcpy(vla->elements + (index * vla->size), element, vla->size));

    vla->length++;

    return ERR_NONE;
}

int vla_del(vla_t *const vla, const size_t index) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (index >= vla->length) return ERR_INDEX_OUT_OF_BOUNDS;

    // Shift block at [index + 1, n) left
    ASSERT(memmove(vla->elements + (index * vla->size),
                   vla->elements + ((index + 1) * vla->size),
                   (vla->length - index + 1) * vla->size));

    vla->length--;

    return ERR_NONE;
}

int vla_clear(vla_t *const vla) {
    if (!vla || !vla->elements) return ERR_NULL;

    memset(vla->elements, 0, vla->size * vla->capacity);

    vla->length = 0;
    return ERR_NONE;
}

int vla_extend(vla_t *const dest, const vla_t *restrict src) {
    if (!dest || !src) return ERR_NULL;

    if (dest->size != src->size) return ERR_INVALID_ARGUMENT;

    int ret;

    // Resize destination until sufficiently large
    while (dest->capacity < dest->length + src->length)
        ERR_PROP(ret, vla_resize(dest, dest->capacity * 2));

    // Copy source into destination
    ASSERT(memcpy(dest->elements + (dest->length * dest->size), src->elements,
                  src->length * src->size));

    return ERR_NONE;
}

int vla_shrink(vla_t *const vla) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (vla->length == 0) return ERR_EMPTY;

    int ret;
    ERR_PROP(ret, vla_resize(vla, vla->length));

    return ERR_NONE;
}

int vla_trunc(vla_t *const vla, size_t length) {
    if (!vla || !vla->elements) return ERR_NULL;
    if (vla->length == 0) return ERR_EMPTY;
    if (vla->length < length) return ERR_INVALID_ARGUMENT;

    int ret;
    ERR_PROP(ret, vla_resize(vla, length));
    vla->length = length;

    return ERR_NONE;
}

long vla_length(const vla_t *const vla) {
    return (!vla || !vla->elements) ? ERR_NULL : vla->length;
}

long vla_size(const vla_t *const vla) {
    return (!vla || !vla->elements) ? ERR_NULL : vla->size;
}

long vla_capacity(const vla_t *const vla) {
    return (!vla || !vla->elements) ? ERR_NONE : vla->capacity;
}

#endif  // STRUCTS_VLA_IMPL

#endif  // STRUCTS_VLA_H
