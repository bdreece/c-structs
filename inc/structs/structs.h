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

#include "structs/cbuf.h"
#include "structs/hashmap.h"
#include "structs/map.h"
#include "structs/vla.h"

#endif  // STRUCTS_STRUCTS_H
