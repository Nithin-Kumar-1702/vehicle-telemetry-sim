#include<string.h>
#include"frame_parser.h"
#include "uart_rx.h"

int parse_byte(uint8_t byte, Frame *f)
{
    static States state = WAIT_START;
    static uint8_t expected_len;
    static uint8_t buf[RING_BUFFER_SIZE];
    static uint8_t count;

switch(state)
{
    case WAIT_START:
        if(byte == START_BYTE_VAL)
        state = READ_LENGTH;
        break;

    case READ_LENGTH:
        expected_len = byte;
        state = READ_PAYLOAD;
        count = 0;
        break;

    case READ_PAYLOAD:
        buf[count] = byte;
        count++;
        if(count == expected_len)
        {
            memcpy(&f->data, buf, expected_len);
            state = READ_CHECKSUM;
            return 1;
        }
        break;
    
    case READ_CHECKSUM:
        f->CheckSum = byte;
        state = WAIT_START;
        return 1;
        break;
}
    
    return 0;  
}
