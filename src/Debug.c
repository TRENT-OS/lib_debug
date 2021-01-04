/**
 * @copyright (C) 2020, HENSOLDT Cyber GmbH
 *
 * @brief Implemention of debug functionality is placed here.
 *
 */
#include "lib_debug/Debug.h"

#include <stdint.h>

#define CHAR_PER_BYTE       3
#define BYTES_PER_LINE      16
#define DUMP_LINE_LENGTH    ((CHAR_PER_BYTE * BYTES_PER_LINE) + 1)

void
Debug_hexDump(
    int debugLvl,
    const void* bytesToDump,
    size_t bytesCount)
{
    if (Debug_Config_LOG_LEVEL >= debugLvl)
    {
        return;
    }

    if (NULL == bytesToDump)
    {
        Debug_PRINTFLN("bytesToDump is NULL!");
        return;
    }

    if (0U == bytesCount)
    {
        Debug_PRINTFLN("No data to dump!");
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
            Debug_PRINTFLN("Byte to hex conversion error: "\
                           "CHAR_PER_BYTE = %d, charWritten = %d",
                           CHAR_PER_BYTE,
                           charWritten);
            return;
        }

        dumpLineCurrent += charWritten;

        const bool isNewLine = (((dumpPos + 1) % BYTES_PER_LINE) == 0);
        if (isNewLine)
        {
            Debug_PRINTFLN("%s", dumpLine);

            dumpLine[0] = '\0';
            dumpLineCurrent = dumpLine;
        }
    }

    if ('\0' != dumpLine[0])
    {
        Debug_PRINTFLN("%s", dumpLine);
    }
}
