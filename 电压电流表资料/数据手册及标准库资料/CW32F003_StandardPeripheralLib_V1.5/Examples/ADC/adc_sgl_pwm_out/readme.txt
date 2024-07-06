示例目的：
          演示定时器外部触发启动ADC转换，定时1s采样AIN1，并以PWM方波输出ADC采样值。

硬件资源：
          1. cw32f003C8T6 StartKit
          2. 时钟HSI
          3. 系统时钟源为HSI时钟, 48MHz，PCLK、HCLK不分频，PCLK=HCLK=SysClk=48MHz
          4. BTIM1、GTIM的时钟源为PCLK，1024分频
          5. PA07设置为PUSH-PULL输出
          6. ADC的时钟源为PCLK，128分频

演示说明：
          定时器BTIM1定时1s自动触发ADC模块进行转换，ADC通道为AIN1:PA01。
		  通用定时器GTIM将AIN1的ADC采样值转换成频率可变的PWM方波，占空比50%。
		  ADC采样值为0时，PWM方波频率为1Hz；ADC采样值为4095时，PWM方波频率为5KHz。
          PA07输出电平翻转，LED1将0.5Hz的频率闪烁。

使用说明：
+ EWARM
          1. 打开adc_sgl_pwm_out.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开adc_sgl_pwm_out.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)