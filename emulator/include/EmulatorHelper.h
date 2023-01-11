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

// LOG_WARN_MSG : Logs a warning to the console
#define LOG_WARN_MSG(X) printf("WARNING : %s\n", X);

// LOG_ERR_MSG : Logs an error to the console
#define LOG_ERR_MSG(X) printf("ERROR : %s\n", X)

// --- Functions ---

// log_status : Logs status to console
void log_status(int status_code);

#endif