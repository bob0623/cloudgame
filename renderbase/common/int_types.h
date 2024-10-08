/* -------------------------------------------------------------------------
 Name:	int_types.h
 Title:	C99 Compliant Integer Types and VarStr
 Package:	Server Platform Library Project

 Written:	Eric Lee <hahalee@163.com>

 $Id: int_types.h,v 1.1.1.1 2003/06/25 08:20:20 lch Exp $
 ------------------------------------------------------------------------- */

#ifndef     _INT_TYPES_H_
#define     _INT_TYPES_H_

#include <sys/types.h>

/* Even in pure C, we still need a standard boolean typedef */
#ifndef     __cplusplus
typedef unsigned char bool;
#define     true    1
#define     false   0
#endif	    /* !__cplusplus */

#ifdef	    __GNUC__
/* FreeBSD has these C99 int types defined in /sys/inttypes.h already */
/*
#ifndef     _SYS_INTTYPES_H_
typedef signed char int8_t;
typedef signed short int16_t;
//typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#endif 
*/
#include <stdint.h>
#elif	    defined(_MSC_VER)
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed __int64 int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
#endif /* _MSC_VER */


#define URI_TYPE int32_t

#endif /* !_INT_TYPES_H_ */

/*
 vim: set et ts=4 sts=4 syn=cpp :
 */
