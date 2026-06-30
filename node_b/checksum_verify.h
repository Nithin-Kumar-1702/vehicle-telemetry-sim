#ifndef CHECKSUM_VERIFY_H
#define CHECKSUM_VERIFY_H

#include"frame.h"
#include<stdint.h>

int verify_frame(Frame *f, uint32_t *err_count);

#endif
