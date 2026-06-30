#include"frame_builder.h"
#include"checksum.h"

int build_frame(Payload *p, Frame *f)
{
    f->start_byte = START_BYTE_VAL;
    f->length = sizeof(Payload);
    f->data = *p;
    f->CheckSum = compute_checksum((uint8_t *)&f->data, f->length);

    return 0;

}
