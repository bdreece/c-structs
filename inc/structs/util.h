/**
 * \file    util.h
 * \brief   libstructs utility functions
 * \author  Brian Reece
 * \version v0.3-alpha
 * \date    2022-01-19
 */

#ifndef STRUCTS_UTIL_H
#define STRUCTS_UTIL_H

#ifndef STRUCTS_DEF
#define STRUCTS_DEF static inline
#endif  // STRUCTS_DEF

#include <stddef.h>
/**
 * TODO: Implement alternative heap
#ifdef STRUCTS_NO_STDLIB_H

STRUCTS_DEF void *structs_malloc(size_t size);

STRUCTS_DEF void *structs_calloc(size_t nmemb, size_t size);

STRUCTS_DEF void *structs_realloc(void *ptr, size_t size);

STRUCTS_DEF void structs_free(void *ptr);

#define STRUCTS_MALLOC(s) structs_malloc((s))
#define STRUCTS_CALLOC(n, s) structs_calloc((n), (s))
#define STRUCTS_REALLOC(p, s) structs_realloc((p), (s))
#define STRUCTS_FREE(p) structs_free((p))

#ifdef STRUCTS_UTIL_IMPL

#ifndef STRUCTS_HEAP_SIZE
#define STRUCTS_HEAP_SIZE 64000UL
#endif  // STRUCTS_HEAP_SIZE

typedef struct {
  char bytes[STRUCTS_HEAP_SIZE];
  size_t offsets[STRUCTS_HEAP_SIZE];
} _heap_t;

static _heap_t heap;

// TODO: Implement malloc
void *structs_malloc(size_t size) { return NULL; }

// TODO: Implement calloc
void *structs_calloc(size_t nmemb, size_t size) { return NULL; }

// TODO: Implement realloc
void *structs_realloc(void *ptr, size_t size) { return NULL; }

// TODO: Implement free
void structs_free(void *ptr) { return; }

#endif  // STRUCTS_UTIL_IMPL

#endif  // STRUCTS_NO_STDLIB_H
*/

#ifdef STRUCTS_NO_STRING_H

STRUCTS_DEF void *structs_memcpy(void *restrict dest, const void *restrict src,
                                 size_t n);

STRUCTS_DEF void *structs_memmove(void *dest, const void *src, size_t n);

STRUCTS_DEF void *structs_memset(void *s, int c, size_t n);

#define STRUCTS_MEMCPY(d, s, n) structs_memcpy((d), (s), (n))
#define STRUCTS_MEMMOVE(d, s, n) structs_memmove((d), (s), (n))
#define STRUCTS_MEMSET(d, c, n) structs_memset((d), (c), (n))

#ifdef STRUCTS_UTIL_IMPL

// TODO: Implement memcpy
void *structs_memcpy(void *dest, const void *src, size_t n) {
  size_t i;
  for (i = 0; i < n; i++) {
    *((char *)(dest)++) = *((char *)(src)++);
  }

  return dest;
}

// TODO: Implement memmove
void *structs_memmove(void *dest, const void *src, size_t n) {
  size_t i;
  for (i = 0; i < n; i++) {
    *((char *)(dest)++) = *((char *)(src)++);
  }

  return dest;
}

void *structs_memset(void *s, int c, size_t n) {
  size_t i;
  for (i = 0; i < n; i++) {
    *((int *)(s)++) = c;
  }

  return s;
}

#endif  // STRUCTS_UTIL_IMPL

#endif  // STRUCTS_NO_STRING_H

#endif  // STRUCTS_UTIL_H
