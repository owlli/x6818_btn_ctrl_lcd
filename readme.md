# readme

自带的屏保不断闪烁影响学习,写了个驱动可以开关x6818的lcd屏

之前拉高pwm0的电平就能把屏幕的背光关了,但是屏幕还是能看到画面

后来把lcd_en的高电平变成低电平,就能把屏幕完全关闭了



## 操作方法

在编译内核时找到Device Drivers--->Input device support--->Keyboards--->SLsiAP push Keypad support

取消勾选,把原本的按键驱动去掉再编译内核,使用新编译的内核启动

加载驱动后,按第四个按键来开关lcd屏



## 存在问题

按键质量差,有抖动,没有做按键消抖,有的时候按一次等于按了两次
