/**********************************************************
 * @file Adc_Types.h
 * @brief Định nghĩa các kiểu dữ liệu cho mô-đun ADC trong hệ thống.
 * @details Tệp này chứa các kiểu dữ liệu quan trọng cần thiết cho việc cấu hình và quản lý mô-đun ADC.
 * @version 1.0
 * @date 2024-10-03
 * @author HALA Academy
 **********************************************************/

#ifndef ADC_TYPES_H
#define ADC_TYPES_H

#include "Std_Types.h"   // Bao gồm các kiểu dữ liệu chuẩn


/* Định nghĩa các mã lỗi liên quan đến ADC */
#define ADC_E_UNINIT                     0x0A  /**< Gọi API trước khi ADC được khởi tạo */
#define ADC_E_ALREADY_INITIALIZED        0x0D  /**< ADC đã được khởi tạo trước đó */
#define ADC_E_PARAM_POINTER              0x14  /**< Tham chiếu không hợp lệ cho buffer */
#define ADC_E_PARAM_GROUP                0x15  /**< Gọi API với nhóm không tồn tại */
#define ADC_E_WRONG_CONV_MODE            0x16  /**< Gọi API với nhóm cấu hình sai chế độ chuyển đổi */
#define ADC_E_WRONG_TRIGG_SRC            0x17  /**< Gọi API không tương thích với nguồn kích hoạt */
#define ADC_E_NOTIF_CAPABILITY           0x18  /**< Gọi API với con trỏ hàm notification là NULL */
#define ADC_E_BUFFER_UNINIT              0x19  /**< Gọi API với bộ đệm chưa khởi tạo */
#define ADC_E_BUSY                       0x0B  /**< Đã có quá trình chuyển đổi khác đang chạy */
#define ADC_E_IDLE                       0x0C  /**< Gọi API khi nhóm ADC đang ở trạng thái IDLE */
#define ADC_E_NOT_DISENGAGED             0x1A  /**< Trạng thái nguồn không thể đạt được */
#define ADC_E_TRANSITION_NOT_POSSIBLE    0x1C  /**< Chuyển đổi trạng thái không thành công */

/* Định nghĩa các macro liên quan đến trạng thái của ADC */
#define ADC_STATUS_IDLE                  0x00  /**< Trạng thái chờ (IDLE) */
#define ADC_STATUS_BUSY                  0x01  /**< Đang chuyển đổi (BUSY) */
#define ADC_STATUS_COMPLETED             0x02  /**< Chuyển đổi hoàn thành */
#define ADC_STATUS_STREAM_COMPLETED      0x03  /**< Quá trình streaming hoàn thành */


/* Định nghĩa macro cho trạng thái nguồn */
#define ADC_POWER_STATE_ON               0x00  /**< Nguồn ADC bật */
#define ADC_POWER_STATE_OFF              0x01  /**< Nguồn ADC tắt */


/**********************************************************
 * @enum Adc_ConversionModeType
 * @brief Kiểu dữ liệu xác định chế độ chuyển đổi ADC.
 * @details Lựa chọn chế độ chuyển đổi: đơn lẻ hoặc liên tục.
 **********************************************************/
typedef enum {
    ADC_CONV_MODE_SINGLE = 0,     /**< Chế độ chuyển đổi đơn lẻ (single conversion mode) */
    ADC_CONV_MODE_CONTINUOUS = 1  /**< Chế độ chuyển đổi liên tục (continuous conversion mode) */
} Adc_ConversionModeType;

/**********************************************************
 * @typedef Adc_TriggerSourceType
 * @brief Định nghĩa kiểu dữ liệu cho nguồn kích hoạt của ADC.
 **********************************************************/
typedef enum {
    ADC_TRIGGER_SOFTWARE = 0,               /**< Kích hoạt chuyển đổi ADC bằng phần mềm */
    ADC_TRIGGER_HARDWARE_TIM1_CC1 = 1,      /**< Kích hoạt phần cứng bằng Timer1 Capture Compare 1 */
    ADC_TRIGGER_HARDWARE_TIM2_CC2 = 2,      /**< Kích hoạt phần cứng bằng Timer2 Capture Compare 2 */
    ADC_TRIGGER_HARDWARE_EXTI_LINE11 = 3    /**< Kích hoạt phần cứng bằng External Interrupt Line 11 */
} Adc_TriggerSourceType;

