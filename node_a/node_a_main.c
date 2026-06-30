#include<unistd.h>
#include<stdio.h>
#include"imu_sensor.h"
#include"load_sensor.h"
#include"frame_builder.h"

Payload p;
Frame f;

int main()
{
    while(1)
    {
    read_imu(&p);
    read_load(&p);
    build_frame(&p, &f);
     for (size_t i = 0; i < sizeof(Frame); i++) {
      printf("Byte %zu: 0x%02X\n", i, ((uint8_t*)&f)[i]);
    }

    usleep(200000);
    }

}
