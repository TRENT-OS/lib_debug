/*
 * Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "lib_debug/Debug.h"

#include <stdint.h>
#include <assert.h>

#define CHAR_PER_BYTE       3
#define BYTES_PER_LINE      16
#define DUMP_LINE_LENGTH    ((CHAR_PER_BYTE * BYTES_PER_LINE) + 1)

// Implementation details needed to use -fstack-protector

// value to be used as a stack cannary
#if UINTPTR_MAX == UINT32_MAX
const uintptr_t __stack_chk_guard = 0xdeadbeef;
#elif UINTPTR_MAX == UINT64_MAX
const uintptr_t __stack_chk_guard = 0xdeadbeefdeadbeef;
#else
#error "Unsupported platform"
#endif

// When compiling with -fstack-protector, __stack_chk_fail() will be called
// when stack corruption is detected. This function will never return.
// A description of this feature can be found here
// https://www.keil.com/support/man/docs/armclang_ref/armclang_ref_cjh1548250046139.htm
// Even if it is tailored to the ARM GCC, the high level parts apply also 
// to the mainline compiler.
void
__stack_chk_fail(void)
{
    Debug_LOG_FATAL("Stack corruption detected! Aborting.\n");
    assert(0);
// TODO: Replace assert with something that stops all threads in the
//       component (control, rpc) and works in release builds.
}

void
Debug_hexDump(
    int debugLvl,
    char* desc,
    const void* bytesToDump,
    size_t bytesCount)
{
    if (Debug_Config_LOG_LEVEL < debugLvl)
    {
        return;
    }

    if (NULL == bytesToDump)
    {
        Debug_LOG_ERROR("bytesToDump is NULL!");
        return;
    }

    if (0U == bytesCount)
    {
        Debug_LOG_WARNING("No data to dump!");
        return;
    }

    // Buffer needs space for the terminating NULL so that is why '+1'.
    char  dumpLine[DUMP_LINE_LENGTH];
    char* dumpLineCurrent = dumpLine;
    char const* const dumpLineEnd = &dumpLine[DUMP_LINE_LENGTH];

    for (size_t dumpPos = 0; dumpPos < bytesCount; ++dumpPos)
    {
        const int charWritten = snprintf(
                                    dumpLineCurrent,
                                    dumpLineEnd - dumpLineCurrent,
                                    "%02X ",
                                    ((uint8_t*)bytesToDump)[dumpPos]);

        if (CHAR_PER_BYTE != charWritten)
        {
            Debug_LOG_ASSERT("Byte to hex conversion error: "\
                             "CHAR_PER_BYTE = %d, charWritten = %d",
                             CHAR_PER_BYTE,
                             charWritten);
            return;
        }

        dumpLineCurrent += charWritten;

        const bool isNewLine = (((dumpPos + 1) % BYTES_PER_LINE) == 0);
        if (isNewLine)
        {
            Debug_PRINT(debugLvl, "%s%s", desc, dumpLine);

            dumpLine[0] = '\0';
            dumpLineCurrent = dumpLine;
        }
    }

    if ('\0' != dumpLine[0])
    {
        Debug_PRINT(debugLvl, "%s%s", desc, dumpLine);
    }
}
