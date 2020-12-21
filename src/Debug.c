/*
 * Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "lib_debug/Debug.h"

#include <stdint.h>

#define CHAR_PER_BYTE       3
#define BYTES_PER_LINE      16
#define DUMP_LINE_LENGTH    ((CHAR_PER_BYTE * BYTES_PER_LINE) + 1)

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

    size_t line_bytes = 0;
    for (size_t dumpPos = 0; dumpPos < bytesCount; dumpPos++)
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

        if (++line_bytes == BYTES_PER_LINE)
        {
            Debug_PRINT(
                debugLvl,
                "%s 0x%04x: %s",
                desc,
                dumpPos + 1 - line_bytes,
                dumpLine);

            line_bytes = 0;
            dumpLine[0] = '\0';
            dumpLineCurrent = dumpLine;
        }
    }

    if (0 != line_bytes)
    {
        Debug_PRINT(
            debugLvl,
            "%s 0x%04x: %s",
            desc,
            bytesCount - line_bytes,
            dumpLine);
    }
}
