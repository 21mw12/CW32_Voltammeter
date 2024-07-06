/**
 * @file cw32f030_ram.c
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
#include "cw32f030_ram.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief   RAM�ж�����
 * 
 * @param RAM_IT     : RAM_IT_PARITY
 * @param NewState   : ENABLE  DISABLE
 */
void RAM_ITConfig(uint32_t RAM_IT, FunctionalState NewState)
{
    assert_param(IS_RAM_IT(RAM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
   
    if (NewState != DISABLE)
    {
        CW_RAM->IER |= RAM_IT;
    }
    else
    {
        CW_RAM->IER &= (~RAM_IT);
    }
}

/**
 * @brief ��ȡRAM�жϱ�־
 * 
 * @param RAM_IT     : RAM_IT_PARITY
 * @return ITStatus    : SET  RESET
 */
ITStatus RAM_GetITStatus(uint32_t RAM_IT)
{
    assert_param(IS_RAM_GET_IT(RAM_IT));

    return (CW_RAM->ISR & RAM_IT) ? SET : RESET;
}

/**
 * @brief ���RAM�жϱ�־
 * 
 * @param RAM_IT   : RAM_IT_PARITY
 */
void RAM_ClearITPendingBit(uint32_t RAM_IT)
{
    assert_param(IS_RAM_IT(RAM_IT));

    CW_RAM->ICR &= (~RAM_IT);
}

/**
 * @brief ��ȡ������żУ����RAM��ַ
 * 
 * @return uint32_t     
 */
uint32_t RAM_GetErrorAddress(void)
{ 
    return (CW_RAM->ADDR);
}

