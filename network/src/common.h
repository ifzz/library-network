/*
**  @(#)common.h
**
**  libnetwork - common definitions
**  -------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
*/
#ifndef __COMMON_H
#define __COMMON_H

/*
**  Check if file stream I/O options are defined in another include file.
*/
#ifdef  _F_RO
#error  _F_RO is defined in another include file
#endif
#ifdef  _F_RO_BIN
#error  _F_RO_BIN is defined in another include file
#endif
#ifdef  _F_RW_BIN
#error  _F_RW_BIN is defined in another include file
#endif
#ifdef  _F_AP
#error  _F_AP is defined in another include file
#endif
#ifdef  _F_AP_BIN
#error  _F_AP_BIN is defined in another include file
#endif

/*
**  Define file stream I/O options.
*/
#define _F_RO "r"
#define _F_RO_BIN "rb+"
#define _F_RW_BIN "wb+"
#define _F_AP "a+"
#define _F_AP_BIN "ab+"

/*
**  Define maximum file name string size.
*/
#ifndef _MAX_FILENAME_SIZE
#define _MAX_FILENAME_SIZE 255
#else
#error  _MAX_FILENAME_SIZE is defined in another include file
#endif

/*
**  Undefine TRUE and FALSE if defined in another include file.
*/
#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

/*
**  Check if data type is defined in another include file.
*/
#ifdef bool_c_t
#error bool_c_t is defined in another include file
#endif

/*
**  Define Boolean data type.
*/
typedef enum { FALSE = 0, TRUE = 1 } bool_c_t;

/*
**  Check if data type is defined in another include file.
*/
#ifdef fptr_c_t
#error fptr_c_t is defined in another include file
#endif

/*
**  Define custon function pointer data type.
*/
typedef void (*fptr_c_t)(int);

/*
**  Check if data type is defined in another include file.
*/
#ifdef string_c_t
#error string_c_t is defined in another include file
#endif

/*
**  Define custom string (null-terminated character array) data type.
*/
typedef char *string_c_t;

#endif /* __COMMON_H */

