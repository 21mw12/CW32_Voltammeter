示例目的：
          演示GTIM的GATE控制计数。

硬件资源：
          1. cw32f003C8T6 StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI，不分频，48MHz， PCLK、HCLK不分频，
             PCLK=HCLK=SysClk=48MHz
          4. GTIM的分频系数设置为1024，ARR设置为48000000/1024/5-1，则GTIM每
             200ms溢出一次。       
          5. 设置PA2为输入复用，GTIM_ETR, 
          6. 设置PA07为PUSH-PULL输出,驱动LED1
          7. 设置GTIM_ETR的极性为低电平有效
          8. 设置PB05为输入,KEY1。
          9. 使能GTIM的中断溢出。

演示说明：
          使用杜邦线将PA2与PB5连接，按下KEY1键，并保持，则LED1以200ms的间隔闪烁。
          
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
