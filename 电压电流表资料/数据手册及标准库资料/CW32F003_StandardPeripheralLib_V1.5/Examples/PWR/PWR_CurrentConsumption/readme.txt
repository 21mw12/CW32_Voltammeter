ʾ��Ŀ�ģ�
          ��ʾMCUͨ����������/�˳����ߺ��������ģʽ��

Ӳ����Դ��
          1. CW32F0003Fx StartKit
          2. ʱ��HSI
          3. ϵͳʱ��ԴΪHSIʱ��2��Ƶ��24MHz�� PCLK��HCLK����Ƶ��PCLK=HCLK=SysClk=24MHz
          4. PB06����Ϊ����(KEY2)�ж�����
          5. PA06/07����ΪPUSH-PULL���

��ʾ˵����
          �ϵ��MCU������������ģʽ��PA07(LED1)�����ƽ��ʱ1s���Ϸ�ת��
		  ��һ�ΰ���KEY2��MCU�������߻����������ģʽ��LED1Ϩ��
		  ��һ�ΰ���KEY2��MCU�˳����߻����������ģʽ��LED1�����Ҳ��Ϸ�ת��MCU������������ģʽ��
		  ע�⣺�޸�cw32f003_pwr_modes.h�еĺ궨�壬����ѡ��͹���ģʽ��
		  
          
ʹ��˵����
+ EWARM
          1. ��PWR_CurrentConsumption.eww�ļ�
          2. ���������ļ���Project->Rebuild all
          3. ���빤�̾���Project->Debug
          4. ���г���Debug->Go(F5)

+ MDK-ARM
          1. ��PWR_CurrentConsumption.uvproj�ļ�
          2. ���������ļ���Project->Rebuild all target files
          3. ���빤�̾���Debug->Start/Stop Debug Session
          4. ���г���Debug->Run(F5)