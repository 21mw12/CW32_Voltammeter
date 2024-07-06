示例目的：
          演示定时器外部触发启动ADC转换，定时1s采样芯片温度。

硬件资源：
          1. CW32F0003Fx StartKit
          2. 时钟HSI
          3. 系统时钟源为HSI时钟6分频，8MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz
          4. PB06设置为按键(KEY2)中断输入
          5. PA07设置为PUSH-PULL输出
          6. ADC的时钟源为PCLK，2分频

演示说明：
          每一次按键(KEY2)产生的中断自动触发ADC模块进行转换，ADC通道为MCU内部温度传感器TS。
          PA07输出电平翻转。

使用说明：
+ EWARM
          1. 打开adc_sgl_ext_trig.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开adc_sgl_ext_trig.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)