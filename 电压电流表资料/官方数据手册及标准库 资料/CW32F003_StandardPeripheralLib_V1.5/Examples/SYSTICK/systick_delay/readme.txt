示例目的：
          利用systick定时器完成100mS定时。

Ӳ����Դ��
          1. CW32F003 StartKit
          2. ʱ��HSI
          3. ϵͳʱ������ΪHSIʱ��2��Ƶ��24MHz�� PCLK��HCLK����Ƶ��PCLK=HCLK=SysClk=24MHz

��ʾ˵����
          ����Ĭ��ʱ�����ã�����ʼ��systickΪ1mS��ʱ����systick�ж�32λ��uwTick�������г�����1���������Ϊ0����
          ����������ͨ����ȡuwTick�Ĳ�ֵ����ʱ��������������systickʵ��100mS�Ķ�ʱ����LED����˸��

使用说明：
+ EWARM
          1. 打开project.eww文件
          2. 编译所有文件：Project->Rebuild all
          3. 载入工程镜像：Project->Debug
          4. 运行程序：Debug->Go(F5)

+ MDK-ARM
          1. 打开systick_delay.uvproj文件
          2. 编译所有文件：Project->Rebuild all target files
          3. 载入工程镜像：Debug->Start/Stop Debug Session
          4. 运行程序：Debug->Run(F5)
