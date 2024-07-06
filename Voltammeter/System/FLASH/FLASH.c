#include "FLASH.h"
#include "cw32f003_flash.h"

#define PAGE_SIZE 		512				// 页大小
#define PAGE_NUM 			1					// 页数量
#define START_ADDR 		(39 * PAGE_SIZE) 						// 起始地址
#define END_ADDR 			(START_ADDR + PAGE_SIZE -1)	// 结束地址

/**
  * @brief 擦除flash最后一页
  * @return 无
  */
void FLASH_Erase(void) {
	FLASH_UnlockPages(START_ADDR, END_ADDR);       // 解锁最后一个页面
	uint8_t flag = FLASH_ErasePages(START_ADDR, END_ADDR); // 擦除最后一个页面
	FLASH_LockAllPages();

	if (flag) {
			while (1); // 擦除失败
	}
}

void FLASH_Write(uint16_t offset, uint16_t *data, uint16_t lenght) {
	FLASH_Erase();	// 写入之前要先擦除

	FLASH_UnlockPages(START_ADDR, END_ADDR); // 解锁最后一个页面
	uint8_t flag = FLASH_WirteHalfWords(START_ADDR + offset * 2, data, lenght);
	FLASH_LockAllPages();

	if (flag) {
			while (1); // 写入失败
	}
}

void FLASH_Read(uint16_t offset, uint16_t *data, uint16_t lenght) {
	
	for (uint16_t i = 0; i < lenght; i++) {
			*data++ = *((volatile uint16_t *)(START_ADDR + offset * 2 + i * 2));
	}
}
