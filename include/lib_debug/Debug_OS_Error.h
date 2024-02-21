/*
 * Copyright (C) 2021-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

/**
 * @addtogroup lib_debug
 * @{
 *
 * @file Debug_OS_Error.h
 *
 * @brief Debugging facility to handle OS Errors
 */

#pragma once

#include "OS_Error.h"

const char*
Debug_OS_Error_toString(
    OS_Error_t err);

///@}
