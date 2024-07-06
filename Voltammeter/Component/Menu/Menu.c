#include "Menu.h"
#include "Nixie.h"

#define DotOffest		10		// ��ʾС����ƫ����

void Menu_VA(uint16_t VData, uint16_t AData) {	
	/* 
	 * ����ѹС��1V������λ����ʾ����ֵ
	 * ����ѹС��10V���ڵ���1V�������λ������ֵ
	 * ����ѹ���ڵ���10V�������λ������ֵ
	 */
	if (VData >= 10000) {
		VData /= 100;
		
		NixieShowNumInfo[0] = VData % 10;
		NixieShowNumInfo[1] = VData / 10 % 10 + DotOffest;
		NixieShowNumInfo[2] = VData / 100 % 10;
	}
	else if (VData >= 1000) {
		VData /= 10;
		
		NixieShowNumInfo[0] = VData % 10;
		NixieShowNumInfo[1] = VData / 10 % 10;
		NixieShowNumInfo[2] = VData / 100 % 10 + DotOffest;
	}
	else {
		/* ����ѹ��ÿһλ�������ʾ���������� */
		NixieShowNumInfo[0] = VData % 10;
		NixieShowNumInfo[1] = VData / 10 % 10;
		NixieShowNumInfo[2] = VData / 100 % 10;
	}
	
	
	/*
   * ������С��1A������λ����ʾ����ֵ
   * ���������ڵ�1AС��10A�������λ��ʾ����ֵ
	 */
	if (AData >= 1000) {
		AData /= 10;
		
		NixieShowNumInfo[3] = AData % 10;
		NixieShowNumInfo[4] = AData / 10 % 10;
		NixieShowNumInfo[5] = AData / 100 % 10 + DotOffest;
	}
	else {
		/* ��������ÿһλ�������ʾ���������� */
		NixieShowNumInfo[3] = AData % 10;
		NixieShowNumInfo[4] = AData / 10 % 10;
		NixieShowNumInfo[5] = AData / 100 % 10;
	}
}

void Menu_OnlyV(uint16_t VData) {
	/* �ڵ�һ�е�һλ��ʾ��V�� */
	NixieShowNumInfo[2] = 20;
	
	NixieShowNumInfo[0] = VData / 1000 % 10 + DotOffest;
	NixieShowNumInfo[1] = VData / 10000 % 10;
	NixieShowNumInfo[3] = VData % 10;
	NixieShowNumInfo[4] = VData / 10 % 10;
	NixieShowNumInfo[5] = VData / 100 % 10;
}

void Menu_OnlyA(uint16_t AData) {	
	/* �ڵ�һ�е�һλ��ʾ��A�� */
	NixieShowNumInfo[2] = 21;
	
	NixieShowNumInfo[0] = AData / 1000 % 10 + DotOffest;
	NixieShowNumInfo[1] = AData / 10000 % 10;
	NixieShowNumInfo[3] = AData % 10;
	NixieShowNumInfo[4] = AData / 10 % 10;
	NixieShowNumInfo[5] = AData / 100 % 10;
}

void Menu_SetV1(uint16_t VData) {
	/* �ڵ�һ����ʾ��V1�� */
	NixieShowNumInfo[2] = 20;
	NixieShowNumInfo[1] = 1;
	NixieShowNumInfo[0] = 22;
	
	/* �ڵڶ�����ʾ�ɼ�ֵ�ĺ���λ */	
	NixieShowNumInfo[3] = VData % 10;
	NixieShowNumInfo[4] = VData / 10 % 10;
	NixieShowNumInfo[5] = VData / 100 % 10;
}

void Menu_SetV2(uint16_t VData) {
	/* �ڵ�һ����ʾ��V2�� */
	NixieShowNumInfo[2] = 20;
	NixieShowNumInfo[1] = 2;
	NixieShowNumInfo[0] = 22;
	
	NixieShowNumInfo[3] = VData % 10;
	NixieShowNumInfo[4] = VData / 10 % 10;
	NixieShowNumInfo[5] = VData / 100 % 10;
}

void Menu_SetA1(uint16_t AData) {
	/* �ڵ�һ����ʾ��A1�� */
	NixieShowNumInfo[2] = 21;
	NixieShowNumInfo[1] = 1;
	NixieShowNumInfo[0] = 22;
	
	NixieShowNumInfo[3] = AData % 10;
	NixieShowNumInfo[4] = AData / 10 % 10;
	NixieShowNumInfo[5] = AData / 100 % 10;
}

void Menu_SetA2(uint16_t AData) {
	/* �ڵ�һ����ʾ��A2�� */
	NixieShowNumInfo[2] = 21;
	NixieShowNumInfo[1] = 2;
	NixieShowNumInfo[0] = 22;
	
	NixieShowNumInfo[3] = AData % 10;
	NixieShowNumInfo[4] = AData / 10 % 10;
	NixieShowNumInfo[5] = AData / 100 % 10;
}
