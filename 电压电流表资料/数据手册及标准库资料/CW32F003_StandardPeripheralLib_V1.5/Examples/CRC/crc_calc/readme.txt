示例目的：
          测试10种不同CRC算法在3种不同输入位宽方式下的计算结果是否相同。

硬件资源：
          1. cw32f003C8T6 StartKit  或者cw32f003CxT6 StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI时钟6分频，8MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz

演示说明：
          通过调试工具，结合软件断点，依次观察10种不同算法模式在3种不同输入数据位宽方式下得到的结果是否相同。

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
