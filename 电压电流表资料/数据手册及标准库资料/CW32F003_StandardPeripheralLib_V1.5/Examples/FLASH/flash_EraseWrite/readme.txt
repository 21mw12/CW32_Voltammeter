示例目的：
          对MCU内置的FLASH的最后一个页面（第127页）依次进行擦除/写/读操作，并对比写入和读取的数据是否一致。

硬件资源：
          1. cw32f003C8T6 StartKit  或者cw32f003CxT6 StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI时钟6分频，8MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz

演示说明：
        采用默认时钟配置，开启FLASH的操作时钟。依次对MCU内置FLASH的最后一个页面（127页）进行擦除、写以及读取，然后对比写入和读取的数据是否相同。如果擦除、写、读取数据操作或者读写数据不一致则挂起，否则完成后会闪灯提示。

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
