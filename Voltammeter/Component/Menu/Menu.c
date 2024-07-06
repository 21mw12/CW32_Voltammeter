#include "Menu.h"
#include "Nixie.h"

#define DotOffest		10		// 显示小数点偏移量

void Menu_VA(uint16_t VData, uint16_t AData) {	
	/* 
	 * 若电压小于1V，则三位均显示毫伏值
	 * 若电压小于10V大于等于1V，则后两位均毫伏值
	 * 若电压大于等于10V，则后两位均毫伏值
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
		/* 将电压的每一位存放在显示缓存数组中 */
		NixieShowNumInfo[0] = VData % 10;
		NixieShowNumInfo[1] = VData / 10 % 10;
		NixieShowNumInfo[2] = VData / 100 % 10;
	}
	
	
	/*
   * 若电流小于1A，则三位均显示毫安值
   * 若电流大于等1A小于10A，则后两位显示毫安值
	 */
	if (AData >= 1000) {
		AData /= 10;
		
		NixieShowNumInfo[3] = AData % 10;
		NixieShowNumInfo[4] = AData / 10 % 10;
		NixieShowNumInfo[5] = AData / 100 % 10 + DotOffest;
	}
	else {
		/* 将电流的每一位存放在显示缓存数组中 */
		NixieShowNumInfo[3] = AData % 10;
		NixieShowNumInfo[4] = AData / 10 % 10;
		NixieShowNumInfo[5] = AData / 100 % 10;
	}
}

void Menu_OnlyV(uint16_t VData) {
	/* 在第一行第一位显示“V” */
	NixieShowNumInfo[2] = 20;
	
	NixieShowNumInfo[0] = VData / 1000 % 10 + DotOffest;
	NixieShowNumInfo[1] = VData / 10000 % 10;
	NixieShowNumInfo[3] = VData % 10;
	NixieShowNumInfo[4] = VData / 10 % 10;
	NixieShowNumInfo[5] = VData / 100 % 10;
}

void Menu_OnlyA(uint16_t AData) {	
	/* 在第一行第一位显示“A” */
	NixieShowNumInfo[2] = 21;
	
	NixieShowNumInfo[0] = AData / 1000 % 10 + DotOffest;
	NixieShowNumInfo[1] = AData / 10000 % 10;
	NixieShowNumInfo[3] = AData % 10;
	NixieShowNumInfo[4] = AData / 10 % 10;
	NixieShowNumInfo[5] = AData / 100 % 10;
}

void Menu_SetV1(uint16_t VData) {
	/* 在第一行显示“V1” */
	NixieShowNumInfo[2] = 20;
	NixieShowNumInfo[1] = 1;
	NixieShowNumInfo[0] = 22;
	
	/* 在第二行显示采集值的后三位 */	
	NixieShowNumInfo[3] = VData % 10;
	NixieShowNumInfo[4] = VData / 10 % 10;
	NixieShowNumInfo[5] = VData / 100 % 10;
}

void Menu_SetV2(uint16_t VData) {
	/* 在第一行显示“V2” */
	NixieShowNumInfo[2] = 20;
	NixieShowNumInfo[1] = 2;
	NixieShowNumInfo[0] = 22;
	
	NixieShowNumInfo[3] = VData % 10;
	NixieShowNumInfo[4] = VData / 10 % 10;
	NixieShowNumInfo[5] = VData / 100 % 10;
}

void Menu_SetA1(uint16_t AData) {
	/* 在第一行显示“A1” */
	NixieShowNumInfo[2] = 21;
	NixieShowNumInfo[1] = 1;
	NixieShowNumInfo[0] = 22;
	
	NixieShowNumInfo[3] = AData % 10;
	NixieShowNumInfo[4] = AData / 10 % 10;
	NixieShowNumInfo[5] = AData / 100 % 10;
}

void Menu_SetA2(uint16_t AData) {
	/* 在第一行显示“A2” */
	NixieShowNumInfo[2] = 21;
	NixieShowNumInfo[1] = 2;
	NixieShowNumInfo[0] = 22;
	
	NixieShowNumInfo[3] = AData % 10;
	NixieShowNumInfo[4] = AData / 10 % 10;
	NixieShowNumInfo[5] = AData / 100 % 10;
}
