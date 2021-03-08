/*
 * Copyright (C) 2021, HENSOLDT Cyber GmbH
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "OS_Error.h"
#include "lib_debug/Debug_OS_Error.h"
#include "lib_debug/Debug.h"

/*
 * If one of the following assert fails it means that OS_Error.h has been
 * changed without updating this file. A change in Debug_OS_Error_toString()
 * and in the following asserts might be required.
 */
Debug_STATIC_ASSERT(__START_OS_ERROR_CODES_NETWORK  == -1318);
Debug_STATIC_ASSERT(__START_OS_ERROR_CODES_DEVICE   == -1204);
Debug_STATIC_ASSERT(__START_OS_ERROR_CODES_FS       == -1124);
Debug_STATIC_ASSERT(__START_OS_ERROR_CODES_CONFIG   == -1004);
Debug_STATIC_ASSERT(__START_OS_ERROR_CODES_GENERIC  == -27);

const char*
Debug_OS_Error_toString(
    OS_Error_t err)
{
#define CASE_OS_ERR_STR(_code_)  case OS_ERROR_ ## _code_: return "OS_ERROR_"#_code_

    switch (err)
    {
    CASE_OS_ERR_STR(NETWORK_NO_SUPPORT);
    CASE_OS_ERR_STR(NETWORK_OP_NO_SUPPORT);
    CASE_OS_ERR_STR(NETWORK_DOWN);
    CASE_OS_ERR_STR(NETWORK_UNREACHABLE);
    CASE_OS_ERR_STR(NETWORK_NO_ROUTE);

    CASE_OS_ERR_STR(NETWORK_PROTO);
    CASE_OS_ERR_STR(NETWORK_PROTO_NO_SUPPORT);
    CASE_OS_ERR_STR(NETWORK_PROTO_OPT_NO_SUPPORT);

    CASE_OS_ERR_STR(NETWORK_ADDR_IN_USE);
    CASE_OS_ERR_STR(NETWORK_ADDR_NOT_AVAILABLE);

    CASE_OS_ERR_STR(NETWORK_CONN_RESET);
    CASE_OS_ERR_STR(NETWORK_CONN_ALREADY_BOUND);
    CASE_OS_ERR_STR(NETWORK_CONN_NONE);
    CASE_OS_ERR_STR(NETWORK_CONN_SHUTDOWN);
    CASE_OS_ERR_STR(NETWORK_CONN_REFUSED);

    CASE_OS_ERR_STR(NETWORK_HOST_DOWN);
    CASE_OS_ERR_STR(NETWORK_HOST_UNREACHABLE);
    //--------------------------------------------------------------------------
    // Device specific error codes
    //--------------------------------------------------------------------------
    CASE_OS_ERR_STR(DEVICE_INVALID);
    CASE_OS_ERR_STR(DEVICE_NOT_PRESENT);
    CASE_OS_ERR_STR(DEVICE_BUSY);
    //--------------------------------------------------------------------------
    // File System specific error codes
    //--------------------------------------------------------------------------
    CASE_OS_ERR_STR(FS_NO_FREE_HANDLE);
    CASE_OS_ERR_STR(FS_DELETE_HANDLE);
    CASE_OS_ERR_STR(FS_NO_DISK);
    CASE_OS_ERR_STR(FS_INIT);
    CASE_OS_ERR_STR(FS_REGISTER);
    CASE_OS_ERR_STR(FS_CREATE_FS);
    CASE_OS_ERR_STR(FS_FORMAT_FS);
    CASE_OS_ERR_STR(FS_PARTITION_READ);
    CASE_OS_ERR_STR(FS_OPEN);
    CASE_OS_ERR_STR(FS_CLOSE);
    CASE_OS_ERR_STR(FS_MOUNT);
    CASE_OS_ERR_STR(FS_UNMOUNT);
    CASE_OS_ERR_STR(FS_FILE_NOT_FOUND);
    CASE_OS_ERR_STR(FS_OPERATION_DENIED);
    CASE_OS_ERR_STR(FS_INSUFFICIENT_STORAGE_CAPACITY);
    CASE_OS_ERR_STR(FS_STRUCTURE);
    CASE_OS_ERR_STR(FS_RESOLVE_HANDLE);
    CASE_OS_ERR_STR(FS_DELETE_RESOLVE_HANDLE);
    CASE_OS_ERR_STR(FS_LIB);
    CASE_OS_ERR_STR(FS_DATABUFFER_OVERLOW);
    CASE_OS_ERR_STR(FS_INVALID_PARTITION_MODE);
    CASE_OS_ERR_STR(FS_PARTITION_NOT_READY);
    CASE_OS_ERR_STR(FS_INVALID_FILESYSTEM);
    //--------------------------------------------------------------------------
    // Configuration Server specific error codes
    //--------------------------------------------------------------------------
    CASE_OS_ERR_STR(CONFIG_DOMAIN_NOT_FOUND);
    CASE_OS_ERR_STR(CONFIG_PARAMETER_NOT_FOUND);
    CASE_OS_ERR_STR(CONFIG_TYPE_MISMATCH);
    //--------------------------------------------------------------------------
    // General error codes
    //--------------------------------------------------------------------------
    CASE_OS_ERR_STR(IN_PROGRESS);
    CASE_OS_ERR_STR(TIMEOUT);
    CASE_OS_ERR_STR(IO);
    CASE_OS_ERR_STR(EXISTS);
    CASE_OS_ERR_STR(BUFFER_FULL);
    CASE_OS_ERR_STR(BUFFER_EMPTY);
    CASE_OS_ERR_STR(NO_DATA);
    CASE_OS_ERR_STR(NOT_INITIALIZED);
    CASE_OS_ERR_STR(TRY_AGAIN);
    CASE_OS_ERR_STR(WOULD_BLOCK);
    CASE_OS_ERR_STR(OUT_OF_BOUNDS);
    CASE_OS_ERR_STR(CONNECTION_CLOSED);
    CASE_OS_ERR_STR(OVERFLOW_DETECTED);
    CASE_OS_ERR_STR(INSUFFICIENT_SPACE);
    CASE_OS_ERR_STR(BUFFER_TOO_SMALL);
    CASE_OS_ERR_STR(ABORTED);
    CASE_OS_ERR_STR(OPERATION_DENIED);
    CASE_OS_ERR_STR(ACCESS_DENIED);
    CASE_OS_ERR_STR(NOT_FOUND);
    CASE_OS_ERR_STR(INVALID_HANDLE);
    CASE_OS_ERR_STR(INVALID_NAME);
    CASE_OS_ERR_STR(INVALID_PARAMETER);
    CASE_OS_ERR_STR(INVALID_STATE);
    CASE_OS_ERR_STR(NOT_SUPPORTED);
    CASE_OS_ERR_STR(NOT_IMPLEMENTED);
    CASE_OS_ERR_STR(GENERIC);

    case OS_SUCCESS:
        return "OS_SUCCESS";

    default:
        break;
    }
    return "OS_ERROR_???";
}
