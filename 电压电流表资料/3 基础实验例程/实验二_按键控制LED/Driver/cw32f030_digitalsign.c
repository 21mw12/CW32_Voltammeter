/**
 * @file cw32f030_digitalsign.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-14
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
#include "cw32f030_digitalsign.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief ��ȡоƬ�ͺ�
 * 
 * @param pChipType  : ���оƬ���͵�Buffer���22�ֽ�
 */
void DIGITALSIGN_GetChipType(uint8_t *pChipType)
{
    uint8_t tmpcnt = 0;

    while( tmpcnt < CHIP_TYPE_LENGTH )
    {
        * (uint8_t *)(pChipType + tmpcnt)  = *( (uint8_t *) (CHIP_TYPE_BASE + tmpcnt ) );
        tmpcnt ++;
    }    
}

/**
 * @brief ��ȡоƬ������
 * 
 * @return uint16_t 
 */
uint16_t DIGITALSIGN_GetPinCount(void)
{
     return ( *( (uint16_t *) PIN_COUNT_BASE ) );    
}

/**
 * @brief  //��ȡFLASH����//
 * 
 * @return uint32_t 
 */
uint32_t DIGITALSIGN_GetFlashSize(void)
{
     return ( *( (uint32_t *) FLASH_SIZE_BASE ) );
}

/**
 * @brief  //��ȡRAM����//
 * 
 * @return uint32_t 
 */
uint32_t DIGITALSIGN_GetRamSize(void)
{
     return ( *( (uint32_t *) RAM_SIZE_BASE ) );
}

/**
 * @brief ��ȡоƬUID 
 * 
 * @param pChipUid : ���оƬUID��Buffer��10�ֽ�
 */
void DIGITALSIGN_GetChipUid(uint8_t *pChipUid)
{
    uint8_t tmpcnt = 0;

    while( tmpcnt < CHIP_UID_LENGTH )
    {
        * (uint8_t *)(pChipUid + tmpcnt)  = *( (uint8_t *) (CHIP_UID_BASE + tmpcnt ) );
        tmpcnt ++;
    }
}


