#ifndef _FLASH_H_
#define _FLASH_H_
#include "cw32f003_flash.h"

void FLASH_Erase(void);
void FLASH_Write(uint16_t offset, uint16_t *data, uint16_t lenght);
void FLASH_Read(uint16_t offset, uint16_t *data, uint16_t lenght);
#endif
