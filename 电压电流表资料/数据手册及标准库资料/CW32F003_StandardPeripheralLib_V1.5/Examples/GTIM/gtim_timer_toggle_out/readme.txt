示例目的：
          演示GTIM的TOGGLE输出功能。

硬件资源：
          1. cw32f003C8T6 StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI，不分频，48MHz， PCLK、HCLK不分频，
             PCLK=HCLK=SysClk=48MHz
          4. GTIM的分频系数设置为1024，ARR设置为48000000/1024/5-1，则GTIM每
             200ms溢出一次。          
          5. PB01，PB00复用为GTIM_TOGN，GTIM_TOGP
          6. 设置PA07为PUSH-PULL输出,驱动LED1

演示说明：
          程序运行后,PB00和PB01以2.5Hz的频率输出互补的方便，PB01的波形和PA07的
          波形的相位一致。LED1以200ms的间隔闪烁。
          
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
