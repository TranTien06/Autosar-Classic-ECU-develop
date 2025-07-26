#include "Dio.h"



static inline GPIO_TypeDef* DIO_GET_PORT(uint8 ChannelId)
{
    if (ChannelId < 16) return GPIOA;
    else if (ChannelId < 32) return GPIOB;
    else if (ChannelId < 48) return GPIOC;
    else if (ChannelId < 64) return GPIOD;
    else return NULL_PTR;
}
static inline GPIO_TypeDef* DIO_GET_PORTID(Dio_PortType PortId)
{
    switch (PortId)
    {
        case DIO_PORTA: return GPIOA;
        case DIO_PORTB: return GPIOB;
        case DIO_PORTC: return GPIOC;
        case DIO_PORTD: return GPIOD;
        default:        return NULL_PTR;
    }
}

/* Đọc dữ liệu tai channelId đó  */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId) {
    GPIO_TypeDef *GPIO_Port;
    uint16_t GPIO_Pin;
    GPIO_Port = DIO_GET_PORT(ChannelId);

    if(GPIO_Port == NULL_PTR)
    {
        return STD_LOW;
    }
    GPIO_Pin = DIO_GET_PIN(ChannelId);
    if(GPIO_ReadInputDataBit(GPIO_Port,GPIO_Pin) == Bit_SET)
    {
    return STD_HIGH;
    }
    else 
    {
    return STD_LOW;
    }
}
/* ghhi dữ mức cao hoặc mức thấp ra channelId*/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level) {
    GPIO_TypeDef *GPIO_Port;
    uint16_t GPIO_Pin;
    GPIO_Port = DIO_GET_PORT(ChannelId);
    if(GPIO_Port == NULL_PTR)
    {if(GPIO_Port == NULL_PTR)
    {
        return STD_LOW; // khong xác định được thoát khỏi hàm 
    }
        return STD_LOW; // khong xác định được thoát khỏi hàm 
    }
    GPIO_Pin = DIO_GET_PIN(ChannelId);
    if(Level == STD_HIGH)
    {
        GPIO_SetBits(GPIO_Port, GPIO_Pin);
    }
    else
    {
        GPIO_ResetBits(GPIO_Port, GPIO_Pin);
    }
}
/*Đảo bit tại channelId đó */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId) {
    GPIO_TypeDef *GPIO_Port;
    uint16_t GPIO_Pin;
    GPIO_Port = DIO_GET_PORT(ChannelId);    
    if(GPIO_Port == NULL_PTR)
    {
        return 0; // trả về 0 khi khong xac dinh 
    }   
    if(Dio_ReadChannel(ChannelId))
    {
        Dio_WriteChannel(ChannelId, STD_LOW);
        return STD_LOW;
    }
    else
    {
        Dio_WriteChannel(ChannelId, STD_HIGH);
        return STD_HIGH;
    }  
}
/*Đọc 1 lan 16 chân của 1 port*/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId) {
    GPIO_TypeDef *GPIO_Port;
    GPIO_Port = DIO_GET_PORTID(PortId);
    if(GPIO_Port == NULL_PTR)
    {
        return 0; // trả về 0 khi khong xac dinh 
    }
    return(GPIO_ReadInputData(GPIO_Port));

}
/*ghi du lieu ra 16 chan cua 1 port*/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level) {
    GPIO_TypeDef *GPIO_Port;
    GPIO_Port = DIO_GET_PORTID(PortId);
    if(GPIO_Port == NULL_PTR)
    {
        return; // khong xác định được thoát khỏi hàm 
    }
    GPIO_Write(GPIO_Port, Level);
}
/*Đọc dữ liệu nhiều PIN liền kề trên cùng 1 port*/
Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr) 
{
    GPIO_TypeDef *GPIO_Port;
    Dio_PortLevelType PortLevel;
    GPIO_Port = DIO_GET_PORTID(ChannelGroupIdPtr->port);
    if(GPIO_Port == NULL_PTR)
    {
        return 0; // khong xác định được thoát khỏi hàm 
    }
    PortLevel =  GPIO_ReadInputData(GPIO_Port);
    PortLevel = (PortLevel & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset;
    return PortLevel;
}
/*Ghi du lieu ra nhieu PIN gần nhau trên 1 port*/
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level)
{
    GPIO_TypeDef *GPIO_Port;
    GPIO_Port = DIO_GET_PORTID(ChannelGroupIdPtr->port);
    if(GPIO_Port == NULL_PTR)
    {
        return; // khong xác định được thoát khỏi hàm 
    }
    GPIO_Write(GPIO_Port, Level);
}
void Dio_MaskedWritePort (Dio_PortType PortId,Dio_PortLevelType Level,Dio_PortLevelType Mask)
{
    GPIO_TypeDef *GPIO_Port;
    GPIO_Port = DIO_GET_PORTID(PortId);
    if(GPIO_Port == NULL_PTR)
    {
        return; // khong xác định được thoát khỏi hàm 
    }
    Dio_PortLevelType currentValue = GPIO_ReadOutputData(GPIO_Port);
    Dio_PortLevelType newValue = (currentValue & (~Mask)) | (Level & Mask); // Ghi đúng bit trong mask
    GPIO_Write(GPIO_Port, newValue); // Ghi lại cả cảng với dữ liệu mới
}

