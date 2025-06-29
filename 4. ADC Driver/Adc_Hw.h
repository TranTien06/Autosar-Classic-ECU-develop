#ifndef ADC_HW_H
#define ADC_HW_H

#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "Adc_Types.h"      // File chứa các định nghĩa cấu trúc và kiểu dữ liệu cho ADC


/**********************************************************
 * @brief Macro bật clock và cấu hình các chân GPIO cho ADC.
 * @details Macro này bật clock cho GPIO và cấu hình các chân ở chế độ Analog Input
 *          để tương ứng với các kênh ADC.
 * @param[in] RCC_GPIO: Xung clock GPIO cần bật.
 * @param[in] GPIO_PORT: Cổng GPIO sử dụng.
 * @param[in] GPIO_PINS: Các chân GPIO cần cấu hình.
 **********************************************************/
#define SETUP_ADC_GPIO(RCC_GPIO, GPIO_PORT, GPIO_PINS)  \
    do {                                                \
        /* Bật xung nhịp cho GPIO */                    \
        RCC_APB2PeriphClockCmd((RCC_GPIO), ENABLE);     \
        /* Cấu hình GPIO cho ADC */                     \
        GPIO_InitTypeDef GPIO_InitStruct;               \
        GPIO_InitStruct.GPIO_Pin = (GPIO_PINS);         \
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;      \
        GPIO_Init((GPIO_PORT), &GPIO_InitStruct);       \
    } while(0)


/**********************************************************
 * @brief Cấu hình GPIO cho các chân ADC dựa trên các kênh được chọn.
 * @param[in] ConfigPtr: Con trỏ tới cấu trúc cấu hình ADC chứa các thông tin về kênh.
 **********************************************************/
static inline void Adc_Hw_SetupGPIO(const Adc_ConfigType* ConfigPtr) {
    // Duyệt qua tất cả các kênh được cấu hình trong ConfigPtr
    for (uint8 i = 0; i < ConfigPtr->NumChannels; i++) {
        Adc_ChannelType channel = ConfigPtr->Channels[i].Channel;

        // Kiểm tra từng kênh và cấu hình GPIO tương ứng
        if (channel <= ADC_CHANNEL_7) {
            // Các kênh ADC_CHANNEL_0 đến ADC_CHANNEL_7 nằm trên GPIOA
            SETUP_ADC_GPIO(RCC_APB2Periph_GPIOA, GPIOA, (1 << channel));  // Cấu hình cổng GPIOA
        } else if (channel == ADC_CHANNEL_8 || channel == ADC_CHANNEL_9) {
            // Các kênh ADC_CHANNEL_8 và ADC_CHANNEL_9 nằm trên GPIOB
            SETUP_ADC_GPIO(RCC_APB2Periph_GPIOB, GPIOB, (1 << (channel - 8)));  // Cấu hình cổng GPIOB
        } else if (channel >= ADC_CHANNEL_10 && channel <= ADC_CHANNEL_15) {
            // Các kênh ADC_CHANNEL_10 đến ADC_CHANNEL_15 nằm trên GPIOC
            SETUP_ADC_GPIO(RCC_APB2Periph_GPIOC, GPIOC, (1 << (channel - 10)));  // Cấu hình cổng GPIOC
        }
    }
}

/**********************************************************
 * @brief Bật xung nhịp và khởi tạo ADC1 với các thông số từ ConfigPtr.
 * @param[in] ConfigPtr: Con trỏ tới cấu trúc cấu hình ADC.
 **********************************************************/