/**********************************************************
 * @enum Adc_ResolutionType
 * @brief Kiểu dữ liệu xác định độ phân giải ADC.
 * @details Lựa chọn độ phân giải của ADC: 8, 10, hoặc 12 bit.
 **********************************************************/
typedef enum {
    ADC_RESOLUTION_8BIT = 8,     /**< Độ phân giải 8-bit */
    ADC_RESOLUTION_10BIT = 10,   /**< Độ phân giải 10-bit */
    ADC_RESOLUTION_12BIT = 12    /**< Độ phân giải 12-bit */
} Adc_ResolutionType;

/**********************************************************
 * @enum Adc_NotificationType
 * @brief Kiểu dữ liệu xác định trạng thái bật/tắt thông báo sau khi chuyển đổi ADC.
 * @details Lựa chọn bật hoặc tắt thông báo khi hoàn tất chuyển đổi ADC.
 **********************************************************/
typedef enum {
    ADC_NOTIFICATION_DISABLED = 0,  /**< Không bật thông báo khi chuyển đổi hoàn tất */
    ADC_NOTIFICATION_ENABLED = 1    /**< Bật thông báo khi chuyển đổi hoàn tất */
} Adc_NotificationType;

/**********************************************************
 * @enum Adc_ChannelType
 * @brief Kiểu dữ liệu xác định kênh ADC được sử dụng.
 * @details Lựa chọn kênh ADC để thực hiện chuyển đổi.
 **********************************************************/
typedef enum {
    ADC_CHANNEL_0 = 0,     /**< Kênh ADC 0, ví dụ PA0 */
    ADC_CHANNEL_1 = 1,     /**< Kênh ADC 1, ví dụ PA1 */
    ADC_CHANNEL_2 = 2,     /**< Kênh ADC 2, ví dụ PA2 */
    ADC_CHANNEL_3 = 3,     /**< Kênh ADC 3, ví dụ PA3 */
    ADC_CHANNEL_4 = 4,     /**< Kênh ADC 4, ví dụ PA4 */
    ADC_CHANNEL_5 = 5,     /**< Kênh ADC 5, ví dụ PA5 */
    ADC_CHANNEL_6 = 6,     /**< Kênh ADC 6, ví dụ PA6 */
    ADC_CHANNEL_7 = 7,     /**< Kênh ADC 7, ví dụ PA7 */
    ADC_CHANNEL_8 = 8,     /**< Kênh ADC 8, ví dụ PB0 */
    ADC_CHANNEL_9 = 9,     /**< Kênh ADC 9, ví dụ PB1 */
    ADC_CHANNEL_10 = 10,   /**< Kênh ADC 10, ví dụ PC0 */
    ADC_CHANNEL_11 = 11,   /**< Kênh ADC 11, ví dụ PC1 */
    ADC_CHANNEL_12 = 12,   /**< Kênh ADC 12, ví dụ PC2 */
    ADC_CHANNEL_13 = 13,   /**< Kênh ADC 13, ví dụ PC3 */
    ADC_CHANNEL_14 = 14,   /**< Kênh ADC 14, ví dụ PC4 */
    ADC_CHANNEL_15 = 15,   /**< Kênh ADC 15, ví dụ PC5 */
    ADC_CHANNEL_16 = 16,   /**< Kênh ADC 16 (cảm biến nhiệt độ nội bộ) */
    ADC_CHANNEL_17 = 17    /**< Kênh ADC 17 (Vrefint - điện áp tham chiếu nội bộ) */
} Adc_ChannelType;

/**********************************************************
 * @typedef Adc_InstanceType
 * @brief Định nghĩa kiểu dữ liệu cho các loại ADC (ADC1, ADC2, ...).
 **********************************************************/
typedef enum {
    ADC_INSTANCE_1 = 0,  /**< Chọn ADC1 */
    ADC_INSTANCE_2 = 1   /**< Chọn ADC2 */
} Adc_InstanceType;

/**********************************************************
 * @enum Adc_SamplingTimeType
 * @brief Kiểu dữ liệu xác định thời gian lấy mẫu cho ADC.
 * @details Lựa chọn thời gian lấy mẫu cho từng kênh ADC.
 **********************************************************/
