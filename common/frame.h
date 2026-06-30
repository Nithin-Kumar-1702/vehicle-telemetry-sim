#ifndef FRAME_H
#define FRAME_H

#include<stdint.h>

#define START_BYTE_VAL 0xAA

typedef struct Payload
{
    float ax,ay,az;

    float load;
} Payload;

typedef struct __attribute__((packed)) Frame
{
    uint8_t start_byte;
    uint8_t length;
    Payload data;
    uint8_t CheckSum;
} Frame;



#endif
