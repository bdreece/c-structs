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

/*! \file       error.h
 *  \brief      List of error codes pertaining to the library.
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       12/28/2021
 */

#ifndef ERROR_H
#define ERROR_H
#include <stdio.h>

#ifdef DEBUG
#define ASSERT(x)                                                             \
    do {                                                                      \
        if (!(x)) {                                                           \
            fprintf(stderr, "[STRUCTS_ERR] Assertion failure: \"%s\"\n", #x); \
            fprintf(stderr, "[STRUCTS_ERR] errno: %m\n");                     \
            fprintf(stderr, "[STRUCTS_ERR] Assertion failed at %s:%d\n",      \
                    __FILE__, __LINE__);                                      \
            exit(1);                                                          \
        }                                                                     \
    } while (0)
#else
#define ASSERT(x) (void)(x)
#endif  // DEBUG

#define ERR_PROP(ret, expr) \
    if (((ret) = (expr)) < 0) return (ret)

#define ERR_NONE 0                  //!< No error
#define ERR_FAILURE -1              //!< Memory failure
#define ERR_INVALID_ARGUMENT -2     //!< Invalid argument
#define ERR_NULL -3                 //!< Null pointer
#define ERR_EMPTY -4                //!< Empty structure
#define ERR_INDEX_OUT_OF_BOUNDS -5  //!< Index out of bounds
#define ERR_NOT_FOUND -6            //!< Element not found

#endif  // ERROR_H