typedef enum {
    ADC_SAMPLETIME_1CYCLE_5 = 0x0,  /**< Thời gian lấy mẫu 1.5 chu kỳ */
    ADC_SAMPLETIME_7CYCLES_5 = 0x1, /**< Thời gian lấy mẫu 7.5 chu kỳ */
    ADC_SAMPLETIME_13CYCLES_5 = 0x2, /**< Thời gian lấy mẫu 13.5 chu kỳ */
    ADC_SAMPLETIME_28CYCLES_5 = 0x3, /**< Thời gian lấy mẫu 28.5 chu kỳ */
    ADC_SAMPLETIME_41CYCLES_5 = 0x4, /**< Thời gian lấy mẫu 41.5 chu kỳ */
    ADC_SAMPLETIME_55CYCLES_5 = 0x5, /**< Thời gian lấy mẫu 55.5 chu kỳ */
    ADC_SAMPLETIME_71CYCLES_5 = 0x6, /**< Thời gian lấy mẫu 71.5 chu kỳ */
    ADC_SAMPLETIME_239CYCLES_5 = 0x7 /**< Thời gian lấy mẫu 239.5 chu kỳ */
} Adc_SamplingTimeType;

/**********************************************************
 * @macro
 * @brief Các macro định nghĩa cho hệ số chia tần số xung nhịp ADC.
 * @details Các giá trị hệ số chia tần số cho bộ ADC.
 **********************************************************/
#define ADC_CLOCK_PRESCALER_2   2   /**< Hệ số chia tần số 2 */
#define ADC_CLOCK_PRESCALER_4   4   /**< Hệ số chia tần số 4 */
#define ADC_CLOCK_PRESCALER_6   6   /**< Hệ số chia tần số 6 */
#define ADC_CLOCK_PRESCALER_8   8   /**< Hệ số chia tần số 8 */


/* ===============================
 *  Định nghĩa các kiểu dữ liệu của ADC Driver
 * =============================== */
/**********************************************************
 * @typedef Adc_ConfigType
 * @brief Cấu trúc chứa các thông tin cấu hình cho mô-đun ADC.
 * @details Cấu trúc này chứa các thông tin cần thiết để khởi tạo và điều khiển các kênh ADC,
 *          bao gồm xung nhịp, chế độ chuyển đổi, độ phân giải, và các kênh ADC.
 **********************************************************/
typedef struct {
    uint32 ClockPrescaler;                    /**< Hệ số chia tần số xung nhịp ADC, thường là giá trị từ 1 đến 256 */
    Adc_ConversionModeType  ConversionMode;   /**< Chế độ chuyển đổi ADC: ADC_CONV_MODE_SINGLE hoặc ADC_CONV_MODE_CONTINUOUS */
    Adc_TriggerSourceType  TriggerSource;     /**< Nguồn kích hoạt chuyển đổi: ADC_TRIGGER_SOFTWARE hoặc ADC_TRIGGER_HARDWARE */
    Adc_ResolutionType  Resolution;           /**< Độ phân giải của ADC, ví dụ: 8, 10, 12 bits */
    Adc_NotificationType NotificationEnabled; /**< Cờ bật/tắt thông báo khi quá trình chuyển đổi kết thúc */
    uint8  NumChannels;                       /**< Số lượng kênh ADC được cấu hình */
    Adc_InstanceType AdcInstance;             /**< Chọn loại ADC: ADC1 hoặc ADC2 */
    
    /**********************************************************
     * @typedef Adc_ChannelConfigType
     * @brief Cấu trúc chứa thông tin cấu hình cho từng kênh ADC.
     **********************************************************/
    struct {
        Adc_ChannelType Channel; /**< Kênh ADC được cấu hình, ví dụ: ADC_CHANNEL_0, ADC_CHANNEL_1,... */
        uint32 SamplingTime;     /**< Thời gian lấy mẫu cho kênh ADC, ví dụ: ADC_SAMPLETIME_1CYCLE_5,... */
        uint8  Rank;             /**< Thứ tự ưu tiên của kênh ADC trong quá trình chuyển đổi */
    }Channels[16]; /**< Mảng cấu hình cho từng kênh ADC (tối đa 16 kênh) */

    /**********************************************************
     * @typedef InitCallback
     * @brief Con trỏ hàm callback được gọi khi quá trình khởi tạo ADC thành công.
     **********************************************************/
    void (*InitCallback)(void);  /**< Con trỏ đến hàm callback khi khởi tạo ADC thành công */
} Adc_ConfigType;



