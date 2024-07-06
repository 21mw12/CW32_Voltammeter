示例目的：
          SPI全双工模式主从通信（查询方式）。

硬件资源：
          1. CW32F003 StartKit
          2. 时钟HSIOSC
          3. 系统时钟设置为HSIOSC时钟2分频，24MHz，PCLK、HCLK不分频，PCLK=HCLK=SysClk=24MHz
          4. SPI，波特率为PCLK的8分频，3Mbps
		  5. LED1_GPIO_PORT设置为PUSH-PULL输出
		  6. LED2_GPIO_PORT设置为PUSH-PULL输出	  

演示说明：
          - 
		  #define  SPI_MASTER //主机模式
          主机查询方式（TXE）将TxBuffer1缓冲区中的数据写入DR寄存器，启动传输。
          主机查询方式（RXNE）读取DR寄存器并存储到RxBuffer1缓冲区。
		  传输完成后，比较TxBuffer2和RxBuffer1，如果数据一致，则LED1亮，否则LED2亮。
		  
		  -
		  #define  SPI_SLAVE  //从机模式
          从机查询方式（TXE）将TxBuffer2缓冲区中的数据写入DR寄存器。
          主机查询方式（RXNE）读取DR寄存器并存储到RxBuffer1缓冲区。
		  传输完成后，比较TxBuffer1和RxBuffer2，如果数据一致，则LED1亮，否则LED2亮。
硬件连接：
          SPI_MASTER SCK  (PA00)-- SPI_SLAVE SCK  (PA00)
          SPI_MASTER MISO (PA04)-- SPI_SLAVE MISO (PA04)
		  SPI_MASTER MOSI (PA01)-- SPI_SLAVE MOSI (PA01)
          SPI_MASTER CS   (PA06)-- SPI_SLAVE CS   (PA06)

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
