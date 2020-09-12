/* ----------------------------------------------------------------------------
Copyright (c) 2018, Microsoft Research, Daan Leijen
This is free software; you can redistribute it and/or modify it under the
terms of the MIT license. A copy of the license can be found in the file
"LICENSE" at the root of this distribution.
-----------------------------------------------------------------------------*/
#pragma once
#ifndef STDLIB_EXTERN_H
#define STDLIB_EXTERN_H

#include "mimalloc-internal.h"

#ifdef MI_STDLIB_EXTERN

// ------------------------------------------------------
// declare external standard lib dependencies
// suitable for compilation with -nostdlib, -nostdinc
// ------------------------------------------------------

// ------------------------------------
// NOTE: our target environment is wasm
// this definition already exists but
// provides some useful restrictions
#define __wasi__
uintptr_t __builtin_wasm_memory_size(int base);
uintptr_t __builtin_wasm_memory_grow(int a, size_t delta);
// ------------------------------------

// --------
// string.h
// --------
void *memset(void *str, int c, size_t n);
void *memcpy(void *dest, const void * src, size_t n);
void *memchr(const void *str, int c, size_t n);
char *strncpy(char *dest, const char *src, size_t n);
char *strstr(const char *haystack, const char *needle);
char *strncat(char *dest, const char *src, size_t n);
char *strerror(int errnum);
size_t strlen(const char *str);

// --------
// stdlib.h
// --------
void exit(int status);
int atexit(void (*func)(void));
char *getenv(const char *name);
long int strtol(const char *str, char **endptr, int base);
char *realpath(const char *restrict file_name, char *restrict resolved_name);
void arc4random_buf(void *buf, size_t nbytes);

// -------
// ctype.h
// -------
int toupper(int c);

// --------
// unistd.h
// --------
long int pathconf (const char *filename, int parameter);

// ------
// time.h
// ------
typedef int clockid_t;
typedef long time_t;
typedef long clock_t;
typedef long suseconds_t;
struct timespec {
  time_t tv_sec;
  long tv_nsec;
};
struct timeval {
  time_t tv_sec;
  suseconds_t tv_usec;
};

#define CLOCK_MONOTONIC 1
#define CLOCKS_PER_SEC ((clock_t) 1000000)

clock_t clock(void);
int clock_gettime(clockid_t clockid, struct timespec *tp);

// ----------
// resource.h
// ----------
#define	RUSAGE_SELF	0
struct rusage {
  struct timeval ru_utime;
  struct timeval ru_stime;
  long   ru_maxrss;
  long   ru_ixrss;
  long   ru_idrss;
  long   ru_isrss;
  long   ru_minflt;
  long   ru_majflt;
  long   ru_nswap;
  long   ru_inblock;
  long   ru_oublock;
  long   ru_msgsnd;
  long   ru_msgrcv;
  long   ru_nsignal;
  long   ru_nvcsw;
  long   ru_nivcsw;
};
int getrusage(int who, struct rusage *usage);

// ----------
// confname.h
// ----------
// #define _PC_PATH_MAX 4

// --------
// limits.h
// --------
// #define LONG_MAX 9223372036854775807L

// --------
// stdint.h
// --------

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef long int int64_t;
typedef long unsigned int uint64_t;
typedef long unsigned int uintptr_t;
// #define INTPTR_MAX 9223372036854775807L

// --------
// stdarg.h
// --------
#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define __va_copy(d,s) __builtin_va_copy(d,s)

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L || !defined(__STRICT_ANSI__)
#define va_copy(dest, src) __builtin_va_copy(dest, src)
#endif

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST 1
typedef __builtin_va_list __gnuc_va_list;
#endif

// ------
// FILE.h
// ------
struct _IO_FILE;
typedef struct _IO_FILE FILE;

// -------
// stdio.h
// -------
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
#define stdin stdin
#define stdout stdout
#define stderr stderr
int fputs (const char *str, FILE *stream);
int snprintf (char *s, size_t n, const char *format, ...);
int vsnprintf (char *s, size_t n, const char *format, va_list arg);

#endif // MI_STDLIB_EXTERN
#endif // STDLIB_EXTERN_H