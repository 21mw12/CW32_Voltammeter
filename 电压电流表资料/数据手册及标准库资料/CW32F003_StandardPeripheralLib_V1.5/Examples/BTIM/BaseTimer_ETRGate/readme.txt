示例目的：
          演示基本定时器BTIM的门控功能。BTIM的使能信号EN设置为有效时，需门控信号有效，定时器方才计数。

硬件资源：
          1. cw32f003C8T6 StartKit
          2. 时钟HSI
          3. 系统时钟设置为HSI时钟6分频，8MHz， PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz
          4. BTIM1的时钟设置为PCLK，8分频，门控模式
          5. PA05复用功能配置为BTIM_ETR，作为GATE信号的输入端口, PCLK,6点滤波
          6. PA07(LED1)设置为PUSH-PULL输出
          7. PA06(LED2)设置为PUSH-PULL输出
          8. BTIM2的时钟设置为PCLK， 512分频
          9. PA01设置为BTIM2的TOGP输出


演示说明：
          BTIM1配置为门控功能，以1MHz时钟进行计数，设置ARR寄存器为49999；
          BTIM2配置为定时模式，以15625Hz时钟频率计数，设置ARR寄存器为15624，设置TOGP输出使能，
          PA01的电平每1s翻转一次。
          BTIM2每秒钟溢出一次，溢出后，触发中断服务程序。中断服务程序中，PA06输出电平翻转，并
          保持和PA01相同的极性，LED2将2Hz的频率闪烁。
          使用杜邦线将PA01脚与PA05脚连接，则当PA01输出高电平时，LED2亮起，BTIM1将每50ms溢出一次，
          并触发中断服务程序。中断服务程序中，PA07输出电平翻转，LED1将10Hz的频率闪烁。
          当PA01输出低电平时，LED2灭，BTIM1停止计数，LED1不闪烁。
          

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
