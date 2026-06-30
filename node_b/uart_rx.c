#include"uart_rx.h"

void uart_rx_init(ring_buffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;

}

int rx_byte_available(ring_buffer *rb)
{
    return rb->count;

}

int get_rx_byte(ring_buffer *rb)
{
    uint8_t byte;

    if(rb->count == 0)
    return -1;
    else
    {
        byte = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
        rb->count--;
        return byte;

    }

}

void uart_rx_push(ring_buffer *rb, uint8_t byte)
{
        rb->buffer[rb->head] = byte;
        rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
        rb->count++;

}
