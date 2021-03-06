#include "logger/logger.h"
#include "index.h"
#include "lora_uart/lora_uart_server.h"
int glob_fd;
void tmp_cb(void)
{
    printf("in the tmp_cb function\n");
    int num = 0;
    num = serialDataAvail(glob_fd);
    if (num < 1)
    {
        return;
    }

    printf("Maxx : receive %d bytes\n", num);

    while (serialDataAvail(glob_fd))
    {
        printf("receive %X\n", serialGetchar(glob_fd));
    }
}
void lora_server_example()
{

    auto server_ptr = lora_uart_server::instance();

    if (!server_ptr->init())
    {
        __LOG(error, "lora server init fail");
        return;
    }
    else
    {
        __LOG(debug, "lora server init success!");
    }

    while (1)
    {
        
        delay(100);
        __LOG(debug, "running.....");
#if 0
        printf("receive %X\n", serialGetchar(glob_fd));
#endif

        printf("now send message\n");
        char tmp_buf[10] = {'A', 'B', 'C'};
        server_ptr->send(tmp_buf, 3, 0x00, 0x1, 1);
    }
}

void lora_client_example()
{
    lora_uart lora(0x00, 0x01, 1);
    lora.set_low_power_call_back(tmp_cb);
    if (lora.init())
    {
    }
    else
    {
        printf("lora init fail!");
    }
    glob_fd = lora.get_fd();
    delay(1000000000);
#if 0
    while (1)
    {
        delay(100);
        while (serialDataAvail(glob_fd))
        {

            printf("................");
            printf("receive %c\n", serialGetchar(glob_fd));
        }
    }


    while (1)
    {
        delay(1000);
        printf(".");
        //printf("receive %X\n", serialGetchar(lora.getfd()));
    }
#endif
}