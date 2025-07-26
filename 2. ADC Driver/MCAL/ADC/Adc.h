#include "Std_Types.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"

typedef uint8 Adc_ChannelType;
typedef uint16 Adc_ValueGroupType; // kieu du lieu tra ve gia tri RAW adc
typedef uint8 Adc_SamplingTimeType; // kieu du lieu thoi diem lay mau
typedef uint8 Adc_GroupPriorityType;
typedef uint8 Adc_GoupType; // kieu so dai dien cho 1 nhom kenh ADC
typedef uint8 Adc_StreamNumSampleType; // so luong kenh su dung DMA

#define SMPR1_SMP_Set               ((uint32_t)0x00000007)
#define SMPR2_SMP_Set               ((uint32_t)0x00000007)
#define SQR3_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR2_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR1_SQ_Set                 ((uint32_t)0x0000001F)

typedef struct {
   uint8 channel;
   uint8 sampletime;
   uint8 rank;
} ADC_ChannelConfigType;

typedef enum
{
    ADC_ACCESS_MODE_SINGLE = 0x00, // ko thi thoi
    ADC_ACCESS_MODE_STREAMING = 0x01 // bat DMA de nhan
}  Adc_GroupAccessModeType;

typedef enum
{
    ADC_HW_TRIG_RISING_EDGE = 0x00, // 
    ADC_HW_TRIG_FALLING_EDGE = 0x01, //
    ADC_HW_TRIG_BOTH_EDGES = 0x02
}  Adc_HwTriggerSignalType;

typedef enum
{
    ADC_STREAM_BUFFER_LINEAR = 0x00, // ADC se dung khi chuyen doi ma buffer da day
    ADC_STREAM_BUFFER_CIRCULAR = 0x01 // ADC se tiep tuc chuyen doi khi buffer day

}Adc_StreamBufferModeType;

typedef enum 
{
    ADC_IDLE = 0x00,
    ADC_BUSY = 0x01,
    ADC_COMPLETED = 0x02,
    ADC_STREAM_COMPLETED = 0x03 // DMA de du lieu vao buffer xong r 
}Adc_StatusType;
typedef enum
{
    ADC_TRIGG_SRC_SW = 0x00,
    ADC_TRIGG_SRC_HW = 0x01
} Adc_TriggerSourceType;

typedef enum
{
    ADC_CONV_MODE_ONESHOT = 0x00,
    ADC_CONV_MODE_CONTINUOUS = 0x01
}Adc_GroupConvModeType;
typedef enum
{
    ADC_ALIGN_LEFT = 0x00,
    ADC_ALIGN_RIGHT = 0x01
}Adc_ResultAlignmentType;


#define ADC_Channel0 ((Adc_ChannelType)0);
#define ADC_Channel1 ((Adc_ChannelType)1);
#define ADC_Channel2 ((Adc_ChannelType)2);
#define ADC_Channel3 ((Adc_ChannelType)3);
#define ADC_Channel4 ((Adc_ChannelType)4);
#define ADC_Channel5 ((Adc_ChannelType)5);
#define ADC_Channel6 ((Adc_ChannelType)6);
#define ADC_Channel7 ((Adc_ChannelType)7);

typedef struct 
{
    uint8 ADCMode; // independent or dual mode =0 la independent
    uint8 Scanmode ; // multi or scan channel enum =0 (bit 8 CR1 = 0 disable)
    Adc_GroupConvModeType ContiMode; //  (bit1 CR2 = 0 la single) = 1 la conti
    Adc_TriggerSourceType Triggersource; //nguon kich timmer hoac software (bit20)
    Adc_ResultAlignmentType Alignment; // qua trai hoac qua phai (bit 11 CR2)
    uint8 NotificationEnable;
    uint8 NumChannel; // so luong channel chuyen doi (ADC1->SQR1 &= ~(0xF << 20);)
    uint8 ADCx; //1 or 2
    Adc_GroupAccessModeType DMA; //(bit 8 CR2)
    ADC_ChannelConfigType channels[16];
    //void(*InitCallback)(void); // con tro den ham khi init thanh cong  
}Adc_ConfigType;

typedef struct 
{
    Adc_GoupType Id; // id cua nhom kenh adc
    uint8 Channel[16];
    Adc_GroupPriorityType Priority;
    uint8 NumChannel;
    Adc_StatusType Status;
    Adc_ValueGroupType *Result ;
}Adc_GproupDefType;

void MyADC_Init(Adc_ConfigType* ADC_InitStruct);
void MyADC_RegularChannelConfig(ADC_ChannelConfigType *Channle);

