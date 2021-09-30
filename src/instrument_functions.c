/*
 * Copyright (C) 2021, HENSOLDT Cyber GmbH
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * OS provided hooks for the gcc -finstrument-fucntions compiler flag.
 * Theses hooks will print markers at the entrance and at the exit of a
 * function. The resulting output format is the following:
 *
 * 0x123a() {
 * ..
 * 0x123a() }
 *
 * With the brackets indicating respectively the entrance and the exit of the
 * function at the address 0x123a.
 *
 * This output can be also translated into a call trace with function names and
 * proper nested printout by using the script provided at the path
 * sdk/scripts/debug/backtrace.py
 * of the SDK.
 */

#include "lib_debug/Debug.h"

#if !defined(LIB_DEBUG_INSTRUMENT_FUNCTIONS)
#   define LIB_DEBUG_INSTRUMENT_FUNCTIONS 1
#endif

#if LIB_DEBUG_INSTRUMENT_FUNCTIONS != 0

__attribute__((no_instrument_function))
void
__cyg_profile_func_enter(
    void* func,
    void* caller)
{
    Debug_PRINT(Debug_LOG_LEVEL_NONE, "\n%p {", func);
}

__attribute__((no_instrument_function))
void
__cyg_profile_func_exit(
    void* func,
    void* caller)
{
    Debug_PRINT(Debug_LOG_LEVEL_NONE, "\n%p }", func);
}

#endif
