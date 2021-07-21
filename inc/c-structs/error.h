/*! \file error.h
 *  \brief List of error codes pertaining to the library.
 *  \author Brian Reece
 *  \version 0.1.0
 */

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_NONE                                    0 //!< No error
#define ERR_FAILURE                                -1 //!< Failure
#define ERR_INVALID_ARGUMENT                       -2 //!< Invalid argument
#define ERR_NULL                                   -3 //!< Null pointer
#define ERR_EMPTY                                  -4 //!< Empty structure
#define ERR_INDEX_OUT_OF_BOUNDS                    -5 //!< Index out of bounds
#define ERR_NOT_FOUND                              -6 //!< Not found

#ifdef __cplusplus
}
#endif

#endif // ERROR_H