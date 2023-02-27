#pragma once
#include "Logger.h"
#ifdef _DEBUG
#define NASSERT(condition, error, ...) if((condition)) { PRINT_ERROR(error, __VA_ARGS__) ; abort();}
#define DEBUG(error, ...)  { PRINT_ERROR(error, __VA_ARGS__) ; abort();}
#else
#define NASSERT(condition, error, ...) if((condition)) {}
#define DEBUG(error, ...){}
#endif

typedef signed char        int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef float float32;
typedef double float64;

typedef int bool32;
typedef std::string sstring;
typedef const char* cstring;

#define FALSE 0
#define TRUE 1 