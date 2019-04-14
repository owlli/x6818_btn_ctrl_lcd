#ifndef __LCD_H__
#define __LCD_H__

//pwm0		gpiod1
//lcd_en	gpioc10


#define S5P6818_PA_LCD      0XC0010000
#define S5P6818_SZ_LCD      SZ_64K

#define GPIODOUT							0xD000
#define GPIODOUTENB							0XD004
#define GPIOD_PULLENB						0xD060
#define GPIOD_PULLENB_DISABLE_DEFAULT		0xD064
#define GPIOCOUT							0xC000
#define GPIOCOUTENB							0XC004
#define GPIOC_PULLENB						0xC060
#define GPIOC_PULLENB_DISABLE_DEFAULT		0xC064





#endif
