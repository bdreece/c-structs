/*! \file vla.h 
 *  \brief VLA definition and manipulation functions.
 *  \author Brian Reece
 *  \version 0.1.0
 */
#ifndef VLA_H
#define VLA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define VLA_SUCCESS 0
#define VLA_FAILURE -1
#define VLA_ARRAY_SIZE_MISMATCH -2
#define VLA_ARRAY_SIZE_ZERO -3
#define VLA_ELEMENT_SIZE_MISMATCH -4
#define VLA_ELEMENT_SIZE_ZERO -5 

//! \brief VLA struct definition.
typedef struct vla {
    unsigned long size;
    unsigned long capacity;
    size_t element_size;
    void **elements;
} vla_t;
//! \brief VLA creation function.
int vla_init(struct vla *vla, size_t element_size, unsigned long initial_size);

//! \brief VLA push function.
int vla_push(struct vla *vla, void *element);

//! \brief VLA pop function.
int vla_pop(struct vla *vla, void *element);

//! \brief VLA get function.
int vla_get(struct vla *vla, unsigned long i, void *element);

//! \brief VLA set function.
int vla_set(struct vla *vla, unsigned long i, void *element);

//! \brief VLA insert function.
int vla_insert(struct vla *vla, void *element, unsigned long index);

//! \brief VLA delete function.
int vla_delete(struct vla *vla, unsigned long i);

//! \brief VLA clear function.
int vla_clear(struct vla *vla);

//! \brief VLA size function.
unsigned long vla_size(struct vla *vla);

//! \brief VLA capacity function.
unsigned long vla_capacity(struct vla *vla);

#ifdef __cplusplus
}
#endif

#endif // VLA_H