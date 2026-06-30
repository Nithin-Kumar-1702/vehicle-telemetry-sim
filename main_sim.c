#include<stdio.h>
#include<unistd.h>
#include"checksum.h"
#include"frame_builder.h"
#include"imu_sensor.h"
#include"load_sensor.h"
#include"checksum_verify.h"
#include"frame_parser.h"
#include"uart_rx.h"
#include"frame.h"


int main()
{
    int pipefd[2];
    pipe(pipefd);
   
    pid_t pid = fork();

    if(pid == 0)
    {
        // Node A 
        close(pipefd[0]);
        Payload p;
        Frame f;
        while(1)
        {
            read_imu(&p);
            read_load(&p);
            build_frame(&p, &f);
            write(pipefd[1], &f, sizeof(Frame));
            usleep(200000);
        }
    }
    else
    {
        // Node B
        close(pipefd[1]);
        ring_buffer rb; 
        Frame f; 
        uint32_t err_count = 0;
        uart_rx_init(&rb);
        while(1)
        {
            uint8_t byte;
            read(pipefd[0], &byte, 1);
            uart_rx_push(&rb, byte);
            int b = get_rx_byte(&rb);
            if(parse_byte(b, &f) == 1)
            {
               if(verify_frame(&f, &err_count) == 1)  
                    printf("valid frame received\n");
               else
                    printf("corrupted! error count: %d\n", err_count);

            }
            
        }
    }

}
