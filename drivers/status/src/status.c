#include "status.h"

const char* StatusCodeToString(STATUS_CODE status) {
    switch (status) {
        case STATUS_OK:
            return "OK";
        case STATUS_ERROR:
            return "ERROR";
        case STATUS_INVALID_PARAM:
            return "INVALID PARAMETER";
        case STATUS_TIMEOUT:
            return "TIMEOUT";
        default:
            return "UNKNOWN STATUS";
    }
}