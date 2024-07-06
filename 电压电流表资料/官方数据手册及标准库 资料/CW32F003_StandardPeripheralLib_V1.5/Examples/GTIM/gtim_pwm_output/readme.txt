示例目的：
          模拟软件发生故障时，窗口看门狗WWDT复位系统的功能。

硬件资源：
          1. cw32f003C8T6 StartKit
          2. 时钟HSI
          3. 系统时钟设置为PLL，由HSI提供的8MHz时钟6倍频到48MHz， PCLK、HCLK不分频，
             PCLK=HCLK=SysClk=48MHz
          4. GTIM的分频系数设置为16，ARR设置为1499，则溢出时长为500us
          5. PB08设置为GTIM的CH3
         

演示说明：
          系统时钟由HSI提供，通过PLL倍频到48MHz。GTIM经16分频后，以3MHz的频率计数，
          ARR设置为1499，GTIM的溢出周期为500us。GTIM每500us进入一次中断，每50ms改变
          一次CH3的CCR寄存器的值，即改变PWM的正脉宽，步长为5us，先递增到ARR，然后递减
          到0，如此反复，LED2将逐步变亮，然后逐步变暗，如此反复。
          
使用说明：
+ EWARM
          1. 打开project.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开project.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)
