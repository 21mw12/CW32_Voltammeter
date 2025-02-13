示例目的：
          演示ADC模块单通道模拟看门狗功能。

硬件资源：
          1. CW32F0003Fx StartKit
          2. 时钟HSI
          3. 系统时钟源为HSI时钟6分频，8MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz
          4. ADC的时钟源为PCLK，1分频
          5. PA06/07设置为PUSH-PULL输出

演示说明：
          软件触发ADC模块进行单通道单次转换。
          ADC模拟看门狗通道为AIN1:PA01，下阈值为0x600。
          外接可调直流电源到PA01，ADC转换完成，如果采样值小于下阈值，则PA07输出电平翻转。

使用说明：
+ EWARM
          1. 打开adc_sgl_wdt.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开adc_sgl_wdt.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)