static inline void Adc_Hw_Init_ADC1(const Adc_ConfigType* ConfigPtr) {
    // Bước 1: Bật xung nhịp cho ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // Bước 3: Khởi tạo các thông số cơ bản cho ADC1
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  // ADC hoạt động độc lập

    // Kiểm tra chế độ chuyển đổi liên tục hoặc đơn từ cấu hình
    ADC_InitStructure.ADC_ContinuousConvMode = (ConfigPtr->ConversionMode == ADC_CONV_MODE_CONTINUOUS) ? ENABLE : DISABLE;

    // Không sử dụng chế độ scan (scan mode)
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;

    // Kiểm tra nguồn kích hoạt: phần mềm hoặc phần cứng
    ADC_InitStructure.ADC_ExternalTrigConv = (ConfigPtr->TriggerSource == ADC_TRIGGER_SOFTWARE) ? ADC_ExternalTrigConv_None : ConfigPtr->TriggerSource;

    // Căn chỉnh dữ liệu phải (mặc định)
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

    // Số kênh được cấu hình
    ADC_InitStructure.ADC_NbrOfChannel = ConfigPtr->NumChannels;

    // Áp dụng cấu hình cho ADC1
    ADC_Init(ADC1, &ADC_InitStructure);

    // Bước 4: Hiệu chuẩn ADC1 (nếu cần)
    ADC_ResetCalibration(ADC1);  // Bắt đầu reset hiệu chuẩn
    while(ADC_GetResetCalibrationStatus(ADC1));  // Chờ quá trình reset hoàn thành

    ADC_StartCalibration(ADC1);  // Bắt đầu hiệu chuẩn
    while(ADC_GetCalibrationStatus(ADC1));  // Chờ quá trình hiệu chuẩn hoàn thành

    // Bước 5: Bật ADC1 và bắt đầu chuyển đổi
    ADC_Cmd(ADC1, ENABLE);  // Bật ADC1
    if (ConfigPtr->TriggerSource == ADC_TRIGGER_SOFTWARE) {
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);  // Bắt đầu chuyển đổi bằng phần mềm
    }
}

/**********************************************************
 * @brief Bật xung nhịp và khởi tạo ADC2 với các thông số từ ConfigPtr.
 * @param[in] ConfigPtr: Con trỏ tới cấu trúc cấu hình ADC.
 **********************************************************/
static inline void Adc_Hw_Init_ADC2(const Adc_ConfigType* ConfigPtr) {
    // Bước 1: Bật xung nhịp cho ADC2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

    // Bước 3: Khởi tạo các thông số cơ bản cho ADC2
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  // ADC hoạt động độc lập

    // Kiểm tra chế độ chuyển đổi liên tục hoặc đơn từ cấu hình
    ADC_InitStructure.ADC_ContinuousConvMode = (ConfigPtr->ConversionMode == ADC_CONV_MODE_CONTINUOUS) ? ENABLE : DISABLE;

    // Không sử dụng chế độ scan (scan mode)
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;

    // Kiểm tra nguồn kích hoạt: phần mềm hoặc phần cứng
    ADC_InitStructure.ADC_ExternalTrigConv = (ConfigPtr->TriggerSource == ADC_TRIGGER_SOFTWARE) ? ADC_ExternalTrigConv_None : ConfigPtr->TriggerSource;

    // Căn chỉnh dữ liệu phải (mặc định)
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

    // Số kênh được cấu hình
    ADC_InitStructure.ADC_NbrOfChannel = ConfigPtr->NumChannels;

    // Áp dụng cấu hình cho ADC2
    ADC_Init(ADC2, &ADC_InitStructure);

    // Bước 4: Hiệu chuẩn ADC2 (nếu cần)
    ADC_ResetCalibration(ADC2);  // Bắt đầu reset hiệu chuẩn
    while(ADC_GetResetCalibrationStatus(ADC2));  // Chờ quá trình reset hoàn thành

    ADC_StartCalibration(ADC2);  // Bắt đầu hiệu chuẩn
    while(ADC_GetCalibrationStatus(ADC2));  // Chờ quá trình hiệu chuẩn hoàn thành

    // Bước 5: Bật ADC2 và bắt đầu chuyển đổi
    ADC_Cmd(ADC2, ENABLE);  // Bật ADC2
    if (ConfigPtr->TriggerSource == ADC_TRIGGER_SOFTWARE) {
        ADC_SoftwareStartConvCmd(ADC2, ENABLE);  // Bắt đầu chuyển đổi bằng phần mềm
    }
}

/**********************************************************
 * @brief Cấu hình các kênh ADC dựa trên cấu hình từ ConfigPtr.
 * @param[in] ConfigPtr: Con trỏ tới cấu trúc cấu hình ADC.
 **********************************************************/
