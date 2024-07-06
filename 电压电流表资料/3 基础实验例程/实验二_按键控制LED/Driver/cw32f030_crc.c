/**
 * @file cw32f030_crc.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
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

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_crc.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief ����8bit��ʽ������CRC16
 * 
 * @param CrcMode    : CRC16_IBM    CRC16_MAXIM
 *                     CRC16_USB    CRC16_MODBUS
 *                     CRC16_CCITT  CRC16_CCITTFALSE
 *                     CRC16_X25    CRC16_XMODEM
 * @param pByteBuf   : uint8_t��Bufferָ��
 * @param ByteCnt    ��0x01 - 0xFFFF
 * @return uint16_t  ��0x00 - 0xFFFF
 */
uint16_t CRC16_Calc_8bit( uint8_t CrcMode , uint8_t *pByteBuf , uint16_t ByteCnt )
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC16_MODE(CrcMode));   
    CW_CRC->CR = CrcMode;
    while ( ByteCnt )
    {
        CW_CRC->DR8 = *pByteBuf;
        pByteBuf++;
        ByteCnt--;
    }
    return( CW_CRC->RESULT16 );
}


/**
 * @brief   ����16bit��ʽ������CRC16
 * 
 * @param CrcMode        : CRC16_IBM    CRC16_MAXIM
 *                         CRC16_USB    CRC16_MODBUS
 *                         CRC16_CCITT  CRC16_CCITTFALSE
 *                         CRC16_X25    CRC16_XMODEM
 * @param pHWBuf         : uint16_t��Bufferָ��
 * @param HalfWordCnt    ��0x01 - 0xFFFF
 * @return uint16_t      ��0x00 - 0xFFFF
 */
uint16_t CRC16_Calc_16bit( uint8_t CrcMode , uint16_t *pHWBuf , uint16_t HalfWordCnt )
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC16_MODE(CrcMode));   

    CW_CRC->CR = CrcMode;
    while ( HalfWordCnt )
    {
        CW_CRC->DR16 = *pHWBuf;
        pHWBuf++;
        HalfWordCnt--;
    }
    return( CW_CRC->RESULT16 );
}


/**
 * @brief   ����32bit��ʽ������CRC16
 * 
 * @param CrcMode    : CRC16_IBM    CRC16_MAXIM
 *                     CRC16_USB    CRC16_MODBUS
 *                     CRC16_CCITT  CRC16_CCITTFALSE
 *                     CRC16_X25    CRC16_XMODEM
 * @param pWBuf      : uint32_t��Bufferָ��
 * @param WordCnt    ��0x01 - 0xFFFF
 * @return uint16_t  ��0x00 - 0xFFFF
 */
uint16_t CRC16_Calc_32bit( uint8_t CrcMode , uint32_t *pWBuf , uint16_t WordCnt )
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC16_MODE(CrcMode));   

    CW_CRC->CR = CrcMode;
    while ( WordCnt )
    {
        CW_CRC->DR32 = *pWBuf;
        pWBuf++;
        WordCnt--;
    }
    return( CW_CRC->RESULT16 );
}

/**
 * @brief   ����8bit��ʽ������CRC32
 * 
 * @param CrcMode       : CRC32_DEFAULT   CRC32_MPEG2
 * @param pByteBuf      : uint8_t��Bufferָ��
 * @param ByteCnt       ��0x01 - 0xFFFF
 * @return uint32_t     ��0x00 - 0xFFFF FFFF
 */
uint32_t CRC32_Calc_8bit( uint8_t CrcMode , uint8_t *pByteBuf , uint16_t ByteCnt )
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC32_MODE(CrcMode));   

    CW_CRC->CR = CrcMode;
    while ( ByteCnt )
    {
        CW_CRC->DR8 = *pByteBuf;
        pByteBuf++;
        ByteCnt--;
    }
    return( CW_CRC->RESULT32 );
}


/**
 * @brief ����16bit��ʽ������CRC32
 * 
 * @param CrcMode        : CRC32_DEFAULT   CRC32_MPEG2
 * @param pHWBuf         : uint16_t��Bufferָ��
 * @param HalfWordCnt    ��0x01 - 0xFFFF
 * @return uint32_t      ��0x00 - 0xFFFF FFFF
 */
uint32_t CRC32_Calc_16bit( uint8_t CrcMode , uint16_t *pHWBuf , uint16_t HalfWordCnt )
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC32_MODE(CrcMode)); 

    CW_CRC->CR = CrcMode;
    while ( HalfWordCnt )
    {
        CW_CRC->DR16 = *pHWBuf;
        pHWBuf++;
        HalfWordCnt--;
    }
    return( CW_CRC->RESULT32 );
}


/**
 * @brief   ����32bit��ʽ������CRC16
 * 
 * @param CrcMode       : CRC32_DEFAULT   CRC32_MPEG2 
 * @param pWBuf         : uint32_t��Bufferָ��
 * @param WordCnt       ��0x01 - 0xFFFF
 * @return uint32_t     ��0x00 - 0xFFFF FFFF
 */
uint32_t CRC32_Calc_32bit( uint8_t CrcMode , uint32_t *pWBuf , uint16_t WordCnt )
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC32_MODE(CrcMode)); 

    CW_CRC->CR = CrcMode;
    while ( WordCnt )
    {
        CW_CRC->DR32 = *pWBuf;
        pWBuf++;
        WordCnt--;
    }
    return( CW_CRC->RESULT32 );
}

//=============================================================================

