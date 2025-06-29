#ifndef ADC_CFG_H
#define ADC_CFG_H

#include "Adc_Types.h"

/**********************************************************************
 * Định nghĩa các hằng số và thông số cho các nhóm và kênh ADC.
 **********************************************************************/

/* Số lượng nhóm ADC */
#define ADC_MAX_GROUPS            2   /**< Tổng số nhóm ADC được cấu hình */

/* Kích thước bộ đệm dữ liệu ADC cho mỗi nhóm */
#define ADC_BUFFER_SIZE_GROUP_1   4   /**< Kích thước bộ đệm cho nhóm 1 */
#define ADC_BUFFER_SIZE_GROUP_2   4   /**< Kích thước bộ đệm cho nhóm 2 */

/* Các nhóm ADC (group) */
#define ADC_GROUP_1   0    /**< Nhóm 1 cho các kênh của ADC1 */
#define ADC_GROUP_2   1    /**< Nhóm 2 cho các kênh của ADC2 */

/**********************************************************************
 * Cấu trúc cấu hình cho các kênh ADC trong mỗi nhóm.
 **********************************************************************/


/**********************************************************************
 * Cấu hình các kênh trong từng nhóm.
 **********************************************************************/

/* Định nghĩa các kênh ADC trong từng nhóm */
#define ADC_GROUP_1_CHANNEL_0     ADC_CHANNEL_0   /**< Kênh 0 thuộc nhóm ADC1 */
#define ADC_GROUP_2_CHANNEL_1     ADC_CHANNEL_1   /**< Kênh 1 thuộc nhóm ADC2 */

/**********************************************************
 * @brief Mảng cấu hình cho các nhóm ADC (ADC1 và ADC2).
 * @details Mỗi nhóm sẽ có các thông tin cấu hình như ClockPrescaler, 
 *          ConversionMode, TriggerSource, Resolution, NotificationEnabled, 
 *          AdcInstance và cấu hình kênh (Channels).
 **********************************************************/
const Adc_ConfigType Adc_Configs[ADC_MAX_GROUPS] = {
    // Nhóm cấu hình thứ nhất cho ADC1
    {
        .ClockPrescaler = 8,                          /**< Hệ số chia tần số */
        .ConversionMode = ADC_CONV_MODE_SINGLE,       /**< Chế độ chuyển đổi đơn */
        .TriggerSource = ADC_TRIGGER_SOFTWARE,        /**< Kích hoạt phần mềm */
        .Resolution = ADC_RESOLUTION_12BIT,           /**< Độ phân giải 12-bit */
        .NotificationEnabled = ADC_NOTIFICATION_ENABLED, /**< Bật thông báo */
        .NumChannels = 2,                             /**< Số kênh cấu hình */
        .AdcInstance = ADC_INSTANCE_1,                /**< Sử dụng ADC1 */
        
        // Cấu hình cho các kênh của nhóm ADC1
        .Channels = {
            { 
                .Channel = ADC_CHANNEL_0,             /**< Kênh ADC1 Channel 0 */
                .SamplingTime = 55,                   /**< Thời gian lấy mẫu 55 cycles */
                .Rank = 1                             /**< Ưu tiên cao nhất (rank 1) */
            },
            {
                .Channel = ADC_CHANNEL_1,             /**< Kênh ADC1 Channel 1 */
                .SamplingTime = 55,                   /**< Thời gian lấy mẫu 55 cycles */
                .Rank = 2                             /**< Thứ tự ưu tiên thấp hơn (rank 2) */
            }
        },
        
        .InitCallback = NULL  /**< Không sử dụng callback cho nhóm này */
    },

    // Nhóm cấu hình thứ hai cho ADC2
    {
        .ClockPrescaler = 16,                         /**< Hệ số chia tần số */
        .ConversionMode = ADC_CONV_MODE_CONTINUOUS,   /**< Chế độ chuyển đổi liên tục */
        .TriggerSource = ADC_TRIGGER_HARDWARE_TIM1_CC1, /**< Kích hoạt phần cứng từ Timer1 Capture Compare 1 */
        .Resolution = ADC_RESOLUTION_10BIT,           /**< Độ phân giải 10-bit */
        .NotificationEnabled = ADC_NOTIFICATION_DISABLED, /**< Tắt thông báo */
        .NumChannels = 1,                             /**< Cấu hình 1 kênh */
        .AdcInstance = ADC_INSTANCE_2,                /**< Sử dụng ADC2 */
        
        // Cấu hình cho kênh của nhóm ADC2
        .Channels = {
            { 
                .Channel = ADC_CHANNEL_2,             /**< Kênh ADC2 Channel 2 */
                .SamplingTime = 28,                   /**< Thời gian lấy mẫu 28 cycles */
                .Rank = 1                             /**< Ưu tiên cao nhất (rank 1) */
            }
        },
        
        .InitCallback = NULL  /**< Không sử dụng callback cho nhóm này */
    }
};

#endif /* ADC_CFG_H */
