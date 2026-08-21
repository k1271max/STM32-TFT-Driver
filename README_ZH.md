# STM32‑HAL‑SPI‑LCD‑128x160
> STM32 HAL库驱动 SPI 接口 LCD 屏，分辨率 128*160，支持字符、数字、中文、图片显示。
[![GitHub stars](https://img.shields.io/github/stars/yourname/STM32‑HAL‑SPI‑LCD‑128x160.svg)](https://github.com/yourname/STM32‑HAL‑SPI‑LCD‑128x160)
[![License](https://img.shields.io/github/license/yourname/STM32‑HAL‑SPI‑LCD‑128x160.svg)](LICENSE)
## 📖 项目简介
本项目基于 **STM32 HAL库**，实现 SPI 模式驱动 128×160 彩色LCD屏幕。
- ✅ 底层LCD硬件驱动
- ✅ GUI图形库：画点、画线、矩形、圆形、按钮控件
- ✅ ASCII 16号英文字库
- ✅ GBK16 中文字库，32号大数字字库
- ✅ 图片显示（`.h`数组格式图片）
> 屏幕参数：
> - 分辨率：`X_MAX_PIXEL = 128`，`Y_MAX_PIXEL = 160`
> - 通信方式：SPI（模拟SPI）
## 📁 目录结构
```
STM32‑HAL‑SPI‑LCD‑128x160
├── Core/
│   └── Inc/
│       ├── LCD_Config.h     # LCD屏幕分辨率配置
│       ├── Lcd_Driver.h     # LCD底层驱动头文件
│       ├── GUI.h            # GUI绘图接口头文件
│       ├── Font.h           # 字库(ASCII、数字、GBK中文)
│       ├── Picture.h        # 图片数组声明
│   └── Src/
│       ├── Lcd_Driver.c     # LCD底层SPI读写、初始化、清屏
│       ├── GUI.c            # GUI绘图与字符显示实现
│       ├── Font.c           # 字库数组定义
│       ├── Picture.c        # 图片数组定义
├── README.md
└── LICENSE
```
## 🔌 硬件引脚定义
> 来自 `Lcd_Driver.h`
|信号 | GPIO | 说明 |
|---|---|---|
| SCL/SCK | PB4 | SPI时钟 |
| SDA/DIN | PB5 | SPI数据 |
| RST | PB6 | LCD复位 |
| RS/DC | PB7 | 数据/命令选择 |
| CS/CE | PB8 | 片选 |
| BL/BLK | PB9 | 背光控制 |
> 使用**模拟SPI**，无需硬件SPI外设。
## 🚀 快速使用示例
```c
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Font.h"
#include "Picture.h"
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    Lcd_Init();                 // LCD初始化
    Lcd_Clear(BLACK);           // 清屏黑色
    Gui_DrawFont_GBK16(10,10,WHITE,BLACK,(u8*)"测试中文");   // 显示中文
    Gui_DrawFont_Num32(10,40,RED,BLACK,2025);                // 32号大数字
    Gui_DrawFont_GBK16(10,80,YELLOW,BLACK,(u8*)"Hello World"); // ASCII字符
    Gui_DrawLine(0,0,127,159,WHITE);    //画线
    Gui_Circle(64,80,30,GREEN);        //画圆
    Gui_box(20,100,40,30,BLUE);        //矩形
    Gui_showimage(gImage_tom,1,1,0,0); //显示图片
    while(1)
    {
    }
}
```
## 📝 API接口说明
### Lcd_Driver.h 底层接口
```c
void LCD_GPIO_Init(void);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);
```
### GUI.h 上层图形接口
```c
u16 LCD_BGR2RGB(u16 c);
void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc);
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);
void Gui_box(u16 x, u16 y, u16 w, u16 h,u16 bc);
void Gui_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
// 显示文字
void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void Gui_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void Gui_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num) ;
// 图片显示
void Gui_showimage(const unsigned char *p, uint8_t c, uint8_t k, uint8_t x, uint8_t y);
```
预定义颜色（RGB565）
```c
RED        0xf800
GREEN    0x07e0
BLUE	0x001f
WHITE	0xffff
BLACK	0x0000
YELLOW  0xFFE0
```
## 🖼 图片转换
1. 使用图片取模工具，选择：
    - 模式：`RGB565`
    - 输出：C语言数组
2. 将数组放入 `Picture.c`，在 `Picture.h` 添加 `extern` 声明
3. 调用 `Gui_showimage()` 显示。
## ⚠️ 注意事项
1. 本驱动为**模拟SPI**，引脚在`Lcd_Driver.h`宏定义，根据你的硬件修改。
2. 分辨率在`LCD_Config.h`：`X_MAX_PIXEL`，`Y_MAX_PIXEL`，和你的屏幕匹配。
3. 中文字库仅内置少量GBK汉字，需要更多汉字需要使用字模工具补充`hz16[]`数组。
4. HAL库工程需要保证系统时钟配置正确。
## 📄 License
MIT License
## 🙋 反馈
如有bug、问题欢迎提交 [Issues](https://github.com/yourname/STM32‑HAL‑SPI‑LCD‑128x160/issues)。
---
> 如果你需要，我可以帮你把这份内容直接输出为 `README.md` 文件原始文本，你复制保存即可。
```markdown
# STM32‑HAL‑SPI‑LCD‑128x160
> STM32 HAL库驱动 SPI 接口 LCD 屏，分辨率 128*160，支持字符、数字、中文、图片显示。
[![GitHub stars](https://img.shields.io/github/stars/yourname/STM32‑HAL‑SPI‑LCD‑128x160.svg)](https://github.com/yourname/STM32‑HAL‑SPI‑LCD‑128x160)
[![License](https://img.shields.io/github/license/yourname/STM32‑HAL‑SPI‑LCD‑128x160.svg)](LICENSE)
## 📖 项目简介
本项目基于 **STM32 HAL库**，实现 SPI 模式驱动 128×160 彩色LCD屏幕。
- ✅ 底层LCD硬件驱动
- ✅ GUI图形库：画点、画线、矩形、圆形、按钮控件
- ✅ ASCII 16号英文字库
- ✅ GBK16 中文字库，32号大数字字库
- ✅ 图片显示（`.h`数组格式图片）
> 屏幕参数：
> - 分辨率：`X_MAX_PIXEL = 128`，`Y_MAX_PIXEL = 160`
> - 通信方式：SPI（模拟SPI）
## 📁 目录结构
```
STM32‑HAL‑SPI‑LCD‑128x160
├── Core/
│   └── Inc/
│       ├── LCD_Config.h     # LCD屏幕分辨率配置
│       ├── Lcd_Driver.h     # LCD底层驱动头文件
│       ├── GUI.h            # GUI绘图接口头文件
│       ├── Font.h           # 字库(ASCII、数字、GBK中文)
│       ├── Picture.h        # 图片数组声明
│   └── Src/
│       ├── Lcd_Driver.c     # LCD底层SPI读写、初始化、清屏
│       ├── GUI.c            # GUI绘图与字符显示实现
│       ├── Font.c           # 字库数组定义
│       ├── Picture.c        # 图片数组定义
├── README.md
└── LICENSE
```
## 🔌 硬件引脚定义
> 来自 `Lcd_Driver.h`
|信号 | GPIO | 说明 |
|---|---|---|
| SCL/SCK | PB4 | SPI时钟 |
| SDA/DIN | PB5 | SPI数据 |
| RST | PB6 | LCD复位 |
| RS/DC | PB7 | 数据/命令选择 |
| CS/CE | PB8 | 片选 |
| BL/BLK | PB9 | 背光控制 |
> 使用**模拟SPI**，无需硬件SPI外设。
## 🚀 快速使用示例
```c
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Font.h"
#include "Picture.h"
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    Lcd_Init();                 // LCD初始化
    Lcd_Clear(BLACK);           // 清屏黑色
    Gui_DrawFont_GBK16(10,10,WHITE,BLACK,(u8*)"测试中文");   // 显示中文
    Gui_DrawFont_Num32(10,40,RED,BLACK,2025);                // 32号大数字
    Gui_DrawFont_GBK16(10,80,YELLOW,BLACK,(u8*)"Hello World"); // ASCII字符
    Gui_DrawLine(0,0,127,159,WHITE);    //画线
    Gui_Circle(64,80,30,GREEN);        //画圆
    Gui_box(20,100,40,30,BLUE);        //矩形
    Gui_showimage(gImage_tom,1,1,0,0); //显示图片
    while(1)
    {
    }
}
```
## 📝 API接口说明
### Lcd_Driver.h 底层接口
```c
void LCD_GPIO_Init(void);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);
```
### GUI.h 上层图形接口
```c
u16 LCD_BGR2RGB(u16 c);
void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc);
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);
void Gui_box(u16 x, u16 y, u16 w, u16 h,u16 bc);
void Gui_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
// 显示文字
void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void Gui_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void Gui_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num) ;
// 图片显示
void Gui_showimage(const unsigned char *p, uint8_t c, uint8_t k, uint8_t x, uint8_t y);
```
预定义颜色（RGB565）
```c
RED	    0xf800
GREEN	0x07e0
BLUE	0x001f
WHITE	0xffff
BLACK	0x0000
YELLOW  0xFFE0
```
## 🖼 图片转换
1. 使用图片取模工具，选择：
    - 模式：`RGB565`
    - 输出：C语言数组
2. 将数组放入 `Picture.c`，在 `Picture.h` 添加 `extern` 声明
3. 调用 `Gui_showimage()` 显示。
## ⚠️ 注意事项
1. 本驱动为**模拟SPI**，引脚在`Lcd_Driver.h`宏定义，根据你的硬件修改。
2. 分辨率在`LCD_Config.h`：`X_MAX_PIXEL`，`Y_MAX_PIXEL`，和你的屏幕匹配。
3. 中文字库仅内置少量GBK汉字，需要更多汉字需要使用字模工具补充`hz16[]`数组。
4. HAL库工程需要保证系统时钟配置正确。
## 🙋 反馈
如有bug、问题欢迎提交 [Issues](https://github.com/yourname/STM32‑HAL‑SPI‑LCD‑128x160/issues)。
```翻译为英文
