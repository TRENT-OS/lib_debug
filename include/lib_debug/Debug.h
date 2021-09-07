/*
 * Copyright (C) 2019-2021, HENSOLDT Cyber GmbH
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @addtogroup lib_debug
 * @{
 *
 * @file Debug.h
 *
 * @brief Debug macros and functions
 */

#pragma once

/* Configuration--------------------------------------------------------------*/

#if !defined(DEBUG_CONFIG_H_FILE)
#   error a configuration file must be provided! See Debug_Config.h.example
#else
#   define Debug_XSTR(d)    Debug_STR(d)
#   define Debug_STR(d)     #d
#   include Debug_XSTR(DEBUG_CONFIG_H_FILE)
#endif

#if !defined (Debug_Config_STANDARD_ASSERT) && \
    !defined (Debug_Config_DISABLE_ASSERT)  && \
    !defined (Debug_Config_ENABLE_ASSERT)
#error make a choice!
#endif

#if !defined (Debug_Config_ASSERT_SELF_PTR) && \
    !defined (Debug_Config_NO_ASSERT_SELF_PTR)
#error make a choice!
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

/* Macro hacks ---------------------------------------------------------------*/

#define Debug_STRINGIZE(x)  Debug_STRINGIZE2(x)
#define Debug_STRINGIZE2(x) #x

/* Exported constants --------------------------------------------------------*/

#define Debug_LOG_LEVEL_NONE    0
#define Debug_LOG_LEVEL_ASSERT  1
#define Debug_LOG_LEVEL_FATAL   2
#define Debug_LOG_LEVEL_ERROR   3
#define Debug_LOG_LEVEL_WARNING 4
#define Debug_LOG_LEVEL_INFO    5
#define Debug_LOG_LEVEL_DEBUG   6
#define Debug_LOG_LEVEL_TRACE   7

/* Print macro ---------------------------------------------------------------*/

#define Debug_PRINT(LEVEL, ...)  \
    Debug_PRINT__(LEVEL, __VA_ARGS__)

#if !defined (Debug_Config_PRINT_TO_LOG_SERVER)
#    define Debug_PRINT__(LEVEL, ...)   \
        do                              \
        {                               \
            printf(__VA_ARGS__);        \
            printf("\n");               \
        } while (0)
#else
#   include Debug_Config_LOG_SERVER_H
#endif

/* Build message -------------------------------------------------------------*/

#define Debug_LOG_MSG(...) \
    Debug_LOG_MSG_WITH_FILE_LINE(__VA_ARGS__)

#define Debug_DUMP_MSG(...) \
    Debug_DUMP_MSG_WITH_FILE_LINE(__VA_ARGS__)

#if defined(Debug_Config_LOG_WITH_FILE_LINE)
#   define Debug_LOG_MSG_WITH_FILE_LINE(...)    \
         __FILE__ ":" Debug_STRINGIZE(__LINE__) \
         ": " __VA_ARGS__
#   define Debug_DUMP_MSG_WITH_FILE_LINE(...)    \
         __FILE__ ":" Debug_STRINGIZE(__LINE__) \
         ": ", __VA_ARGS__
#else
#   define Debug_LOG_MSG_WITH_FILE_LINE(...) \
        __VA_ARGS__
#   define Debug_DUMP_MSG_WITH_FILE_LINE(...) \
        __VA_ARGS__
#endif

/* Check constants------------------------------------------------------------*/

#if !defined(Debug_Config_LOG_LEVEL)  \
    || Debug_Config_LOG_LEVEL == Debug_LOG_LEVEL_NONE

/* Debug_LOG -----------------------------------------------------------------*/

