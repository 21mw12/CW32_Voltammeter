示例目的：
          UART多机通信模式示例。

硬件资源：
          1. CW32F003 StartKit
          2. 时钟HSIOSC
          3. 系统时钟设置为HSIOSC时钟6分频，8MHz，PCLK、HCLK不分频，PCLK=HCLK=SysClk=8MHz
          4. UART的传输时钟设置为PCLK
          5. LED1_GPIO_PORT设置为PUSH-PULL输出
		  6. LED2_GPIO_PORT设置为PUSH-PULL输出

演示说明：
          USARTy（主机）发送地址帧0xA5寻址到USARTz（从机）。
		  
          USARTy（主机）查询方式（TXE）发送TxBuffer1缓冲区中的数据；
          USARTz（从机）中断方式接收数据帧，并存储到RxBuffer2缓冲区，同时发送TxBuffer2缓冲区中的数据到USARTy（主机）；
          USARTy（主机）查询方式（RC）接收数据，并存储到RxBuffer1缓冲区。
		  
          比较TxBuffer1和RxBuffer2、TxBuffer2和RxBuffer1，
          如果数据一致，LED1亮，否则LED2亮。

硬件连接：
          UART1_TXD (PB02) -- UART2_RXD (PB03)
          UART1_RXD (PA00) -- UART2_TXD (PB04)

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
