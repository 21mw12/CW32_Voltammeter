示例目的：
          演示GPIO通过库函数和宏定义的方法完整初始化配置和输入输出的读写操作

硬件资源：
          1. CW32f003Fx StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI时钟6分频，8MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz
          4. PA00 / PA01 / PA02 / PA03 输出，PA08 / PA09输入上拉

演示说明：
          进入DeepSleep mode前，LED1亮，按下KEY1，进入DeepSleep mode，LED1熄灭。
          按下KEY1或KEY2可唤醒MCU，LED2翻转，变量tmp记录唤醒次数，然后再次进入DeepSleep mode。

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
