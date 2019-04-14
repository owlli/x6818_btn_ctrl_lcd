#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

#include <mach/platform.h>
#include <mach/s5p6818_irq.h>
#include <linux/gpio.h>

#include <linux/interrupt.h>

#include <asm/io.h>
#include "lcd.h"

void __iomem *virt1, *virt2;



int irq1, irq2, irq3, irq4;

//第一个参数是中断线
//中断处理函数处于中断上下文,不能睡眠,不能调用睡眠函数和可能睡眠的函数,比如kmalloc(199, GFP_KERNEL)
irqreturn_t irq1_handler(int irq, void *data)
{
	printk("<0>""%s\n", __FUNCTION__);
	
	//执行成功
	return IRQ_HANDLED;
	//执行失败,比如申请内存失败
	//return IRQ_NONE;
}
irqreturn_t irq2_handler(int irq, void *data)
{
	printk("<0>""%s\n", __FUNCTION__);
	return IRQ_HANDLED;
}

//这个中断处理函数用来取反gpiod1的电平,即控制lcd屏的背光
irqreturn_t irq3_handler(int irq, void *data)
{
	u32 tmp;

	printk("<0>""%s\n", __FUNCTION__);
	//tmp = ioread32(virt1 + GPIODOUT);
	//tmp ^= (1 << 1);
	//iowrite32(tmp, virt1 + GPIODOUT);

	tmp = ioread32(virt2 + GPIOCOUT);
	tmp ^= (1 << 10);
	iowrite32(tmp, virt2 + GPIOCOUT);
	return IRQ_HANDLED;
}

static __init int test_init(void)
{
	int ret;
	u32 tmp;

	//打印pwm0对应的寄存器gpio d1的值
	virt1 = ioremap(S5P6818_PA_LCD, S5P6818_SZ_LCD);
	tmp = ioread32(virt1 + GPIODOUT);
	printk("<0>""GPIODOUT = %#X\n", tmp);
	tmp = ioread32(virt1 + GPIODOUTENB);
	printk("<0>""GPIODOUTENB = %#X\n", tmp);
	tmp = ioread32(virt1 + GPIOD_PULLENB);
	printk("<0>""GPIOD_PULLENB = %#X\n", tmp);
	tmp = ioread32(virt1 + GPIOD_PULLENB_DISABLE_DEFAULT);
	printk("<0>""GPIOD_PULLENB_DISABLE_DEFAULT = %#X\n", tmp);

	//打印lcd_en对应的寄存器gpio 10的值
	virt2 = ioremap(S5P6818_PA_LCD, S5P6818_SZ_LCD);
	tmp = ioread32(virt2 + GPIOCOUT);
	printk("<0>""GPIOCOUT = %#X\n", tmp);
	tmp = ioread32(virt2 + GPIOCOUTENB);
	printk("<0>""GPIOCOUTENB = %#X\n", tmp);
	tmp = ioread32(virt2 + GPIOC_PULLENB);
	printk("<0>""GPIOC_PULLENB = %#X\n", tmp);
	tmp = ioread32(virt2 + GPIOC_PULLENB_DISABLE_DEFAULT);

	irq1 = IRQ_GPIO_A_START + 28;
	irq2 = IRQ_GPIO_B_START + 30;
	irq3 = gpio_to_irq(PAD_GPIO_B + 31);
	irq4 = gpio_to_irq(PAD_GPIO_B + 9);

	//申请中断
	//第三个参数就在linux-3.4/include/linux/interrupt.h文件的最开头
	ret = request_irq(irq1, irq1_handler, IRQF_TRIGGER_FALLING | IRQF_SAMPLE_RANDOM, "button0", NULL); 
	//如果irq1已经被申请过了,还要去申请,就会申请失败
	if (ret) {
		goto irq1_error;
	}
	ret = request_irq(irq2, irq2_handler, IRQF_TRIGGER_FALLING | IRQF_SAMPLE_RANDOM, "button1", NULL); 
	if (ret) {
		goto irq2_error;
	}
	ret = request_irq(irq3, irq3_handler, IRQF_TRIGGER_FALLING | IRQF_SAMPLE_RANDOM, "button2", NULL); 
	if (ret) {
		goto irq3_error;
	}

	return 0;
irq3_error:
	free_irq(irq2, NULL);
irq2_error:
	free_irq(irq1, NULL);
irq1_error:
	return ret;
}
 
static __exit void test_exit(void)
{
	iounmap(virt1);
	iounmap(virt2);
	free_irq(irq3, NULL);
	free_irq(irq2, NULL);
	free_irq(irq1, NULL);
}



module_init(test_init);
module_exit(test_exit);
 
MODULE_LICENSE("GPL");
