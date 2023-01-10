#ifndef EMULATOR_IO_H
#define EMULATOR_IO_H

#include "EmulatorConfig.h"

// --- Macros ---

#if LOG_ERRORS
#define LOG_STATUS(X) log_status(X)
#else
#define LOG_STATUS(X)
#endif

#if NULL_CHECKS
#define HANDLE_NULL(X, RET)                 \
    if (X == NULL)                          \
    {                                       \
        LOG_STATUS(error_invalid_argument); \
        return RET;                         \
    }
#else
#define HANDLE_NULL(X, RET)
#endif

// --- Functions ---

// log_status : Logs status to console
void log_status(int status_code);

#endif