#ifndef FRAME_PARSER_H
#define FRAME_PARSER_H

#include"frame.h"

typedef enum {

    WAIT_START,
    READ_LENGTH,
    READ_PAYLOAD,
    READ_CHECKSUM

} States;

int parse_byte(uint8_t byte, Frame *f);


#endif
