/*! \file cbuf.c
 *  \brief The circular buffer implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include <stdlib.h>
#include <string.h>

#include "c-structs/error.h"
#include "c-structs/cbuf.h"

int cbuf_init(cbuf_t *cbuf, size_t element_size, size_t size)
{
    if(!cbuf)
        return ERR_NULL;

    if (size < 1)
        return ERR_EMPTY;

    cbuf->size = size;
    cbuf->element_size = element_size;
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->elements = malloc(size * element_size);
    if(!cbuf->elements)
        return ERR_FAILURE;

    return ERR_NONE;
}

int cbuf_deinit(cbuf_t *cbuf)
{
    if(!cbuf)
        return ERR_NULL;

    free(cbuf->elements);
    return ERR_NONE;
}

int cbuf_read(cbuf_t *cbuf, void *element)
{
    if(!cbuf)
        return ERR_NULL;

    if(cbuf->size == 0)
        return ERR_EMPTY;

    if(cbuf->size == 1)
    {   
        memcpy(element, cbuf->elements, cbuf->element_size);
        return ERR_NONE;
    } else
    {
        memcpy(element, cbuf->elements + cbuf->head * cbuf->element_size, cbuf->element_size);
        cbuf->head = (cbuf->head + 1) % cbuf->size;
        return ERR_NONE;
    }
}

int cbuf_write(cbuf_t *cbuf, void *element)
{
    if(!cbuf)
        return ERR_NULL;

    if(cbuf->size == 0)
        return ERR_EMPTY;

    if(cbuf->size == 1)
    {
        memcpy(cbuf->elements, element, cbuf->element_size);
        return ERR_NONE;
    } else
    {
        memcpy(cbuf->elements + cbuf->tail * cbuf->element_size, element, cbuf->element_size);
        cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        return ERR_NONE;
    }
}

int cbuf_clear(cbuf_t *cbuf)
{
    if(!cbuf)
        return ERR_NULL;

    cbuf->head = 0;
    cbuf->tail = 0;
    return ERR_NONE;
}