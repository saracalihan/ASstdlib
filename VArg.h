/*
 * Copyright (c) 2023, Alihan SARAÇ <saracalihan@gmail.com>
 *
 * This file is under the "MIT" license. Please read "LICENSE" file for more detail.
 */

#ifndef VARG_HEADER
#define VARG_HEADER

#include <cstddef>
#include <stdarg.h>

#define VA_DEFAULT_TYPE int

#define FOR_EACH_VARG(args, type, func_body)                                   \
  do {                                                                         \
    va_start(args, type);                                                       \
    for (char *arg = va_start(args, type); arg != NULL;                        \
         arg = va_arg(args, type)) {                                           \
      body                                                                     \
    }                                                                          \
    va_end(args);                                                              \
  } while (0)

#endif