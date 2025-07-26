#include "Port.h"
#include "Dio.h"

void delay(volatile uint32_t t)
{
    while (t--) __asm__("nop");
}

int main(void)
{
    Port_Init();     // Khởi tạo mode các chân (trước)

    for (int i = 0; i < 10; i++)
    {
        Dio_ToggleChannel(DIO_CHANNEL_LED);
        delay(500000);
        Dio_ToggleChannel(DIO_CHANNEL_LED);
        delay(500000);
    }

    // Sau khi nhấp nháy 10 lần, có thể tắt LED hoặc dừng chương trình
    // Dio_WriteChannel(DIO_CHANNEL_LED, STD_LOW);

    while (1); // Dừng chương trình tại đây
}
