示例目的：
          演示MCU通过按键进入/退出休眠和深度休眠模式。

硬件资源：
          1. CW32F0003Fx StartKit
          2. 时钟HSI
          3. 系统时钟源为HSI时钟2分频，24MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=24MHz
          4. PB06设置为按键(KEY2)中断输入
          5. PA06/07设置为PUSH-PULL输出

演示说明：
          上电后，MCU处于正常工作模式，PA07(LED1)输出电平延时1s不断翻转。
		  第一次按下KEY2，MCU进入休眠或者深度休眠模式，LED1熄灭。
		  再一次按下KEY2，MCU退出休眠或者深度休眠模式，LED1点亮且不断翻转，MCU返回正常工作模式。
		  注意：修改cw32f003_pwr_modes.h中的宏定义，即可选择低功耗模式。
		  
          
使用说明：
+ EWARM
          1. 打开PWR_CurrentConsumption.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开PWR_CurrentConsumption.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)