/*! \file       error.h
 *  \brief      List of error codes pertaining to the library.
 *  \author     Brian Reece
 *  \version    v0.3-alpha
 *  \date       12/28/2021
 */

#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include <error.h>

#ifdef __cplusplus
extern "C" {
#endif

//! \brief Assertion macro
#define ASSERT(x)                                                       \
  do {                                                                  \
    if (!(x))                                                           \
      error_at_line(1, errno, __FILE__, __LINE__, "[ERROR]: %s\n", #x); \
  } while (0)

#define ERR_NONE 0                  //!< No error
#define ERR_FAILURE -1              //!< Memory failure
#define ERR_INVALID_ARGUMENT -2     //!< Invalid argument
#define ERR_NULL -3                 //!< Null pointer
#define ERR_EMPTY -4                //!< Empty structure
#define ERR_INDEX_OUT_OF_BOUNDS -5  //!< Index out of bounds
#define ERR_NOT_FOUND -6            //!< Element not found

#ifdef __cplusplus
}
#endif

#endif  // ERROR_H
