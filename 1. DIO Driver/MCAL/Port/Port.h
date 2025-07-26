#include "Std_Types.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "gp_drive.h"
typedef uint8 Port_PinModeType;
#define PORT_PIN_MODE_GPIO        ((Port_PinModeType)0)

#define PORT_PIN_MODE_ADC1        ((Port_PinModeType)1)

typedef uint8 Port_PinOutSpeedType;
typedef uint8 Port_PinType;

#define PIN0 ((Port_PinType)0)
#define PIN1 ((Port_PinType)1)
#define PIN2 ((Port_PinType)2)
#define PIN3 ((Port_PinType)3)
#define PIN4 ((Port_PinType)4)
#define PIN5 ((Port_PinType)5)
#define PIN6 ((Port_PinType)6)
#define PIN7 ((Port_PinType)7)
#define PIN8 ((Port_PinType)8)
#define PIN9 ((Port_PinType)9)
#define PIN10 ((Port_PinType)10)
#define PIN11 ((Port_PinType)11)
#define PIN12 ((Port_PinType)12)
#define PIN13 ((Port_PinType)13)
#define PIN14 ((Port_PinType)14)
#define PIN15 ((Port_PinType)15)



#define LED13       ((Port_PinType)45) //portc pin 13


/*#define PA 1
#define PB 2
#define PC 3*/


/*#define OUT10 	    ((Port_PinOutSpeedType)1)
#define OUT2	 	((Port_PinOutSpeedType)2)
#define OUT50 	    ((Port_PinOutSpeedType)3)*/



#define PORT_GET_PIN(PinNum) \
(1 << ((PinNum)))

static inline GPIO_TypeDef* PORT_GET_PORTID(uint8 PortNum)
{
    switch (PortNum)
    {
        case 1: return GPIOA;
        case 2: return GPIOB;
        case 3: return GPIOC;
        case 4: return GPIOD;
        default:        return NULL_PTR;
    }
}



typedef enum {
    PORT_PIN_IN, // = 0 la ngo vao
    PORT_PIN_OUT // = 1 la ngo ra
} Port_PinDirectionType; 

typedef enum {
    PORT_NO_PULL, //= 0
    PORT_PULL_UP, //= 1 
    PORT_PULL_DOWN // = 2 
} Port_InternalResistor;

typedef struct
{
    uint8 PortNum;                // Số hiệu port (A=0, B=1,...)
    Port_PinType PinNum;
    Port_PinDirectionType Direction;      // INPUT hoặc OUTPUT
    Port_PinModeType Mode;        // GPIO hoặc alternative function hoac la ADC, 
    //boolean directionChangeable;    // TRUE/FALSE: cho phép đổi hướng lúc runtime
    //boolean modeChangeable;         // TRUE/FALSE: cho phép đổi mode lúc runtime
    Port_InternalResistor pull;           // NoPull, PullUp, PullDown

    Port_PinOutSpeedType OutputSpeed;                    // LOW, MEDIUM, HIGH (nếu OUTPUT)
    uint8 AlternateFunction;              // AF số, nếu dùng AF gia tri 1 hoac 0


} Port_ConfigType;
void Port_SetPinDirection (Port_PinType Pin, Port_PinDirectionType Direction);// during run time
void Port_Init (const Port_ConfigType* ConfigPtr);
//void Port_RefreshPortDirection (void);
//void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode); // during runtime