/**********************************************************
 * @typedef Adc_ChannelType
 * @brief Kiểu dữ liệu cho ID của kênh ADC.
 * @details Định nghĩa ID của kênh ADC, được biểu diễn dưới dạng số nguyên 32-bit.
 **********************************************************/
typedef uint32 Adc_ChannelType; /**< Kênh ADC được biểu diễn dưới dạng giá trị 32-bit. */

/**********************************************************
 * @typedef Adc_GroupType
 * @brief Kiểu dữ liệu cho nhóm kênh ADC.
 * @details Mỗi nhóm kênh có thể được cấu hình để chuyển đổi theo thứ tự.
 **********************************************************/
typedef uint32 Adc_GroupType; /**< Nhóm kênh ADC được biểu diễn bằng giá trị 32-bit. */

/**********************************************************
 * @typedef Adc_ValueGroupType
 * @brief Kiểu dữ liệu cho kết quả chuyển đổi của ADC.
 * @details Giá trị được trả về sau quá trình chuyển đổi, được biểu diễn dưới dạng số nguyên 16-bit.
 **********************************************************/
typedef uint16 Adc_ValueGroupType; /**< Kết quả chuyển đổi ADC được biểu diễn bằng số nguyên 16-bit. */

/**********************************************************
 * @typedef Adc_PrescaleType
 * @brief Kiểu dữ liệu cho hệ số chia tần số clock của ADC.
 * @details Hệ số chia tần số cho ADC được biểu diễn bằng số nguyên 32-bit.
 **********************************************************/
typedef uint32 Adc_PrescaleType; /**< Hệ số chia tần số của ADC. */

/**********************************************************
 * @typedef Adc_ConversionTimeType
 * @brief Kiểu dữ liệu cho thời gian chuyển đổi của ADC.
 * @details Thời gian chuyển đổi được biểu diễn bằng số nguyên 32-bit.
 **********************************************************/
typedef uint32 Adc_ConversionTimeType; /**< Thời gian chuyển đổi của ADC. */

/**********************************************************
 * @typedef Adc_SamplingTimeType
 * @brief Kiểu dữ liệu cho thời gian lấy mẫu của ADC.
 * @details Thời gian lấy mẫu được biểu diễn bằng số chu kỳ của clock.
 **********************************************************/
typedef uint32 Adc_SamplingTimeType; /**< Thời gian lấy mẫu của ADC. */

/**********************************************************
 * @typedef Adc_ResolutionType
 * @brief Kiểu dữ liệu cho độ phân giải của ADC.
 * @details Độ phân giải của ADC được biểu diễn bằng số nguyên 8-bit.
 **********************************************************/
typedef uint8 Adc_ResolutionType; /**< Độ phân giải của ADC được biểu diễn bằng giá trị 8-bit. */

/**********************************************************
 * @typedef Adc_StatusType
 * @brief Kiểu dữ liệu cho trạng thái của quá trình chuyển đổi ADC.
 * @details Xác định trạng thái của ADC như chờ, đang chuyển đổi, hoặc hoàn thành.
 **********************************************************/
typedef enum {
    ADC_IDLE = 0x00,        /**< ADC đang ở trạng thái chờ */
    ADC_BUSY = 0x01,        /**< ADC đang thực hiện chuyển đổi */
    ADC_COMPLETED = 0x02,   /**< ADC đã hoàn thành quá trình chuyển đổi */
    ADC_ERROR = 0x03        /**< Lỗi xảy ra trong quá trình chuyển đổi */
} Adc_StatusType; /**< Trạng thái của quá trình chuyển đổi ADC. */

/**********************************************************
 * @typedef Adc_TriggerSourceType
 * @brief Kiểu dữ liệu cho nguồn kích hoạt quá trình chuyển đổi ADC.
 * @details Nguồn kích hoạt có thể là phần mềm hoặc phần cứng.
 **********************************************************/
