#ifndef _STATUS_H
#define _STATUS_H

#include <stdint.h>

typedef enum {
    STATUS_OK = 0x00U,
    STATUS_ERROR = 0x01U,
    STATUS_INVALID_PARAM = 0x02U,
    STATUS_TIMEOUT = 0x03U
} STATUS_CODE;

#endif // _STATUS_H