#include"imu_sensor.h"

int read_imu(Payload *p)
{
    p->ax = 0;
    p->ay = 0;
    p->az = 9.8;

    return 0;
}
