![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)
![Platform](https://img.shields.io/badge/platform-STM32F103-blue)

# 🚗 AUTOSAR Classic ECU Development

> **Ví dụ DIO Driver cho STM32F103 (Blue Pill)**

---

## 📋 Mục lục
- [Giới thiệu](#giới-thiệu)
- [Yêu cầu hệ thống](#yêu-cầu-hệ-thống)
- [Cấu trúc thư mục](#cấu-trúc-thư-mục)
- [Hướng dẫn build & nạp firmware](#hướng-dẫn-build-và-nạp-firmware)
- [Giải thích Makefile](#giải-thích-makefile)
- [Mở rộng dự án](#mở-rộng-dự-án)
- [Liên hệ](#liên-hệ)

---

## 📝 Giới thiệu

Dự án này cung cấp một ví dụ chuẩn về **DIO Driver** theo tiêu chuẩn AUTOSAR Classic MCAL (Microcontroller Abstraction Layer) dành cho vi điều khiển STM32F103 (Blue Pill).

- Sử dụng **CMSIS** và **STM32 Standard Peripheral Library (SPL)**
- Module **Port** và **Dio** tách biệt, dễ bảo trì
- File build (`.o`, `.elf`, `.bin`) lưu trong thư mục `Tools/`
- Ứng dụng mẫu: LED nhấp nháy minh họa sử dụng DIO driver

---

## ⚙️ Yêu cầu hệ thống

| Thành phần           | Yêu cầu                                                                 |
|---------------------|-------------------------------------------------------------------------|
| Toolchain           | [GNU Arm Embedded Toolchain (arm-none-eabi-gcc)](https://developer.arm.com/downloads/-/gnu-rm) |
| OpenOCD             | Công cụ nạp firmware qua ST-Link                                         |
| Make                | Có sẵn trên Linux/macOS; Windows: cài MinGW hoặc WSL                     |
| Phần cứng           | Board STM32F103C8T6 (Blue Pill)                                          |
| Thiết bị lập trình   | ST-Link (v2 hoặc tương thích)                                            |
| Hệ điều hành        | Linux, macOS, hoặc Windows (khuyến nghị dùng WSL trên Windows)            |

---

## 🗂️ Cấu trúc thư mục

```
AUTOSAR-Classic-ECU-Development/
└── 1. DIO Driver/
    ├── CMSIS/
    │   ├── cmsis_compiler.h
    │   ├── cmsis_gcc.h
    │   ├── cmsis_version.h
    │   └── core_cm3.h
    ├── Config/
    ├── Linker/
    │   └── stm32f103.ld
    ├── MCAL/
    │   ├── Dio/
    │   │   ├── Dio.c
    │   │   └── Dio.h
    │   └── Port/
    │       ├── Port.c
    │       └── Port.h
    ├── SPL/
    │   ├── inc/
    │   │   ├── stm32f10x_gpio.h
    │   │   ├── stm32f10x_rcc.h
    │   │   ├── stm32f10x.h
    │   │   └── system_stm32f10x.h
    │   └── src/
    │       ├── stm32f10x_gpio.c
    │       ├── stm32f10x_rcc.c
    │       └── system_stm32f10x.c
    ├── Startup/
    │   └── startup_stm32f103.s
    ├── Tools/
    ├── main.c
    └── makefile
```

| Thư mục/File      | Mô tả |
|-------------------|-------|
| CMSIS/            | Header ARM Cortex-M3 CMSIS |
| Config/           | File cấu hình dự án |
| Linker/           | Linker script STM32F103 |
| MCAL/Dio, MCAL/Port | Driver DIO & Port chuẩn AUTOSAR |
| SPL/              | STM32 Standard Peripheral Library |
| Startup/          | Mã assembly khởi động cho GCC |
| Tools/            | Chứa file build (`.o`, `.elf`, `.bin`) |
| main.c            | Ứng dụng mẫu (LED nhấp nháy) |
| makefile          | Script build tự động |

---

## 🚀 Hướng dẫn build và nạp firmware

### 1. Cài đặt môi trường

> ℹ️ **Lưu ý:** Đảm bảo đã cài đủ toolchain, OpenOCD, Make và kết nối board STM32F103 với ST-Link.

1. **Cài GNU Arm Toolchain**
   - Tải & cài [GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-rm)
   - Thêm đường dẫn `bin/` vào biến môi trường `PATH`
   - Kiểm tra:
     ```sh
     arm-none-eabi-gcc --version
     ```
2. **Cài OpenOCD**
   - Tải & cài từ [openocd.org](http://openocd.org/) hoặc qua package manager
   - Đảm bảo ST-Link nhận diện được
3. **Cài Make**
   - Linux/macOS: thường đã có sẵn
   - Windows: cài MinGW hoặc dùng WSL
4. **Chuẩn bị phần cứng**
   - Kết nối board với ST-Link
   - Cấp nguồn cho board

### 2. Build Firmware

```sh
cd path/to/AUTOSAR-Classic-ECU-Development/1.\ DIO\ Driver/
make
```

- File build sẽ nằm trong `Tools/`: `blinkled.elf`, `blinkled.bin`, các file `.o`
- Nếu lỗi: kiểm tra lại toolchain, file CMSIS/SPL/Startup

### 3. Nạp Firmware

```sh
make flash
```

- Nếu thành công: LED nhấp nháy theo logic trong `main.c`
- Nếu lỗi: kiểm tra ST-Link, cấu hình OpenOCD trong makefile

### 4. Xóa File Build

```sh
make clean
```

- Xóa sạch file `.o`, `.elf`, `.bin` trong `Tools/`

---

## 🛠️ Giải thích Makefile

- **BUILDDIR = Tools**: Thư mục chứa file build
- **CFLAGS, LDFLAGS**: Cờ biên dịch & liên kết tối ưu cho STM32F103
- **Các rule**:
  - `make`: build & liên kết tạo `.elf`, `.bin`
  - `make flash`: nạp firmware qua ST-Link
  - `make clean`: xóa file build

---

## 🌱 Mở rộng dự án

- Thêm kênh DIO/Port mới trong `MCAL/Dio/` hoặc `MCAL/Port/`
- Tích hợp với IDE: VSCode, Keil, IAR, CMake
- Thiết kế module hóa, dễ mở rộng cho các dự án STM32 khác

---

## 📞 Liên hệ

Vui lòng liên hệ **Hala Academy** để gửi phản hồi hoặc đề xuất cải tiến.

---

![STM32F103 Blue Pill](https://upload.wikimedia.org/wikipedia/commons/2/2b/STM32F103C8T6_Board.jpg)
AUTOSAR-Classic-ECU-Development/
└── 1. DIO Driver/
    ├── CMSIS/
    │   ├── cmsis_compiler.h
    │   ├── cmsis_gcc.h
    │   ├── cmsis_version.h
    │   └── core_cm3.h
    ├── Config/
    ├── Linker/
    │   └── stm32f103.ld
    ├── MCAL/
    │   ├── Dio/
    │   │   ├── Dio.c
    │   │   └── Dio.h
    │   └── Port/
    │       ├── Port.c
    │       └── Port.h
    ├── SPL/
    │   ├── inc/
    │   │   ├── stm32f10x_gpio.h
    │   │   ├── stm32f10x_rcc.h
    │   │   ├── stm32f10x.h
    │   │   └── system_stm32f10x.h
    │   └── src/
    │       ├── stm32f10x_gpio.c
    │       ├── stm32f10x_rcc.c
    │       └── system_stm32f10x.c
    ├── Startup/
    │   └── startup_stm32f103.s
    ├── Tools/
    ├── main.c
    └── makefile
```

- **CMSIS/**: Chứa các file header của ARM Cortex-M3 CMSIS
- **Config/**: Thư mục chứa các file cấu hình dự án
- **Linker/**: File linker script cho STM32F103
- **MCAL/Dio, MCAL/Port**: Các driver DIO và Port tuân theo chuẩn AUTOSAR
- **SPL/**: Thư viện STM32 Standard Peripheral Library
- **Startup/**: File mã assembly khởi động cho GCC
- **Tools/**: Thư mục chứa các file build (`.o`, `.elf`, `.bin`)
- **main.c**: Mã ứng dụng mẫu (LED nhấp nháy)
- **makefile**: Script để tự động hóa quá trình build

## Hướng dẫn build và nạp firmware

### 1. Cài đặt môi trường

1. **Cài đặt GNU Arm Toolchain**:
   - Tải và cài đặt [GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-rm) phù hợp với hệ điều hành.
   - Thêm đường dẫn của toolchain (thư mục `bin/`) vào biến môi trường `PATH`.
   - Kiểm tra cài đặt bằng lệnh:
     ```sh
     arm-none-eabi-gcc --version
     ```

2. **Cài đặt OpenOCD**:
   - Tải và cài đặt OpenOCD từ [trang chính thức](http://openocd.org/) hoặc qua gói quản lý (ví dụ: `sudo apt install openocd` trên Ubuntu).
   - Đảm bảo ST-Link được nhận diện bởi hệ thống.

3. **Cài đặt Make**:
   - Trên Linux/macOS: Make thường đã có sẵn. Kiểm tra bằng lệnh `make --version`.
   - Trên Windows: Cài MinGW hoặc dùng WSL và chạy `sudo apt install make` (trên WSL).

4. **Chuẩn bị phần cứng**:
   - Kết nối boardim với board STM32F103 qua ST-Link.
   - Đảm bảo board Blue Pill được cấp nguồn (thông qua USB hoặc nguồn ngoài).

### 2. Build Firmware

1. Mở terminal (hoặc command prompt trên Windows) và chuyển đến thư mục `1. DIO Driver/`:
   ```sh
   cd path/to/AUTOSAR-Classic-ECU-Development/1.\ DIO\ Driver/
   ```

2. Chạy lệnh build:
   ```sh
   make
   ```

3. Sau khi build thành công, các file sau sẽ được tạo trong thư mục `Tools/`:
   - `blinkled.elf`: File định dạng ELF để debug
   - `blinkled.bin`: File nhị phân để nạp vào board
   - Các file object (`.o`): File trung gian của quá trình biên dịch

**Lưu ý**: Nếu gặp lỗi khi build, kiểm tra:
- Đường dẫn toolchain đã được thiết lập đúng.
- Các file trong thư mục `CMSIS/`, `SPL/`, và `Startup/` không bị thiếu.

### 3. Nạp Firmware

1. Kết nối ST-Link với board STM32F103 và máy tính.
2. Chạy lệnh để nạp firmware:
   ```sh
   make flash
   ```

3. Kiểm tra kết quả:
   - Nếu thành công, LED trên board sẽ nhấp nháy theo logic trong `main.c`.
   - Nếu thất bại, kiểm tra:
     - ST-Link có được nhận diện không (dùng lệnh `openocd -f interface/stlink.cfg -f target/stm32f1x.cfg` để kiểm tra).
     - File `makefile` có cấu hình OpenOCD đúng không (đặc biệt với các board khác Blue Pill).

### 4. Xóa File Build

Để xóa tất cả file build trong thư mục `Tools/`:
```sh
make clean
```

Lệnh này sẽ xóa sạch các file `.o`, `.elf`, `.bin` để bắt đầu lại quá trình build.

## Giải thích Makefile

- **BUILDDIR = Tools**: Chỉ định thư mục chứa các file build.
- **CFLAGS, LDFLAGS**: Các cờ biên dịch và liên kết được thiết lập cho dự án nhúng STM32 (tắt stdlib, tối ưu hóa cho chip STM32F103).
- **Các rule**:
  - `make`: Biên dịch và liên kết để tạo các file `.elf` và `.bin`.
  - `make flash`: Nạp firmware vào board qua ST-Link.
  - `make clean`: Xóa tất cả file trong thư mục `Tools/`.

## Mở rộng dự án

- **Thêm kênh DIO/Port**: Có thể thêm các kênh mới trong `MCAL/Dio/` hoặc `MCAL/Port/` để hỗ trợ thêm chân GPIO hoặc tính năng.
- **Tích hợp với IDE**: Cấu trúc dự án tương thích với CMake hoặc các IDE như VSCode, Keil, hoặc IAR.
- **Tái sử dụng**: Thiết kế module hóa giúp dễ dàng mở rộng cho các dự án STM32 khác.


## Liên hệ

Vui lòng liên hệ **Hala Academy** để gửi phản hồi hoặc đề xuất cải tiến.
