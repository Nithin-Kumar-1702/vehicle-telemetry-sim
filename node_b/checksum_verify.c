#include"checksum_verify.h"
#include"checksum.h"
#include<stdio.h>


int verify_frame(Frame *f, uint32_t *err_count)
{
    uint8_t calculated = compute_checksum((uint8_t*)&f->data, sizeof(Payload));
    
    //printf("calculated: 0x%02X, received: 0x%02X\n", calculated, f->CheckSum);

    if (calculated == f->CheckSum)
    return 1;
    else 
    {
        (*err_count)++;
        return 0;
    }
}