static inline void Adc_Hw_SetupChannels(const Adc_ConfigType* ConfigPtr) {
    for (uint8 i = 0; i < ConfigPtr->NumChannels; i++) {
        Adc_ChannelType channel = ConfigPtr->Channels[i].Channel;  // Lấy kênh
        uint32 samplingTime = ConfigPtr->Channels[i].SamplingTime;  // Lấy thời gian lấy mẫu
        uint8 rank = ConfigPtr->Channels[i].Rank;  // Lấy thứ tự ưu tiên

        // Thiết lập thứ tự ưu tiên và thời gian lấy mẫu cho kênh
        if (ConfigPtr->AdcInstance == ADC_INSTANCE_1) {
            ADC_RegularChannelConfig(ADC1, channel, rank, samplingTime);  // Cấu hình cho ADC1
        } else if (ConfigPtr->AdcInstance == ADC_INSTANCE_2) {
            ADC_RegularChannelConfig(ADC2, channel, rank, samplingTime);  // Cấu hình cho ADC2
        }
    }
}

/**********************************************************
 * @brief Bật ADC1 hoặc ADC2 dựa trên cấu hình từ ConfigPtr.
 * @param[in] ConfigPtr: Con trỏ tới cấu trúc cấu hình ADC.
 **********************************************************/
static inline void Adc_Hw_EnableADC(const Adc_ConfigType* ConfigPtr) {
    if (ConfigPtr->AdcInstance == ADC_INSTANCE_1) {
        ADC_Cmd(ADC1, ENABLE);  // Bật ADC1
    } else if (ConfigPtr->AdcInstance == ADC_INSTANCE_2) {
        ADC_Cmd(ADC2, ENABLE);  // Bật ADC2
    }
}

/**********************************************************
 * @brief Kiểm tra và kích hoạt quá trình hiệu chuẩn cho ADC.
 * @param[in] ConfigPtr: Con trỏ tới cấu trúc cấu hình ADC.
 **********************************************************/
static inline void Adc_Hw_Calibrate(const Adc_ConfigType* ConfigPtr) {
    if (ConfigPtr->AdcInstance == ADC_INSTANCE_1) {
        // Bắt đầu reset hiệu chuẩn cho ADC1
        ADC_ResetCalibration(ADC1);
        while (ADC_GetResetCalibrationStatus(ADC1));  // Chờ quá trình reset hoàn thành

        // Bắt đầu hiệu chuẩn cho ADC1
        ADC_StartCalibration(ADC1);
        while (ADC_GetCalibrationStatus(ADC1));  // Chờ quá trình hiệu chuẩn hoàn thành
    } else if (ConfigPtr->AdcInstance == ADC_INSTANCE_2) {
        // Bắt đầu reset hiệu chuẩn cho ADC2
        ADC_ResetCalibration(ADC2);
        while (ADC_GetResetCalibrationStatus(ADC2));  // Chờ quá trình reset hoàn thành

        // Bắt đầu hiệu chuẩn cho ADC2
        ADC_StartCalibration(ADC2);
        while (ADC_GetCalibrationStatus(ADC2));  // Chờ quá trình hiệu chuẩn hoàn thành
    }
}

/**********************************************************
 * @brief Kích hoạt chuyển đổi ADC bằng phần mềm nếu cấu hình cho trigger phần mềm.
 * @param[in] ConfigPtr: Con trỏ tới cấu trúc cấu hình ADC.
 **********************************************************/
static inline void Adc_Hw_StartSoftwareConversion(const Adc_ConfigType* ConfigPtr) {
    // Kiểm tra nếu trigger được cấu hình là phần mềm
    if (ConfigPtr->TriggerSource == ADC_TRIGGER_SOFTWARE) {
        if (ConfigPtr->AdcInstance == ADC_INSTANCE_1) {
            // Kích hoạt chuyển đổi cho ADC1
            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        } else if (ConfigPtr->AdcInstance == ADC_INSTANCE_2) {
            // Kích hoạt chuyển đổi cho ADC2
            ADC_SoftwareStartConvCmd(ADC2, ENABLE);
        }
    }
}

#endif /* ADC_HW_H */