#    if !defined(Debug_LOG)
#        define Debug_LOG(LEVEL, LEVEL_STR, ...)
#    endif
#    if !defined(Debug_LOG_ASSERT)
#        define Debug_LOG_ASSERT(...)
#    endif
#    if !defined(Debug_LOG_FATAL)
#        define Debug_LOG_FATAL(...)
#    endif
#    if !defined(Debug_LOG_ERROR)
#        define Debug_LOG_ERROR(...)
#    endif
#    if !defined(Debug_LOG_WARNING)
#        define Debug_LOG_WARNING(...)
#    endif
#    if !defined(Debug_LOG_INFO)
#        define Debug_LOG_INFO(...)
#    endif
#    if !defined(Debug_LOG_DEBUG)
#        define Debug_LOG_DEBUG(...)
#    endif
#    if !defined(Debug_LOG_TRACE)
#        define Debug_LOG_TRACE(...)
#    endif

/* Debug_DUMP ----------------------------------------------------------------*/

#    if !defined(Debug_DUMP)
#        define Debug_DUMP(LEVEL, LEVEL_STR, ...)
#    endif
#    if !defined(Debug_DUMP_ASSERT)
#        define Debug_DUMP_ASSERT(...)
#    endif
#    if !defined(Debug_DUMP_FATAL)
#        define Debug_DUMP_FATAL(...)
#    endif
#    if !defined(Debug_DUMP_ERROR)
#        define Debug_DUMP_ERROR(...)
#    endif
#    if !defined(Debug_DUMP_WARNING)
#        define Debug_DUMP_WARNING(...)
#    endif
#    if !defined(Debug_DUMP_INFO)
#        define Debug_DUMP_INFO(...)
#    endif
#    if !defined(Debug_DUMP_DEBUG)
#        define Debug_DUMP_DEBUG(...)
#    endif
#    if !defined(Debug_DUMP_TRACE)
#        define Debug_DUMP_TRACE(...)
#    endif

#else

/* Debug_LOG -----------------------------------------------------------------*/

#    if defined(Debug_Config_INCLUDE_LEVEL_IN_MSG)
#    define Debug_LOG(LEVEL, LEVEL_STR, ...) \
            Debug_PRINT(LEVEL, LEVEL_STR ": " Debug_LOG_MSG(__VA_ARGS__))
#    else
#    define Debug_LOG(LEVEL, LEVEL_STR, ...) \
            Debug_PRINT(LEVEL, Debug_LOG_MSG(__VA_ARGS__))
#    endif

#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_TRACE
#        define Debug_LOG_TRACE(...)
#    else
#        define Debug_LOG_TRACE(...)\
             Debug_LOG(Debug_LOG_LEVEL_TRACE, "  TRACE", __VA_ARGS__)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_DEBUG
#        define Debug_LOG_DEBUG(...)
#    else
#        define Debug_LOG_DEBUG(...)\
             Debug_LOG(Debug_LOG_LEVEL_DEBUG, "  DEBUG", __VA_ARGS__)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_INFO
#        define Debug_LOG_INFO(...)
#    else
#        define Debug_LOG_INFO(...)\
             Debug_LOG(Debug_LOG_LEVEL_INFO, "   INFO", __VA_ARGS__)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_WARNING
#        define Debug_LOG_WARNING(...)
#    else
#        define Debug_LOG_WARNING(...)\
             Debug_LOG(Debug_LOG_LEVEL_WARNING, "WARNING", __VA_ARGS__)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_ERROR
#        define Debug_LOG_ERROR(...)
#    else
#        define Debug_LOG_ERROR(...)\
             Debug_LOG(Debug_LOG_LEVEL_ERROR, "  ERROR", __VA_ARGS__)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_FATAL
#        define Debug_LOG_FATAL(...)
#    else
#        define Debug_LOG_FATAL(...)\
             Debug_LOG(Debug_LOG_LEVEL_FATAL, "  FATAL", __VA_ARGS__)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_ASSERT
#        define Debug_LOG_ASSERT(...)
#    else
#        define Debug_LOG_ASSERT(...)\
             Debug_LOG(Debug_LOG_LEVEL_ASSERT, " ASSERT", __VA_ARGS__)
#    endif

/* Debug_DUMP ----------------------------------------------------------------*/

