/**********************************************************
/**********************************************************
 * @file Adc.h
 * @brief Khai báo các hàm và kiểu dữ liệu liên quan đến điều khiển ADC
 * @details File này cung cấp các khai báo và định nghĩa cần thiết cho việc khởi tạo,
 *          chuyển đổi, đọc kết quả và quản lý trạng thái của ADC trên vi điều khiển.
 * @version 1.0
 * @date 2024-10-03
 * @author HALA Academy
 **********************************************************/

#ifndef ADC_H
#define ADC_H

#include "Adc_Types.h"
//#include "Adc_Hw.h"

/* ===============================
 *  Khai báo các hàm API của ADC Driver
 * =============================== */

/**********************************************************
 * @brief Khởi tạo mô-đun ADC.
 * @details Hàm này khởi tạo các đơn vị phần cứng ADC và driver theo cấu hình được chỉ định.
 * @param[in] ConfigPtr Con trỏ tới tập cấu hình cho mô-đun ADC.
 * @return None
 **********************************************************/
void Adc_Init(const Adc_ConfigType* ConfigPtr);

/**********************************************************
 * @brief Thiết lập bộ đệm kết quả cho nhóm ADC.
 * @details Hàm này thiết lập địa chỉ bộ đệm kết quả cho các kênh trong nhóm.
 * @param[in] Group ID của nhóm kênh ADC.
 * @param[in] DataBufferPtr Con trỏ tới bộ đệm kết quả.
 * @return Std_ReturnType Trả về E_OK nếu thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);

/**********************************************************
 * @brief Hủy khởi tạo mô-đun ADC.
 * @details Đưa tất cả các đơn vị phần cứng ADC về trạng thái chưa khởi tạo.
 * @return None
 **********************************************************/
void Adc_DeInit(void);

/**********************************************************
 * @brief Bắt đầu chuyển đổi nhóm kênh ADC.
 * @details Bắt đầu quá trình chuyển đổi cho tất cả các kênh trong nhóm.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_StartGroupConversion(Adc_GroupType Group);

/**********************************************************
 * @brief Dừng quá trình chuyển đổi nhóm ADC.
 * @details Dừng quá trình chuyển đổi của nhóm kênh ADC được chỉ định.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_StopGroupConversion(Adc_GroupType Group);

/**********************************************************
 * @brief Đọc kết quả chuyển đổi của nhóm ADC.
 * @details Trả về giá trị kết quả của các kênh trong nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @param[out] DataBufferPtr Con trỏ tới bộ đệm lưu trữ kết quả.
 * @return Std_ReturnType Trả về E_OK nếu đọc thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);

/**********************************************************
 * @brief Bật kích hoạt phần cứng cho nhóm ADC.
 * @details Kích hoạt nguồn phần cứng cho nhóm kênh được chỉ định.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_EnableHardwareTrigger(Adc_GroupType Group);

/**********************************************************
 * @brief Tắt kích hoạt phần cứng cho nhóm ADC.
 * @details Vô hiệu hóa nguồn phần cứng cho nhóm kênh được chỉ định.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_DisableHardwareTrigger(Adc_GroupType Group);

/**********************************************************
 * @brief Bật thông báo cho nhóm ADC.
 * @details Kích hoạt thông báo nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_EnableGroupNotification(Adc_GroupType Group);

/**********************************************************
 * @brief Tắt thông báo cho nhóm ADC.
 * @details Vô hiệu hóa thông báo nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_DisableGroupNotification(Adc_GroupType Group);

/**********************************************************
 * @brief Lấy trạng thái nhóm ADC.
 * @details Trả về trạng thái hiện tại của nhóm ADC (IDLE, BUSY, hoặc COMPLETED).
 * @param[in] Group ID của nhóm kênh ADC.
 * @return Adc_StatusType Trạng thái của nhóm kênh ADC.
 **********************************************************/
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);

/**********************************************************
 * @brief Lấy con trỏ cuối cùng của buffer trong chế độ streaming.
 * @details Trả về địa chỉ của mẫu cuối cùng được ghi vào bộ đệm của nhóm kênh.
 * @param[in] Group ID của nhóm kênh ADC.
 * @param[out] PtrToSampleAddress Con trỏ tới địa chỉ của mẫu cuối cùng.
 * @return Std_ReturnType Trả về E_OK nếu thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType** PtrToSampleAddress);

/**********************************************************
 * @brief Lấy thông tin phiên bản của driver.
 * @details Trả về thông tin phiên bản của mô-đun ADC driver.
 * @param[out] VersionInfo Con trỏ tới cấu trúc chứa thông tin phiên bản.
 * @return None
 **********************************************************/
void Adc_GetVersionInfo(Std_VersionInfoType* VersionInfo);

/**********************************************************
 * @brief Thiết lập trạng thái nguồn cho ADC.
 * @details Thay đổi trạng thái nguồn của ADC dựa trên yêu cầu của hệ thống.
 * @param[in] PowerState Trạng thái nguồn mong muốn của ADC.
 * @return Std_ReturnType Trả về E_OK nếu thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_SetPowerState(Adc_PowerStateType PowerState);

/**********************************************************
 * @brief Lấy trạng thái nguồn hiện tại của ADC.
 * @details Trả về trạng thái nguồn hiện tại của ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return Adc_PowerStateType Trạng thái nguồn hiện tại.
 **********************************************************/
Adc_PowerStateType Adc_GetCurrentPowerState(Adc_GroupType Group);

/**********************************************************
 * @brief Lấy trạng thái nguồn mục tiêu của ADC.
 * @details Trả về trạng thái nguồn mục tiêu mà ADC đang chuyển đổi.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return Adc_PowerStateType Trạng thái nguồn mục tiêu.
 **********************************************************/
Adc_PowerStateType Adc_GetTargetPowerState(Adc_GroupType Group);

/**********************************************************
 * @brief Chuẩn bị cho quá trình chuyển đổi trạng thái nguồn.
 * @details Chuẩn bị ADC để chuyển sang trạng thái nguồn mới.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return Std_ReturnType Trả về E_OK nếu thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_PreparePowerState(Adc_GroupType Group);


#endif // ADC_H


