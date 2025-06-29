/**********************************************************
 * @file Adc.c
 * @brief Triển khai các hàm điều khiển ADC.
 * @details File này triển khai các hàm đã khai báo trong Adc.h, bao gồm khởi tạo, chuyển đổi,
 *          đọc kết quả và quản lý trạng thái của mô-đun ADC.
 * @version 1.0
 * @date 2024-10-03
 * @author HALA Academy
 **********************************************************/

#include "Adc.h"
#include "Adc_Hw.h"  /* Tệp phần cứng liên quan đến ADC */

/**********************************************************
 * @brief Khởi tạo ADC với cấu hình được truyền vào.
 * @param[in] ConfigPtr: Con trỏ trỏ tới cấu trúc cấu hình ADC.
 **********************************************************/
void Adc_Init(const Adc_ConfigType* ConfigPtr) {
    // Bước 1: Kiểm tra tham số đầu vào
    if (ConfigPtr == NULL) {
        // Nếu con trỏ cấu hình NULL, báo lỗi và thoát
        return;
    }

     // Bước 2: Cấu hình GPIO cho các chân ADC dựa trên kênh
    Adc_Hw_SetupGPIO(ConfigPtr);

    // Bước 3: Khởi tạo các thông số cho ADC1 hoặc ADC2
    if (ConfigPtr->AdcInstance == ADC_INSTANCE_1) {
        Adc_Hw_Init_ADC1(ConfigPtr);
    } else if (ConfigPtr->AdcInstance == ADC_INSTANCE_2) {
        Adc_Hw_Init_ADC2(ConfigPtr);
    }

    // Bước 4: Thiết lập độ phân giải (đối với STM32F1, mặc định là 12-bit)
    // Nếu vi điều khiển hỗ trợ độ phân giải khác, bạn có thể thêm điều kiện xử lý ở đây.


    // Bước 5: Cấu hình các kênh ADC
    Adc_Hw_SetupChannels(ConfigPtr);

    // Bước 6: Bật ADC
    Adc_Hw_EnableADC(ConfigPtr);

    // Bước 7: Kiểm tra và kích hoạt hiệu chuẩn
    Adc_Hw_Calibrate(ConfigPtr);

    // Bước 8: Kích hoạt chuyển đổi bằng phần mềm nếu cần
    Adc_Hw_StartSoftwareConversion(ConfigPtr);

    // Bước 9: Gọi hàm callback nếu có cấu hình
    if (ConfigPtr->InitCallback != NULL) {
        ConfigPtr->InitCallback();
    }
}


/**********************************************************
 * @brief Thiết lập bộ đệm kết quả cho nhóm kênh ADC.
 * @details Liên kết bộ đệm kết quả với bộ chuyển đổi ADC để lưu trữ kết quả từ quá trình chuyển đổi ADC.
 * @param[in] Group: Nhóm kênh ADC cần thiết lập bộ đệm kết quả.
 * @param[in] DataBufferPtr: Con trỏ tới bộ đệm để lưu trữ giá trị kết quả.
 * @return Std_ReturnType: Trả về E_OK nếu thành công, E_NOT_OK nếu có lỗi.
 **********************************************************/
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr) {
    // Kiểm tra tính hợp lệ của con trỏ bộ đệm
    if (DataBufferPtr == NULL) {
        return E_NOT_OK;  // Trả về lỗi nếu bộ đệm không hợp lệ
    }

    // Liên kết bộ đệm với nhóm ADC tương ứng
    if (Group == ADC_INSTANCE_1) {
        // Thiết lập kết quả chuyển đổi của ADC1 với SPL
        ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
        ADC_ContinuousModeCmd(ADC1, ENABLE);  // Chế độ chuyển đổi liên tục
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);  // Kích hoạt chuyển đổi bằng phần mềm
        *DataBufferPtr = ADC_GetConversionValue(ADC1);  // Lưu kết quả vào bộ đệm

    } else if (Group == ADC_INSTANCE_2) {
        // Thiết lập kết quả chuyển đổi của ADC2 với SPL
        ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
        ADC_ContinuousModeCmd(ADC2, ENABLE);  // Chế độ chuyển đổi liên tục
        ADC_SoftwareStartConvCmd(ADC2, ENABLE);  // Kích hoạt chuyển đổi bằng phần mềm
        *DataBufferPtr = ADC_GetConversionValue(ADC2);  // Lưu kết quả vào bộ đệm

    } else {
        return E_NOT_OK;  // Nhóm ADC không hợp lệ
    }

    return E_OK;  // Trả về thành công
}

/**********************************************************
 * @brief Hủy khởi tạo mô-đun ADC.
 * @return None
 **********************************************************/