#    if defined(Debug_Config_INCLUDE_LEVEL_IN_MSG)
#    define Debug_DUMP(LEVEL, LEVEL_STR, ...) \
            Debug_hexDump(LEVEL, LEVEL_STR ": " Debug_DUMP_MSG(__VA_ARGS__))
#    else
#    define Debug_DUMP(LEVEL, LEVEL_STR, ...) \
            Debug_hexDump(LEVEL, Debug_DUMP_MSG(__VA_ARGS__))
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_TRACE
#        define Debug_DUMP_TRACE(...)
#    else
#        define Debug_DUMP_TRACE(buf, len)\
             Debug_DUMP(Debug_LOG_LEVEL_TRACE, "  TRACE", buf, len)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_DEBUG
#        define Debug_DUMP_DEBUG(...)
#    else
#        define Debug_DUMP_DEBUG(buf, len)\
             Debug_DUMP(Debug_LOG_LEVEL_DEBUG, "  DEBUG", buf, len)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_INFO
#        define Debug_DUMP_INFO(...)
#    else
#        define Debug_DUMP_INFO(buf, len)\
             Debug_DUMP(Debug_LOG_LEVEL_INFO, "   INFO", buf, len)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_WARNING
#        define Debug_DUMP_WARNING(...)
#    else
#        define Debug_DUMP_WARNING(buf, len)\
             Debug_DUMP(Debug_LOG_LEVEL_WARNING, "WARNING", buf, len)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_ERROR
#        define Debug_DUMP_ERROR(...)
#    else
#        define Debug_DUMP_ERROR(buf, len)\
             Debug_DUMP(Debug_LOG_LEVEL_ERROR, "  ERROR", buf, len)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_FATAL
#        define Debug_DUMP_FATAL(...)
#    else
#        define Debug_DUMP_FATAL(buf, len)\
             Debug_DUMP(Debug_LOG_LEVEL_FATAL, "  FATAL", buf, len)
#    endif
#    if Debug_Config_LOG_LEVEL < Debug_LOG_LEVEL_ASSERT
#        define Debug_DUMP_ASSERT(...)
#    else
#        define Debug_DUMP_ASSERT(buf, len)\
             Debug_DUMP(Debug_LOG_LEVEL_ASSERT, " ASSERT", buf, len)
#    endif

#endif

/* Assert checks -------------------------------------------------------------*/

#define Debug_ASSERT_PRINTFLN(C__, ...) \
do\
{\
    if (!(C__)) \
    { \
        Debug_LOG_ASSERT(__VA_ARGS__); \
        Debug_ASSERT(false); \
    } \
}\
while(0)

#if defined(Debug_Config_ENABLE_ASSERT)

void
Debug_failedAssert();

#   define Debug_ASSERT(C__) \
    do \
    { \
        if (!(C__)) \
        { \
            Debug_failedAssert(); \
        } \
    } \
    while(0)

#elif defined(Debug_Config_STANDARD_ASSERT)

#   include <assert.h>
#   define Debug_ASSERT(C__) assert(C__)

#else // Asserts are disabled.

#   define Debug_ASSERT(C__)

#endif

// Checking if standard static asserts are available.
#if ((defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) \
        || (defined(__cplusplus) && (__cplusplus >= 201103L)))

#       define Debug_STATIC_ASSERT(_cond_) \
                static_assert(_cond_, "Debug_STATIC_ASSERT")

#else // Using non standard static assert.

#   define Debug_STATIC_ASSERT(_cond_) \
                typedef int assert_failed[(_cond_) ? 1 : -1]

#endif

#if defined (Debug_Config_ASSERT_SELF_PTR)
#   define Debug_ASSERT_SELF(self)  Debug_ASSERT(self != NULL);
#else
#   define Debug_ASSERT_SELF(self)
#endif

/* Exported functions ------------------------------------------------------- */

void
Debug_hexDump(
    int debugLvl,
    char* desc,
    const void* bytesToDump,
    size_t bytesCount);

///@}
