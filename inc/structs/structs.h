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

/**
 * \file    structs.h
 * \brief   libstructs meta-header
 * \author  Brian Reece
 * \version v0.3-alpha
 * \date    2022-01-17
 */

#ifndef STRUCTS_STRUCTS_H

#ifdef STRUCTS_ALL_IMPL
#define STRUCTS_VLA_IMPL
#define STRUCTS_CBUF_IMPL
#define STRUCTS_MAP_IMPL
#define STRUCTS_HASHMAP_IMPL
#endif  // STRUCTS_ALL_IMPL

// #include "structs/hashmap.h"
#include "structs/map.h"
#include "structs/ringbuf.h"
#include "structs/vla.h"

#endif  // STRUCTS_STRUCTS_H
