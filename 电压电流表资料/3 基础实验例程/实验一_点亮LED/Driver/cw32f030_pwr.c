/**
 * @file cw32f030_pwr.c
 * @author P&S (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-19
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "cw32f030.h"
#include "cw32f030_pwr.h"

/**
 *******************************************************************************
 ** \addtogroup LpmGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*
#define IS_VALID_SEVONPEND(x)           (SevPndDisable == (x) ||\
                                         SevPndEnable  == (x))
#define IS_VALID_SLEEPDEEP(x)           (SlpDpDisable  == (x) ||\
                                         SlpDpEnable   == (x))
#define IS_VALID_SLEEPONEXIT(x)         (SlpExtDisable == (x) ||\
                                         SlpExtEnable  == (x))                                         
*/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief �͹���ģʽ����
 *
 * @param PWR_InitTypeDef      �͹���ģʽ���ýṹ��ָ��
 *
 * @return
 */
void PWR_Config(PWR_InitTypeDef* PWR_InitTypeDef)
{
    ASSERT(NULL != PWR_InitTypeDef);
    assert_param(IS_PWR_SEVONPEND(PWR_InitTypeDef->PWR_Sevonpend));
    assert_param(IS_PWR_SLEEPDEEP(PWR_InitTypeDef->PWR_SleepDeep));
    assert_param(IS_PWR_SLEEPONEXIT(PWR_InitTypeDef->PWR_SleepOnExit));
    
/*
    SCB->SCR = PWR_InitTypeDef->PWR_Sevonpend   ? (SCB->SCR | SCB_SCR_SEVONPEND_Msk)   : (SCB->SCR & ~SCB_SCR_SEVONPEND_Msk);
    SCB->SCR = PWR_InitTypeDef->PWR_SleepDeep   ? (SCB->SCR | SCB_SCR_SLEEPDEEP_Msk)   : (SCB->SCR & ~SCB_SCR_SLEEPDEEP_Msk);
    SCB->SCR = PWR_InitTypeDef->PWR_SleepOnExit ? (SCB->SCR | SCB_SCR_SLEEPONEXIT_Msk) : (SCB->SCR & ~SCB_SCR_SLEEPONEXIT_Msk);
*/

    REGBITS_MODIFY(SCB->SCR, SCB_SCR_SEVONPEND_Msk | \
					SCB_SCR_SLEEPDEEP_Msk | \
					SCB_SCR_SLEEPONEXIT_Msk, \
					PWR_InitTypeDef->PWR_Sevonpend | \
					PWR_InitTypeDef->PWR_SleepDeep | \
					PWR_InitTypeDef->PWR_SleepOnExit);
}

/**
 * @brief ����˯��ģʽ
 *
 * @return
 */
void PWR_GotoLpmMode(void)
{
    __WFI();
}
                        
//@} // LpmGroup                                                                           

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