typedef enum {
    ADC_TRIGGER_SOFTWARE = 0x00, /**< Kích hoạt bằng phần mềm */
    ADC_TRIGGER_HARDWARE = 0x01  /**< Kích hoạt bằng phần cứng */
} Adc_TriggerSourceType; /**< Nguồn kích hoạt cho quá trình chuyển đổi ADC. */

/**********************************************************
 * @typedef Adc_GroupConvModeType
 * @brief Định nghĩa kiểu dữ liệu xác định chế độ chuyển đổi của nhóm kênh ADC.
 * @details Xác định xem nhóm kênh sẽ chuyển đổi một lần (one-shot) hay liên tục (continuous).
 **********************************************************/
typedef enum {
    ADC_CONV_MODE_ONESHOT = 0x00,   /**< Chuyển đổi một lần cho mỗi kênh sau sự kiện kích hoạt */
    ADC_CONV_MODE_CONTINUOUS = 0x01 /**< Chuyển đổi liên tục các kênh ADC cho đến khi dừng */
} Adc_GroupConvModeType;

/**********************************************************
 * @typedef Adc_GroupPriorityType
 * @brief Kiểu dữ liệu xác định mức ưu tiên của nhóm kênh ADC.
 * @details Xác định mức độ ưu tiên của nhóm kênh trong hệ thống ADC.
 **********************************************************/
typedef uint8 Adc_GroupPriorityType; /**< Mức độ ưu tiên của nhóm kênh ADC, giá trị từ 0 đến 255. */

/**********************************************************
 * @typedef Adc_GroupDefType
 * @brief Kiểu dữ liệu xác định cấu hình của nhóm kênh ADC.
 * @details Xác định các kênh ADC được gán vào nhóm, không phải là kiểu API.
 **********************************************************/
typedef struct {
    Adc_ChannelType Channels[16];  /**< Mảng chứa các kênh ADC được cấu hình trong nhóm */
    Adc_GroupPriorityType Priority; /**< Mức ưu tiên của nhóm */
    uint8 NumChannels;              /**< Số lượng kênh trong nhóm */
} Adc_GroupDefType;

/**********************************************************
 * @typedef Adc_StreamNumSampleType
 * @brief Kiểu dữ liệu xác định số lượng mẫu trong chế độ streaming.
 * @details Xác định số lượng mẫu thu thập trong chế độ streaming, giá trị tùy thuộc vào vi điều khiển.
 **********************************************************/
typedef uint16 Adc_StreamNumSampleType; /**< Số lượng mẫu trong chế độ streaming. */

/**********************************************************
 * @typedef Adc_StreamBufferModeType
 * @brief Kiểu dữ liệu xác định chế độ buffer trong chế độ streaming.
 * @details Xác định buffer sẽ là tuyến tính hay vòng lặp khi số mẫu đạt đến giới hạn.
 **********************************************************/
typedef enum {
    ADC_STREAM_BUFFER_LINEAR = 0x00,   /**< Buffer tuyến tính, dừng khi buffer đầy */
    ADC_STREAM_BUFFER_CIRCULAR = 0x01  /**< Buffer vòng lặp, tiếp tục ghi đè khi buffer đầy */
} Adc_StreamBufferModeType;

/**********************************************************
 * @typedef Adc_GroupAccessModeType
 * @brief Kiểu dữ liệu xác định chế độ truy cập kết quả của nhóm kênh ADC.
 * @details Xác định chế độ truy cập là một lần (single) hay streaming.
 **********************************************************/
typedef enum {
    ADC_ACCESS_MODE_SINGLE = 0x00,    /**< Truy cập kết quả một lần */
    ADC_ACCESS_MODE_STREAMING = 0x01  /**< Truy cập kết quả theo chế độ streaming */
} Adc_GroupAccessModeType;

/**********************************************************
 * @typedef Adc_HwTriggerSignalType
 * @brief Kiểu dữ liệu xác định loại tín hiệu kích hoạt phần cứng cho ADC.
 * @details Xác định ADC sẽ phản hồi theo cạnh lên, cạnh xuống, hoặc cả hai cạnh của tín hiệu.
 **********************************************************/
