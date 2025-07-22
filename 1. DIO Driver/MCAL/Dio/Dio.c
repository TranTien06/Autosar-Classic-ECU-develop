#include "Dio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

// Mapping kênh DIO tới chân GPIO vật lý (ở đây ví dụ chỉ có LED tại PA5)
typedef struct {
    GPIO_TypeDef* port;
    uint16_t      pin;
} Dio_ChannelConfigType;

static const Dio_ChannelConfigType Dio_ChannelConfig[] = {
    // DIO_CHANNEL_LED:
    { GPIOA, GPIO_Pin_5 }
    // Thêm channel khác nếu có
};


// Viết giá trị ra chân DIO
void Dio_WriteChannel(Dio_ChannelType channel, Dio_LevelType level)
{
    GPIO_TypeDef* port = Dio_ChannelConfig[channel].port;
    uint16_t pin = Dio_ChannelConfig[channel].pin;

    if (level == DIO_PIN_SET) {
        GPIO_SetBits(port, pin);
    } else {
        GPIO_ResetBits(port, pin);
    }
}

// Đọc trạng thái chân DIO
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channel)
{
    GPIO_TypeDef* port = Dio_ChannelConfig[channel].port;
    uint16_t pin = Dio_ChannelConfig[channel].pin;

    return (GPIO_ReadInputDataBit(port, pin) ? DIO_PIN_SET : DIO_PIN_RESET);
}

// Đảo trạng thái chân DIO
void Dio_ToggleChannel(Dio_ChannelType channel)
{
    GPIO_TypeDef* port = Dio_ChannelConfig[channel].port;
    uint16_t pin = Dio_ChannelConfig[channel].pin;

    if (GPIO_ReadOutputDataBit(port, pin))
        GPIO_ResetBits(port, pin);
    else
        GPIO_SetBits(port, pin);
}
