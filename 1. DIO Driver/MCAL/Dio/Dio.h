#ifndef DIO_H
#define DIO_H

#include "Std_Types.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define DIO_PORTA   ((Dio_PortType)0)
#define DIO_PORTB   ((Dio_PortType)1)
#define DIO_PORTC   ((Dio_PortType)2)
#define DIO_PORTD   ((Dio_PortType)3)

#define PORTA_PIN0  ((Dio_ChannelType)0)
#define PORTA_PIN1  ((Dio_ChannelType)1)
#define PORTA_PIN2  ((Dio_ChannelType)2)
#define PORTA_PIN3  ((Dio_ChannelType)3)
#define PORTA_PIN4  ((Dio_ChannelType)4)
#define PORTA_PIN5  ((Dio_ChannelType)5)
#define PORTA_PIN6  ((Dio_ChannelType)6)
#define PORTA_PIN7  ((Dio_ChannelType)7)
#define PORTA_PIN8  ((Dio_ChannelType)8)
#define PORTA_PIN9  ((Dio_ChannelType)9)
#define PORTA_PIN10  ((Dio_ChannelType)10)
#define PORTA_PIN11  ((Dio_ChannelType)11)
#define PORTA_PIN12  ((Dio_ChannelType)12)
#define PORTA_PIN13  ((Dio_ChannelType)13)
#define PORTA_PIN14  ((Dio_ChannelType)14)
#define PORTA_PIN15  ((Dio_ChannelType)15)
#define PORTB_PIN0  ((Dio_ChannelType)16)
#define PORTB_PIN1  ((Dio_ChannelType)17)
#define PORTB_PIN2  ((Dio_ChannelType)18)
#define PORTB_PIN3  ((Dio_ChannelType)19)
#define PORTB_PIN4  ((Dio_ChannelType)20)
#define PORTB_PIN5  ((Dio_ChannelType)21)
#define PORTB_PIN6  ((Dio_ChannelType)22)
#define PORTB_PIN7  ((Dio_ChannelType)23)
#define PORTB_PIN8  ((Dio_ChannelType)24)
#define PORTB_PIN9  ((Dio_ChannelType)25)
#define PORTB_PIN10  ((Dio_ChannelType)26)
#define PORTB_PIN11  ((Dio_ChannelType)27)
#define PORTB_PIN12  ((Dio_ChannelType)28)
#define PORTB_PIN13  ((Dio_ChannelType)29)
#define PORTB_PIN14  ((Dio_ChannelType)30)
#define PORTB_PIN15  ((Dio_ChannelType)31)
#define PORTC_PIN0  ((Dio_ChannelType)32)
#define PORTC_PIN1  ((Dio_ChannelType)33)
#define PORTC_PIN2  ((Dio_ChannelType)34)
#define PORTC_PIN3  ((Dio_ChannelType)35)
#define PORTC_PIN4  ((Dio_ChannelType)36)
#define PORTC_PIN5  ((Dio_ChannelType)37)
#define PORTC_PIN6  ((Dio_ChannelType)38)
#define PORTC_PIN7  ((Dio_ChannelType)39)
#define PORTC_PIN8  ((Dio_ChannelType)40)
#define PORTC_PIN9  ((Dio_ChannelType)41)
#define PORTC_PIN10  ((Dio_ChannelType)42)
#define PORTC_PIN11  ((Dio_ChannelType)43)
#define PORTC_PIN12  ((Dio_ChannelType)44)
#define PORTC_PIN13  ((Dio_ChannelType)45)
#define PORTC_PIN14  ((Dio_ChannelType)46)
#define PORTC_PIN15  ((Dio_ChannelType)47)



typedef uint8 Dio_ChannelType; // day la dinh danh cho 1 chan pins cu the
typedef uint8 Dio_LevelType; // dinh nghia muc dien ap cua chan
    /* 
    có 2 giá tri: STD_LOW, STD_HIGH
    */
typedef uint8 Dio_PortType; // phan biet cac port vs nhau   
typedef uint16 Dio_PortLevelType; // dai dien cho dien ap cua 16 chan 
    /*
    kieu du lieu bao quat het tat ca cac pin trong port (gia tri dien ap)
    phai dinh nghia cho 1 cai port dai nhat neu 32bit thi phai dinh nghia 32
    */

typedef struct
{
    uint8 mask; // dinh nghia vi tri cua Channel Group (chon nhung cai chan)
    uint8 offset; //vi tri cua channel group tu vi tri thap nhat
    Dio_PortType port; // port ma channel group muon difine
} Dio_ChannelGroupType; // nhóm chân gpio de lam viec


/* APIs chuẩn AUTOSAR */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
    /*
        tra ve STD_LOW, STD HIGH, tham so truyen vao la 1 ID nao do (0)
    */
Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr) ;// r
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);//
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);//
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);//
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level);
void Dio_MaskedWritePort (Dio_PortType PortId,Dio_PortLevelType Level,Dio_PortLevelType Mask);
/*Macro xac dinh cong GPIO du tren channel ID */
#define DIO_GET_PIN(ChannelId) \
(1 << ((ChannelId)%16))
// o đâu có chữ DIO_GET_PIN(ChannelID) thì thay bằng (1<<((ChannelId)%16))

#endif /* DIO_H */