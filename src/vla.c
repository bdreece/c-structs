/*! \file vla.c
 *  \brief Variable length array implementation.
 */

#include <string.h>
#include <stdlib.h>

#include "vla.h"

static int vla_resize(vla_t *vla, unsigned long size) {
    void *p = realloc(vla->elements, vla->element_size * size);
    if (p == NULL) {
        return VLA_FAILURE;
    }
    vla->elements = p;
    vla->capacity = size;
    return VLA_SUCCESS;
}

unsigned long vla_size(vla_t *vla) {
    return vla->size;
}

unsigned long vla_capacity(vla_t *vla) {
    return vla->capacity;
}

int vla_init(vla_t *vla, size_t element_size, unsigned long initial_size) {
    vla->element_size = element_size;
    vla->size = 0;
    vla->capacity = initial_size;
    vla->elements = malloc(element_size * initial_size);
    if (vla->elements == NULL) {
        return VLA_FAILURE;
    }
    return VLA_SUCCESS;
}

int vla_push(vla_t *vla, void *element) {
    if (vla->size == vla->capacity) {
        if (vla_resize(vla, vla->capacity * 2) == VLA_FAILURE) {
            return VLA_FAILURE;
        }
    }
    memcpy(vla->elements + (vla->size * vla->element_size), element, vla->element_size);
    vla->size++;
    return VLA_SUCCESS;
}

int vla_pop(vla_t *vla, void *element) {
    if (vla->size == 0) {
        return VLA_FAILURE;
    }
    memcpy(element, vla->elements[0], vla->element_size);
    vla->elements += vla->element_size;

    vla->size--;
    return VLA_SUCCESS;
}

int vla_get(vla_t *vla, unsigned long index, void *element) {
    if (index >= vla->size) {
        return VLA_FAILURE;
    }
    
    memcpy(element, vla->elements + (index * vla->element_size), vla->element_size);
    return VLA_SUCCESS;
}

int vla_set(vla_t *vla, unsigned long index, void *element) {
    if (index >= vla->size) {
        return VLA_FAILURE;
    }

    memcpy(vla->elements + (index * vla->element_size), element, vla->element_size);
    return VLA_SUCCESS;
}

int vla_delete(vla_t *vla, unsigned long index) {
    if (index >= vla->size) {
        return VLA_FAILURE;
    }

    vla->elements += (index * vla->element_size);
    vla->size--;
    return VLA_SUCCESS;
}

int vla_insert(vla_t *vla, void *element, unsigned long index) {
    if (index > vla->size) {
        return VLA_FAILURE;
    }
    if (vla->size == vla->capacity) {
        if (vla_resize(vla, vla->capacity * 2) == VLA_FAILURE) {
            return VLA_FAILURE;
        }
    }
    memmove(vla->elements + (index * vla->element_size) + vla->element_size,
            vla->elements + (index * vla->element_size),
            (vla->size - index) * vla->element_size);

    vla->size++;
    memcpy(vla->elements + (index * vla->element_size), element, vla->element_size);
    return VLA_SUCCESS;
}

int vla_clear(vla_t *vla) {
    vla->size = 0;
    return VLA_SUCCESS;
}