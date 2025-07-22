# AUTOSAR-Classic-ECU-Development - DIO Driver Example for STM32F103

## Mục lục
- [AUTOSAR-Classic-ECU-Development - DIO Driver Example for STM32F103](#autosar-classic-ecu-development---dio-driver-example-for-stm32f103)
  - [Mục lục](#mục-lục)
  - [Giới thiệu](#giới-thiệu)
  - [Yêu cầu hệ thống](#yêu-cầu-hệ-thống)
  - [Cấu trúc thư mục](#cấu-trúc-thư-mục)
  - [Hướng dẫn build và nạp firmware](#hướng-dẫn-build-và-nạp-firmware)
    - [1. Build firmware](#1-build-firmware)

---

## Giới thiệu

Ví dụ chuẩn về **DIO Driver** theo phong cách AUTOSAR Classic MCAL cho dòng STM32F103 (Blue Pill).  
Project sử dụng **CMSIS**, **StdPeriph (SPL)**, chia module Port/Dio rõ ràng.  
**Tất cả file build (.o, .elf, .bin...) được đặt trong thư mục `Tools/`** để thuận tiện quản lý.

---

## Yêu cầu hệ thống

- **Toolchain:** [GNU Arm Embedded Toolchain (arm-none-eabi-gcc)](https://developer.arm.com/downloads/-/gnu-rm)
- **OpenOCD** để nạp firmware qua ST-Link
- **make** (có sẵn trên Linux/macOS, với Windows cài qua MinGW hoặc WSL)
- **Board:** STM32F103C8T6 (Blue Pill)

---

## Cấu trúc thư mục

AUTOSAR-Classic-ECU-Development/
└── 1. DIO Driver/
├── CMSIS/
│ ├── cmsis_compiler.h
│ ├── cmsis_gcc.h
│ ├── cmsis_version.h
│ └── core_cm3.h
├── Config/
├── Linker/
│ └── stm32f103.ld
├── MCAL/
│ ├── Dio/
│ │ ├── Dio.c
│ │ └── Dio.h
│ └── Port/
│ ├── Port.c
│ └── Port.h
├── SPL/
│ ├── inc/
│ │ ├── stm32f10x_gpio.h
│ │ ├── stm32f10x_rcc.h
│ │ ├── stm32f10x.h
│ │ └── system_stm32f10x.h
│ └── src/
│ ├── stm32f10x_gpio.c
│ ├── stm32f10x_rcc.c
│ └── system_stm32f10x.c
├── Startup/
│ └── startup_stm32f10x_md.s
├── Tools/
├── main.c
└── makefile

markdown
Sao chép
Chỉnh sửa

- **CMSIS/**: ARM core CMSIS headers  
- **MCAL/Dio, MCAL/Port**: Code driver DIO/Port abstraction  
- **SPL/**: STM32 Standard Peripheral Library  
- **Startup/**: File startup assembly cho GCC  
- **Linker/**: Linker script  
- **Tools/**: Chứa toàn bộ file build (`.o`, `.elf`, `.bin`)  
- **main.c**: Code ứng dụng mẫu  
- **makefile**: Script build chính

---

## Hướng dẫn build và nạp firmware

### 1. Build firmware

Mở terminal/cmd, chuyển vào thư mục `1. DIO Driver/` rồi chạy:

```sh
make
Sau khi build xong sẽ xuất hiện các file:

Tools/blinkled.elf: file .elf (có thể debug)

Tools/blinkled.bin: file nhị phân để nạp board

Các file object .o đều nằm trong Tools/

2. Nạp firmware vào board (cần ST-Link)
sh
Sao chép
Chỉnh sửa
make flash
Lưu ý:

Đảm bảo cắm ST-Link vào board, OpenOCD nhận đúng cổng.

Nếu dùng board khác, có thể cần chỉnh dòng openocd trong makefile cho phù hợp cấu hình.

3. Xóa file build cũ
sh
Sao chép
Chỉnh sửa
make clean
Tất cả file build trong Tools/ sẽ được xóa sạch.

Giải thích Makefile
BUILDDIR = Tools: Toàn bộ file build nằm trong thư mục này

CFLAGS, LDFLAGS: Thiết lập flags phù hợp cho project STM32/embedded (không stdlib, build nhúng, đúng chip)

Các rule: Tự động tạo thư mục, build từng object vào đúng vị trí, link ra ELF, objcopy sang BIN

make: build firmware

make flash: nạp firmware

make clean: xóa file build

Mở rộng
Có thể thêm mới hoặc mở rộng DIO/Port channel trong MCAL/

Dễ tích hợp với CMake hoặc các IDE như VSCode

Cấu trúc rõ ràng, dễ chia sẻ, nhân bản cho dự án lớn hơn

Bản quyền
Dựa trên STMicroelectronics STM32F10x StdPeriph Lib

Project mở mã nguồn cho mục đích học tập, nghiên cứu.

Mọi góp ý/cải tiến vui lòng liên hệ Hala Academy!

yaml
Sao chép
Chỉnh sửa

---

**Nếu muốn bổ sung hình ảnh mạch hoặc đoạn code demo blink LED mẫu, bạn chỉ việc thêm vào các section trên!**