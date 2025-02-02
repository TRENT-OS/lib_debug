/*
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "lib_debug/Debug.h"

#include <stdint.h>

#define CHAR_PER_BYTE       3
#define BYTES_PER_LINE      16

// Length of the dump line (excluding null terminator).
#define DUMP_LINE_LEN       (CHAR_PER_BYTE * BYTES_PER_LINE)

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
    char  dumpLine[DUMP_LINE_LEN + 1];
    char* dumpLineCurrent = dumpLine;
    char const* const dumpLineEnd = &dumpLine[DUMP_LINE_LEN + 1];

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
