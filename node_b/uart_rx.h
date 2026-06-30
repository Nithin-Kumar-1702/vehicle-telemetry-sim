#ifndef UART_RX_H
#define UART_RX_H
#include<stdint.h>

#define RING_BUFFER_SIZE 256

typedef struct ring_buffer
{
    uint8_t buffer[RING_BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} ring_buffer;

void uart_rx_init(ring_buffer *);
int rx_byte_available(ring_buffer *);
int get_rx_byte(ring_buffer *);
void uart_rx_push(ring_buffer *rb, uint8_t byte);

#endif