typedef enum {
    ADC_HW_TRIG_RISING_EDGE = 0x00,    /**< Kích hoạt theo cạnh lên của tín hiệu */
    ADC_HW_TRIG_FALLING_EDGE = 0x01,   /**< Kích hoạt theo cạnh xuống của tín hiệu */
    ADC_HW_TRIG_BOTH_EDGES = 0x02      /**< Kích hoạt theo cả hai cạnh của tín hiệu */
} Adc_HwTriggerSignalType;

/**********************************************************
 * @typedef Adc_HwTriggerTimerType
 * @brief Kiểu dữ liệu xác định bộ định thời phần cứng kích hoạt ADC.
 * @details Xác định timer dùng để kích hoạt quá trình chuyển đổi ADC.
 **********************************************************/
typedef uint32 Adc_HwTriggerTimerType; /**< Bộ định thời phần cứng của ADC. */

/**********************************************************
 * @typedef Adc_PriorityImplementationType
 * @brief Kiểu dữ liệu xác định cách thức thực hiện ưu tiên trong quá trình chuyển đổi.
 * @details Xác định cơ chế ưu tiên giữa các nhóm chuyển đổi.
 **********************************************************/
typedef uint8 Adc_PriorityImplementationType; /**< Mức độ ưu tiên được thực hiện. */

/**********************************************************
 * @typedef Adc_GroupReplacementType
 * @brief Kiểu dữ liệu xác định cơ chế thay thế cho nhóm kênh ADC khi bị gián đoạn.
 * @details Cơ chế thay thế khi quá trình chuyển đổi nhóm bị gián đoạn bởi nhóm có mức ưu tiên cao hơn.
 **********************************************************/
typedef enum {
    ADC_GROUP_REPL_ABORT_RESTART = 0x00, /**< Cơ chế hủy và khởi động lại nhóm bị gián đoạn */
    ADC_GROUP_REPL_SUSPEND_RESUME = 0x01 /**< Cơ chế tạm dừng và tiếp tục sau khi nhóm ưu tiên cao hoàn thành */
} Adc_GroupReplacementType;

/**********************************************************
 * @typedef Adc_ChannelRangeSelectType
 * @brief Kiểu dữ liệu xác định phạm vi giá trị đầu vào của kênh ADC.
 * @details Xác định phạm vi đầu vào của kênh trong quá trình chuyển đổi.
 **********************************************************/
typedef uint8 Adc_ChannelRangeSelectType; /**< Phạm vi giá trị đầu vào của kênh ADC. */

/**********************************************************
 * @typedef Adc_ResultAlignmentType
 * @brief Kiểu dữ liệu xác định cách sắp xếp kết quả chuyển đổi của ADC.
 * @details Xác định kết quả chuyển đổi sẽ được sắp xếp về bên trái hoặc bên phải.
 **********************************************************/
typedef enum {
    ADC_RESULT_ALIGNMENT_RIGHT = 0x00, /**< Kết quả được sắp xếp về bên phải */
    ADC_RESULT_ALIGNMENT_LEFT = 0x01   /**< Kết quả được sắp xếp về bên trái */
} Adc_ResultAlignmentType;

/**********************************************************
 * @typedef Adc_PowerStateType
 * @brief Kiểu dữ liệu xác định trạng thái nguồn của ADC.
 * @details Xác định trạng thái nguồn hiện tại của ADC.
 **********************************************************/
typedef uint32 Adc_PowerStateType; /**< Trạng thái nguồn của ADC. */

/**********************************************************
 * @typedef Adc_PowerStateRequestResultType
 * @brief Kiểu dữ liệu xác định kết quả yêu cầu thay đổi trạng thái nguồn của ADC.
 * @details Xác định kết quả của yêu cầu thay đổi trạng thái nguồn ADC (thành công hoặc thất bại).
 **********************************************************/
typedef enum {
    ADC_POWER_STATE_REQUEST_OK = 0x00,      /**< Yêu cầu thay đổi trạng thái nguồn thành công */
    ADC_POWER_STATE_REQUEST_NOT_OK = 0x01  /**< Yêu cầu thay đổi trạng thái nguồn thất bại */
} Adc_PowerStateRequestResultType;

#endif /* ADC_TYPES_H */
