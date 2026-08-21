# STM32‑HAL‑SPI‑LCD‑128x160 [中文|Chinese](https://github.com/k1271max/STM32-TFT-Driver/blob/main/README_ZH.md "查看中文文档")
> 
> STM32 HAL library driver for SPI‑interface LCD screen, 128*160 resolution, supporting character, number, Chinese and image display.
> [](https://github.com/yourname/STM32%E2%80%91HAL%E2%80%91SPI%E2%80%91LCD%E2%80%91128x160)
> [](LICENSE)

## 📖 Project Introduction

This project is built on the **STM32 HAL library** to drive a 128×160 color LCD screen via SPI.

- ✅ Low‑level LCD hardware driver
- ✅ GUI graphics library: draw points, lines, rectangles, circles and button widgets
- ✅ 16‑point ASCII font
- ✅ GBK16 Chinese font and 32‑point large‑digit font
- ✅ Image display (`.h` array format images)

> 
> Screen Specifications:
> 
> 
> - Resolution: `X_MAX_PIXEL = 128`, `Y_MAX_PIXEL = 160`
> - Communication: SPI (Software‑simulated SPI)

## 📁 Directory Structure

```
STM32‑HAL‑SPI‑LCD‑128x160
├── Core/
│   └── Inc/
│       ├── LCD_Config.h     # LCD screen resolution configuration
│       ├── Lcd_Driver.h     # LCD low‑level driver header
│       ├── GUI.h            # GUI drawing API header
│       ├── Font.h           # Font library (ASCII, digit, GBK Chinese)
│       ├── Picture.h        # Image array declarations
│   └── Src/
│       ├── Lcd_Driver.c     # LCD SPI read/write, initialization, screen clearing
│       ├── GUI.c            # Implementation for GUI drawing and character rendering
│       ├── Font.c           # Font array definitions
│       ├── Picture.c        # Image array definitions
├── README.md
└── LICENSE
```

## 🔌 Hardware Pin Definition

> 
> Defined in `Lcd_Driver.h`

表格

| Signal | GPIO | Description |
| --- | --- | --- |
| SCL/SCK | PB4 | SPI Clock |
| SDA/DIN | PB5 | SPI Data |
| RST | PB6 | LCD Reset |
| RS/DC | PB7 | Data / Command Select |
| CS/CE | PB8 | Chip Select |
| BL/BLK | PB9 | Backlight Control |

> 
> Software‑simulated SPI, no hardware SPI peripheral required.

## 🚀 Quick Usage Example

```
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Font.h"
#include "Picture.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    Lcd_Init();                 // Initialize LCD
    Lcd_Clear(BLACK);           // Clear screen to black

    Gui_DrawFont_GBK16(10,10,WHITE,BLACK,(uint8_t*)"Test Chinese");   // Show Chinese characters
    Gui_DrawFont_Num32(10,40,RED,BLACK,2025);                          // 32‑point large digit
    Gui_DrawFont_GBK16(10,80,YELLOW,BLACK,(uint8_t*)"Hello World");    // ASCII text

    Gui_DrawLine(0,0,127,159,WHITE);    // Draw line
    Gui_Circle(64,80,30,GREEN);        // Draw circle
    Gui_box(20,100,40,30,BLUE);        // Draw rectangle
    Gui_showimage(gImage_tom,1,1,0,0); // Display image

    while(1)
    {
    }
}
```

## 📝 API Reference

### Low‑level APIs in Lcd_Driver.h

```
void LCD_GPIO_Init(void);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Data);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);
```

### High‑level GUI APIs in GUI.h

```
uint16_t LCD_BGR2RGB(uint16_t c);
void Gui_Circle(uint16_t X,uint16_t Y,uint16_t R,uint16_t fc);
void Gui_DrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,uint16_t Color);
void Gui_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t bc);
void Gui_box2(uint16_t x,uint16_t y,uint16_t w,uint16_t h, uint8_t mode);
void DisplayButtonDown(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void DisplayButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

// Text rendering
void Gui_DrawFont_GBK16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s);
void Gui_DrawFont_GBK24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s);
void Gui_DrawFont_Num32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint16 num);

// Image display
void Gui_showimage(const unsigned char *p, uint8_t c, uint8_t k, uint8_t x, uint8_t y);
```

Pre‑defined RGB565 Colors

```
RED	    0xf800
GREEN	0x07e0
BLUE	0x001f
WHITE	0xffff
BLACK	0x0000
YELLOW  0xFFE0
```

## 🖼 Image Conversion

1. Use an image‑to‑mod tool with these settings:
   - Mode: `RGB565`
   - Output: C‑language array
2. Paste the generated array into `Picture.c`, and add an `extern` declaration in `Picture.h`.
3. Call `Gui_showimage()` to render the image.

## ⚠️ Notes

1. This driver uses **software‑simulated SPI**. Modify pin macros inside `Lcd_Driver.h` to match your hardware.
2. Screen resolution is configured in `LCD_Config.h`: `X_MAX_PIXEL`, `Y_MAX_PIXEL`. Match them with your actual screen.
3. Only a small set of GBK Chinese characters are built‑in. Use the font‑modelling tool to extend the `hz16[]` array for more characters.
4. Ensure system clock is correctly configured in your HAL‑based project.

## 📄 License

MIT License

## 🙋 Feedback

For bugs and questions, please open an [Issues](https://github.com/yourname/STM32%E2%80%91HAL%E2%80%91SPI%E2%80%91LCD%E2%80%91128x160/issues).
