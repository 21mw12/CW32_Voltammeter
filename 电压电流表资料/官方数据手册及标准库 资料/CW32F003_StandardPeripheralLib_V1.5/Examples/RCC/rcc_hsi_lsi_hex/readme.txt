示例目的：
          系统时钟源在HSI\LSI\HEX之间进行切换。

硬件资源：
          1. cw32f003C8T6 StartKit  或者cw32f003CxT6 StartKit
          2. 时钟HSI和LSI, PB0端口上输入的外部时钟
          3. HSI作为系统时钟时，设置为HSIOSC到HSI时钟的分频比为2，则SysClk为24MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=24MHz
          4. LSI作为系统时钟时，32.8K。PCLK、HCLK不分频，PCLK=HCLK=SysClk=32.8KHz。

演示说明：
        通过按键KEY1（PB05），程序循环在HSI、LSI、HEX时钟之间进行切换，LED1（PA07）的闪烁的快慢表示当前允许的系统时钟的频率高低。

使用说明：
+ EWARM
          1. 打开project.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开rcc_hsi_lsi.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)
