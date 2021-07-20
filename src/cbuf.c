/*! \file cbuf.c
 *  \brief The circular buffer implementation
 *  \author Brian Reece
 *  \version 0.1.0
 */

#include <stdlib.h>
#include <string.h>

#include "cbuf.h"

int cbuf_init(cbuf_t *cbuf, size_t element_size, size_t size)
{
    if(!cbuf)
        return CBUF_FAILURE;

    if (size < 1)
        return CBUF_EMPTY;

    cbuf->size = size;
    cbuf->element_size = element_size;
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->elements = malloc(size * element_size);
    if(!cbuf->elements)
        return CBUF_FAILURE;

    return CBUF_SUCCESS;
}

int cbuf_deinit(cbuf_t *cbuf)
{
    if(!cbuf)
        return CBUF_FAILURE;

    free(cbuf->elements);
    return CBUF_SUCCESS;
}

int cbuf_read(cbuf_t *cbuf, void *element)
{
    if(!cbuf)
        return CBUF_FAILURE;

    if(cbuf->size == 0)
        return CBUF_EMPTY;

    if(cbuf->size == 1)
    {   
        memcpy(element, cbuf->elements, cbuf->element_size);
        return CBUF_SUCCESS;
    } else
    {
        memcpy(element, cbuf->elements + cbuf->head * cbuf->element_size, cbuf->element_size);
        cbuf->head = (cbuf->head + 1) % cbuf->size;
        return CBUF_SUCCESS;
    }
}

int cbuf_write(cbuf_t *cbuf, void *element)
{
    if(!cbuf)
        return CBUF_FAILURE;

    if(cbuf->size == 0)
        return CBUF_EMPTY;

    if(cbuf->size == 1)
    {
        memcpy(cbuf->elements, element, cbuf->element_size);
        return CBUF_SUCCESS;
    } else
    {
        memcpy(cbuf->elements + cbuf->tail * cbuf->element_size, element, cbuf->element_size);
        cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        return CBUF_SUCCESS;
    }
}

int cbuf_clear(cbuf_t *cbuf)
{
    if(!cbuf)
        return CBUF_FAILURE;

    cbuf->head = 0;
    cbuf->tail = 0;
    return CBUF_SUCCESS;
}

