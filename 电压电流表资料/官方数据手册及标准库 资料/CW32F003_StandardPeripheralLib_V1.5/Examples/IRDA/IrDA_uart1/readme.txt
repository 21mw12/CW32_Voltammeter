示例目的：
          演示GTIM和UART1联合产生IrDA的输出波形

硬件资源：
          1. CW32F003Fx StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI时钟1分频，48MHz，PCLK、HCLK不分频，
             PCLK=HCLK=SysClk=48MHz
          4. GTIM生成115.2kHz载波
          5. UART1的TXD调制GTIM的产生的载波。

演示说明：
         PA04输出IrDA调制的波形。

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
