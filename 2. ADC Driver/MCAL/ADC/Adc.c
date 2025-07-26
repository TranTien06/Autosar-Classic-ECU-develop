#include "Adc.h"

void MyADC_Init(Adc_ConfigType* ADC_InitStruct)
{
    if(ADC_InitStruct->ADCx == 1)
    {
        if(ADC_InitStruct->Scanmode == 0)// independent mode
        {
            ADC1->CR1 &= ~(0xF << 16); 
        }
        if(ADC_InitStruct->ContiMode == ADC_CONV_MODE_ONESHOT)
        {
            ADC1->CR2 &= ~(1 << 1);
        }
        else
        {
            ADC1->CR2 |= (1 << 1);
        }
        if(ADC_InitStruct->Triggersource == ADC_TRIGG_SRC_HW)
        {
            ADC1->CR2 |= (1 << 20);
        }
        if(ADC_InitStruct->Alignment == ADC_ALIGN_RIGHT)
        {
            ADC1->CR2 &= ~(1 << 11);
        }
        uint8 num = ADC_InitStruct->NumChannel - 1; 
        num &= 0xF;
        ADC1->SQR1 &= ~(num << 20);
        if(ADC_InitStruct->DMA == ADC_ACCESS_MODE_STREAMING)
        {
            ADC1->CR2 |= (1<<8); // chỉ có ADC1 hoac ADC3 moi dung DMA dc thoi
        }
        MyADC_RegularChannelConfig(ADC_InitStruct->channels);
    }    
}

void MyADC_RegularChannelConfig(ADC_ChannelConfigType *Channle)
{   
    for(int i = 0; i < 16;i++)  {
    uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* Check the parameters */

  /* if ADC_Channel_10 ... ADC_Channel_17 is selected */
  if (Channle[i].channel > ADC_Channel_9)
  {
    /* Get the old register value */
    tmpreg1 = ADC1->SMPR1;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR1_SMP_Set << (3 * (Channle[i].channel - 10));
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)Channle[i].sampletime << (3 * (Channle[i].channel - 10));
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADC1->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Get the old register value */
    tmpreg1 = ADC1->SMPR2;
    /* Calculate the mask to clear */
    tmpreg2 = SMPR2_SMP_Set << (3 * Channle[i].channel);
    /* Clear the old channel sample time */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)Channle[i].sampletime << (3 * Channle[i].channel);
    /* Set the new channel sample time */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADC1->SMPR2 = tmpreg1;
  }
  /* For Rank 1 to 6 */
  if (Channle[i].rank < 7)
  {
    /* Get the old register value */
    tmpreg1 = ADC1->SQR3;
    /* Calculate the mask to clear */
    tmpreg2 = SQR3_SQ_Set << (5 * (Channle[i].rank - 1));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)Channle[i].channel << (5 * (Channle[i].rank - 1));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADC1->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Channle[i].rank < 13)
  {
    /* Get the old register value */
    tmpreg1 = ADC1->SQR2;
    /* Calculate the mask to clear */
    tmpreg2 = SQR2_SQ_Set << (5 * (Channle[i].rank - 7));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)Channle[i].channel << (5 * (Channle[i].rank - 7));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADC1->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Get the old register value */
    tmpreg1 = ADC1->SQR1;
    /* Calculate the mask to clear */
    tmpreg2 = SQR1_SQ_Set << (5 * (Channle[i].rank - 13));
    /* Clear the old SQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set */
    tmpreg2 = (uint32_t)Channle[i].channel << (5 * (Channle[i].rank - 13));
    /* Set the SQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADC1->SQR1 = tmpreg1;
  }
    }
}
void Adc_StartGroupConversion()
{
  
}