void Adc_DeInit(void) {
    /* Hủy bỏ cấu hình phần cứng */
    Adc_Hw_DeInit();

    /* Xóa cấu hình */
    Adc_ConfigPtr = NULL;
}

/**********************************************************
 * @brief Bắt đầu chuyển đổi nhóm kênh ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_StartGroupConversion(Adc_GroupType Group) {
    /* Kiểm tra cấu hình ADC trước khi bắt đầu chuyển đổi */
    if (Adc_ConfigPtr != NULL) {
        Adc_Hw_StartConversion(Group);
    }
}

/**********************************************************
 * @brief Dừng quá trình chuyển đổi nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_StopGroupConversion(Adc_GroupType Group) {
    /* Dừng quá trình chuyển đổi trên phần cứng */
    Adc_Hw_StopConversion(Group);
}

/**********************************************************
 * @brief Đọc kết quả chuyển đổi của nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @param[out] DataBufferPtr Con trỏ tới bộ đệm kết quả.
 * @return Std_ReturnType E_OK nếu đọc thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr) {
    if (DataBufferPtr == NULL) {
        return E_NOT_OK;
    }

    /* Đọc kết quả từ phần cứng ADC */
    return Adc_Hw_ReadGroup(Group, DataBufferPtr);
}

/**********************************************************
 * @brief Bật kích hoạt phần cứng cho nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_EnableHardwareTrigger(Adc_GroupType Group) {
    /* Kích hoạt phần cứng cho nhóm ADC */
    Adc_Hw_EnableHardwareTrigger(Group);
}

/**********************************************************
 * @brief Tắt kích hoạt phần cứng cho nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_DisableHardwareTrigger(Adc_GroupType Group) {
    /* Vô hiệu hóa phần cứng cho nhóm ADC */
    Adc_Hw_DisableHardwareTrigger(Group);
}

/**********************************************************
 * @brief Bật thông báo cho nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_EnableGroupNotification(Adc_GroupType Group) {
    /* Kích hoạt thông báo cho nhóm ADC */
    Adc_Hw_EnableNotification(Group);
}

/**********************************************************
 * @brief Tắt thông báo cho nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return None
 **********************************************************/
void Adc_DisableGroupNotification(Adc_GroupType Group) {
    /* Vô hiệu hóa thông báo cho nhóm ADC */
    Adc_Hw_DisableNotification(Group);
}

/**********************************************************
 * @brief Lấy trạng thái hiện tại của nhóm ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return Trạng thái hiện tại của nhóm (IDLE, BUSY, COMPLETED).
 **********************************************************/
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group) {
    return Adc_Hw_GetGroupStatus(Group);
}

/**********************************************************
 * @brief Lấy con trỏ cuối cùng của buffer trong chế độ streaming.
 * @param[in] Group ID của nhóm kênh ADC.
 * @param[out] PtrToSampleAddress Con trỏ tới mẫu cuối cùng.
 * @return Std_ReturnType E_OK nếu thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType** PtrToSampleAddress) {
    return Adc_Hw_GetStreamLastPointer(Group, PtrToSampleAddress);
}

/**********************************************************
 * @brief Lấy thông tin phiên bản của driver.
 * @param[out] VersionInfo Con trỏ tới cấu trúc chứa thông tin phiên bản.
 * @return None
 **********************************************************/
void Adc_GetVersionInfo(Std_VersionInfoType* VersionInfo) {
    /* Kiểm tra con trỏ có hợp lệ không */
    if (VersionInfo != NULL) {
        VersionInfo->vendorID = ADC_VENDOR_ID;
        VersionInfo->moduleID = ADC_MODULE_ID;
        VersionInfo->sw_major_version = ADC_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = ADC_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = ADC_SW_PATCH_VERSION;
    }
}

/**********************************************************
 * @brief Thiết lập trạng thái nguồn cho ADC.
 * @param[in] PowerState Trạng thái nguồn mong muốn của ADC.
 * @return Std_ReturnType E_OK nếu thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_SetPowerState(Adc_PowerStateType PowerState) {
    return Adc_Hw_SetPowerState(PowerState);
}

/**********************************************************
 * @brief Lấy trạng thái nguồn hiện tại của ADC.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return Trạng thái nguồn hiện tại của ADC.
 **********************************************************/
Adc_PowerStateType Adc_GetCurrentPowerState(Adc_GroupType Group) {
    return Adc_Hw_GetCurrentPowerState(Group);
}

/**********************************************************
 * @brief Chuẩn bị cho quá trình chuyển đổi trạng thái nguồn.
 * @param[in] Group ID của nhóm kênh ADC.
 * @return Std_ReturnType E_OK nếu thành công, E_NOT_OK nếu thất bại.
 **********************************************************/
Std_ReturnType Adc_PreparePowerState(Adc_GroupType Group) {
    return Adc_Hw_PreparePowerState(Group);
}
