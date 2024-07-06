示例目的：
          利用PCLK时钟输出功能将PCLK时钟从PB03引脚输出。

硬件资源：
          1. cw32f003C8T6 StartKit  或者cw32f003CxT6 StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI时钟2分频，24MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=24MHz

演示说明：
        采用默认时钟配置，并设置PCLK时钟输出，用示波器观测PB03引脚的波形，默认程序为24MHz。

使用说明：
+ EWARM
          1. 打开project.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开rcc_pclkout.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)
