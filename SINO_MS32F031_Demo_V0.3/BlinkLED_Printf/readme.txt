******Demo BlinkLED 说明：
----- SINOMCU-AE
----- 2021-10-27(rev:0.3)：
1) 软件：Keil MDK-Lite  Version: 5.36.0.0
2) 硬件：SinoMCU MS32F031 core boad of MOTOT EV Kit
3) 运行：MS32F031 core boad 3.3V供电；
         PB8 连接LED2（LED通过电阻接GND）；
		 PB9 连接LED1（LED通过电阻接GND）；
		 PA9 连接USB转UART的RX（PA9 MCU发送）；
		 PC机打开USB转UART对应的串口，波特率115200，8bit、无校验、1个停止位；
		 
		 a)LED1与LED2交替亮灭，周期（默认2*200ms) 为2倍的LED_BLINK_HALF_PRE;
		 b)每隔LED_BLINK_HALF_PRE，串口收到信息：
		   -----running count:n(n从1开始到2的32次幂).
----- rev:0.3修改说明：
安装“Sinomcu.MS32F0xx_DFP.1.0.0.pack”；修改工程设置；
----- rev:0.2修改说明：
1）增加重定向printf到UART1功能；
2）注释格式整理；
3）mian.c中定义宏LED_BLINK_HALF_PRE；
4）DemoCode代码调整为单独一个文件夹；
5）更改了工程名称。
==================================================

