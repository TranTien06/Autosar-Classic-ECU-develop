#ifndef DIO_H
#define DIO_H

#include <stdint.h>

// Định nghĩa kiểu DIO Channel và trạng thái mức
typedef enum {
    DIO_PIN_RESET = 0,
    DIO_PIN_SET
} Dio_LevelType;

// Định danh các chân (Channel)
typedef enum {
    DIO_CHANNEL_LED = 0,  // LED gắn với PA5
    // ... thêm các chân khác nếu cần
} Dio_ChannelType;


// API: Viết giá trị ra chân DIO
void Dio_WriteChannel(Dio_ChannelType channel, Dio_LevelType level);

// API: Đọc trạng thái chân DIO
Dio_LevelType Dio_ReadChannel(Dio_ChannelType channel);

// API: Đảo trạng thái chân DIO
void Dio_ToggleChannel(Dio_ChannelType channel);

#endif // DIO_H
