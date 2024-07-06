/**
 * @file cw32f030_crc.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/*******************************************************************************
*
* ������ɺ�������Ϣ
* �人��Դ�뵼�����޹�˾������ʹ�����б�̴���ʾ���ķ�ר���İ�Ȩ��ɣ��������ɴ�
* ���ɸ��������ض���Ҫ�����Ƶ����ƹ��ܡ����ݲ��ܱ��ų����κη�����֤���人��Դ��
* �������޹�˾������򿪷��̺͹�Ӧ�̶Գ������֧�֣�����У����ṩ�κ���ʾ��
* ���ı�֤�������������������ڰ������й������ԡ�������ĳ���ض���;�ͷ���Ȩ�ı�֤
* ��������
* ���ۺ������Σ��人��Դ�뵼�����޹�˾������򿪷��̻�Ӧ�̾��������и����
* ��ʹ����֪�䷢���Ŀ�����ʱ��Ҳ����ˣ����ݵĶ�ʧ���𻵣�ֱ�ӵġ��ر�ġ�������
* ���ӵ��𺦣����κκ���Ծ����𺦣�������ҵ�����롢������Ԥ�ڿɽ�ʡ����
* ��ʧ��
* ĳЩ˾��Ͻ���������ֱ�ӵġ������Ļ����Ե������κε��ų������ƣ����ĳЩ��
* ȫ�������ų������ƿ��ܲ�������������
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F03x_CRC_H__
#define __CW32F03x_CRC_H__

#ifdef __cplusplus
 extern "C" {
#endif

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "base_types.h"
#include "cw32f030.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/

//============================================================


uint16_t CRC16_Calc_8bit(  uint8_t CrcMode , uint8_t  *pByteBuf , uint16_t ByteCnt );
uint16_t CRC16_Calc_16bit( uint8_t CrcMode , uint16_t *pHWBuf   , uint16_t HalfWordCnt );
uint16_t CRC16_Calc_32bit( uint8_t CrcMode , uint32_t *pWBuf    , uint16_t WordCnt );

uint32_t CRC32_Calc_8bit(  uint8_t CrcMode , uint8_t  *pByteBuf , uint16_t ByteCnt );
uint32_t CRC32_Calc_16bit( uint8_t CrcMode , uint16_t *pHWBuf   , uint16_t HalfWordCnt );
uint32_t CRC32_Calc_32bit( uint8_t CrcMode , uint32_t *pWBuf    , uint16_t WordCnt );


//============================================================

#define		CRC16_IBM			0x00UL
#define		CRC16_MAXIM			0x01UL
#define		CRC16_USB			0x02UL
#define		CRC16_MODBUS		0x03UL
#define		CRC16_CCITT			0x04UL
#define		CRC16_CCITTFALSE	0x05UL
#define		CRC16_X25			0x06UL
#define		CRC16_XMODEM		0x07UL
#define		CRC32_DEFAULT		0x08UL
#define		CRC32_MPEG2			0x09UL


#define IS_CRC_CRC16_MODE(MODE) (((MODE) == CRC16_IBM)    || \
                                 ((MODE) == CRC16_MAXIM)  || \
                                 ((MODE) == CRC16_USB)    || \
                                 ((MODE) == CRC16_MODBUS) || \
                                 ((MODE) == CRC16_CCITT)  || \
                                 ((MODE) == CRC16_CCITTFALSE) || \
                                 ((MODE) == CRC16_X25)    || \
                                 ((MODE) == CRC16_XMODEM))
#define IS_CRC_CRC32_MODE(MODE) (((MODE) == CRC32_DEFAULT) || \
                                 ((MODE) == CRC32_MPEG2))

//============================================================

#ifdef __cplusplus
}
#endif

#endif
