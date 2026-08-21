#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H
#include "stm32f1xx_hal.h"

#include <stdint.h>
#include "Picture.h"
#ifndef __TYPEDEF_U8_U16__
#define __TYPEDEF_U8_U16__
typedef uint8_t u8;
typedef uint16_t u16;
#endif

#define RED  	0xf800		//RGB	
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	
#define GRAY1   0x8410      
#define GRAY2   0x4208      




#define LCD_CTRLA   	  	GPIOB		
#define LCD_CTRLB   	  	GPIOB		



#define LCD_SCL        	GPIO_PIN_4	// SCL/SCK
#define LCD_SDA        	GPIO_PIN_5	// SDA/DIN
#define LCD_RST     	GPIO_PIN_6  // RST
#define LCD_RS         	GPIO_PIN_7  // RS/DC
#define LCD_CS        	GPIO_PIN_8  // CS/CE
#define LCD_LED        	GPIO_PIN_9  // BL/BLK


#define LCD_SCL_SET   (LCD_CTRLA->BSRR = (uint32_t)LCD_SCL)
#define LCD_SDA_SET   (LCD_CTRLA->BSRR = (uint32_t)LCD_SDA)
#define LCD_CS_SET    (LCD_CTRLA->BSRR = (uint32_t)LCD_CS)

#define LCD_LED_SET   (LCD_CTRLB->BSRR = (uint32_t)LCD_LED)
#define LCD_RS_SET    (LCD_CTRLB->BSRR = (uint32_t)LCD_RS)
#define LCD_RST_SET   (LCD_CTRLB->BSRR = (uint32_t)LCD_RST)

#define LCD_SCL_CLR   (LCD_CTRLA->BRR = (uint32_t)LCD_SCL)
#define LCD_SDA_CLR   (LCD_CTRLA->BRR = (uint32_t)LCD_SDA)
#define LCD_CS_CLR    (LCD_CTRLA->BRR = (uint32_t)LCD_CS)

#define LCD_LED_CLR   (LCD_CTRLB->BRR = (uint32_t)LCD_LED)
#define LCD_RST_CLR   (LCD_CTRLB->BRR = (uint32_t)LCD_RST)
#define LCD_RS_CLR    (LCD_CTRLB->BRR = (uint32_t)LCD_RS)

#define LCD_DATAOUT(x) LCD_DATA->ODR=x; 
#define LCD_DATAIN     LCD_DATA->IDR;   

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);

#endif