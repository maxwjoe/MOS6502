#ifndef EMULATOR_IO_H
#define EMULATOR_IO_H

#include "EmulatorConfig.h"

#if LOG_ERRORS
#define LOG_STATUS(X) log_status(X)
#else
#define LOG_STATUS(X)
#endif

// log_status : Logs status to console
void log_status(int status_code);

#endif