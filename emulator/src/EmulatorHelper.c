#include "EmulatorHelper.h"
#include "EmulatorTypes.h"

#include "stdio.h"

void log_status(int status_code)
{
    switch (status_code)
    {
    case ok:
        printf("STATUS : Success\n");
        break;
    case error_generic:
        LOG_ERR_MSG("Generic Error");
        break;
    case error_create:
        LOG_ERR_MSG("Create Error");
        break;
    case error_read:
        LOG_ERR_MSG("Read Error");
        break;
    case error_write:
        LOG_ERR_MSG("Write Error");
        break;
    case error_invalid_argument:
        LOG_ERR_MSG("Invalid Argument Passed");
        break;
    case error_null_deref:
        LOG_ERR_MSG("Null Dereference Occurred");
        break;
    case error_file_io:
        LOG_ERR_MSG("File IO Error");
        break;
    case error_free:
        LOG_ERR_MSG("Failed to free memory");
        break;
    case error_invalid_op_code:
        LOG_ERR_MSG("Unhandled CPU Operation");
        break;
    default:
        LOG_ERR_MSG("Unknown Status Code");
    }
}
