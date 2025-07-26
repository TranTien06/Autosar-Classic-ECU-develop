#include "Port.h"
void Port_Init (const Port_ConfigType* ConfigPtr)
{   
        GPIO_TypeDef *GPIO_Port;
        GPIO_Port = PORT_GET_PORTID(ConfigPtr->PortNum);
        switch (ConfigPtr->PortNum)
        {
        case 1:
            RCC_APB2ENR |= 4;
            break;
        case 2:
            RCC_APB2ENR |= (1<<3);
            break;
        case 3:
            RCC_APB2ENR |= (1<<4);
            break;    
        default:
            break;
        }

    if(ConfigPtr->Mode == PORT_PIN_MODE_GPIO)
    {   
        if(ConfigPtr->AlternateFunction)
        {
            RCC->APB2ENR |= 1;
        }
        switch(ConfigPtr->Direction)
        {
            volatile unsigned long * ODR;
            unsigned long offset = 0x03; 
            ODR = (volatile unsigned long * )(&GPIO_Port);
            
            case PORT_PIN_IN:
                if(ConfigPtr->pull == PORT_NO_PULL)
                {
                        init_GP(ConfigPtr->PortNum,ConfigPtr->PinNum,PORT_PIN_IN,I_F);
                }
                else if(ConfigPtr->pull == PORT_PULL_UP)
                {
                    init_GP(ConfigPtr->PortNum,ConfigPtr->PinNum,PORT_PIN_IN,I_PP);
                    *ODR |= (1 << ConfigPtr->PinNum);
                }
                else if(ConfigPtr->pull == PORT_PULL_DOWN)
                {
                    init_GP(ConfigPtr->PortNum,ConfigPtr->PinNum,PORT_PIN_IN,I_PP);
                    *ODR &= ~(1 << ConfigPtr->PinNum);
                }
                break;
            case PORT_PIN_OUT:
                if(ConfigPtr->AlternateFunction)
                {
                    init_GP(ConfigPtr->PortNum,ConfigPtr->PinNum,ConfigPtr->OutputSpeed,O_AF_PP);
                }
                else
                {
                    init_GP(ConfigPtr->PortNum,ConfigPtr->PinNum,ConfigPtr->OutputSpeed,O_GP_PP);
                }
                break;
            default: break;
        }

    }
    else if(ConfigPtr->Mode == PORT_PIN_MODE_ADC1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;    
        if((ConfigPtr->PortNum == PA)&&((ConfigPtr->PinNum >= PIN0 && ConfigPtr->PinNum <= PIN10)))
        {
            GPIOA->CRL &= ~(0xF << ConfigPtr->PinNum); // cau hình cho ngo vao che do ADC
        } 
        else if((ConfigPtr->PortNum == PB)&&((ConfigPtr->PinNum >= PIN0 && ConfigPtr->PinNum <= PIN1)))
        {
            GPIOB->CRL &= ~(0xF << ConfigPtr->PinNum);
        }
        else if((ConfigPtr->PortNum == PC)&&((ConfigPtr->PinNum >= PIN0 && ConfigPtr->PinNum <= PIN5)))
        {
            GPIOC->CRL &= ~(0xF << ConfigPtr->PinNum);
        }
        else return; 
    }
}

void Port_SetPinDirection (Port_PinType Pin, Port_PinDirectionType Direction)
{
    /*từ Pin tính ra dc port và pin luôn từ định nghĩa của kiểu dữ liệu*/
    if(Pin == 45)
    {
        if(Direction == PORT_PIN_IN)
        {
            init_GP(PC,13,OUT50,O_GP_PP);
        }
        else
        {
            init_GP(PC,13,IN,I_PP);
        }
    }
}

