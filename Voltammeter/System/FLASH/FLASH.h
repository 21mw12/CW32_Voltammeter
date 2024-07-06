#ifndef _FLASH_H_
#define _FLASH_H_

////////////////////////////////////////////////////////////////////////////
//
// 文件功能：读写Flash功能
// 作者：CW32官方
//
//	原作者信息在上，这里只做个人的二次理解并转换为个人的代码风格！！！
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/**
  * @brief 写入flash
  * @param offset 起始偏移量
  * @param data 存入数据
  * @param lenght 存入数据长度
  * @return 
  */
void FLASH_Write(uint16_t offset, uint16_t *data, uint16_t lenght);

/**
  * @brief 读出flash
  * @param offset 起始偏移量
  * @param data 读出数据
  * @param lenght 读出数据长度
  * @return 
  */
void FLASH_Read(uint16_t offset, uint16_t *data, uint16_t lenght);
#endif
