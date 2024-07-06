示例目的：
          演示软件触发ADC模块进行序列转换，支持序列连续、扫描、多次、断续等4种转换模式。

硬件资源：
          1. CW32F0003Fx StartKit
          2. 时钟HSI
          3. 系统时钟源为HSI时钟6分频，8MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz
          4. ADC的时钟源为PCLK，1或者16分频
          5. PA06/07设置为PUSH-PULL输出

演示说明：
          ADC SQR通道分别为：VDDA/3, TS, BGR基准电压1.2V, AIN7:PC02。
          ADC转换完成，PA07输出电平翻转。
          序列多次转换模式时，如果实际完成转换次数与设定值不等时，PA06/07全部点亮。
          注意：修改main.h中的转换模式宏定义，即可实现各种转换模式的测试。

使用说明：
+ EWARM
          1. 打开adc_sqr_irq_sw.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开adc_sqr_irq_sw.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)