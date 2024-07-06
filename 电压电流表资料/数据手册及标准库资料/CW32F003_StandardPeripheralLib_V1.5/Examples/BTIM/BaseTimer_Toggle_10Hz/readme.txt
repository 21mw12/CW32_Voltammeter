示例目的：
          演示基本定时器BTIM的TOG输出功能，不需要中断和口线寄存器的操作，完全由硬件实现方波的输出。

硬件资源：
          1. cw32f003C8T6 StartKit
          2. 时钟HSI，6分频，8MHz
          3. PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz
          4. BTIM1的时钟设置为PCLK，128分频，
          5. PA00,PB02,PC01,PC02设置为PUSH-PULL输出, 复用为BTIM1的TOG输出
          6. PA07(LED1)设置为PUSH-PULL输出
          7. PA06(LED1)设置为PUSH-PULL输出



演示说明：
          BTIM1的计数时钟为8MHz/128=62500Hz，设置ARR寄存器为62500 / 20 - 1，BTIM1每50ms溢出一次；
          溢出后，触发中断服务程序。中断服务程序中，PA07输出翻转，LED1闪烁，用于指示。
          PB02和PC00输出TOGP，PA00和PC01输出TOGN，可以示波器观测波形。
          

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
