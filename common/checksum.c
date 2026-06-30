#include"checksum.h"

uint8_t compute_checksum(uint8_t *data, uint8_t len)
{
    uint8_t accumalator = 0,i=0;
    for(i=0; i<len; i++)
    accumalator = accumalator ^ data[i];

    return accumalator;

}

