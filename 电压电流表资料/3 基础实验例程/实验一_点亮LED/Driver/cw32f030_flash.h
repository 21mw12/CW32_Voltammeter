/**
 * @file cw32f030_flash.h
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
#ifndef __CW32F03x_FLASH_H__
#define __CW32F03x_FLASH_H__

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

/** @defgroup FLASH״̬ 
  * @{
  */ 
#define FLASH_FLAG_OK                  (0UL)
#define FLASH_FLAG_BSY                 (bv5)  /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR               (bv4)  /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTERR            (bv1)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_PCERR               (bv0)  /*!< FLASH PC error flag */
#define FLASH_ERROR_ADDR               0x80

/** @defgroup ������������ʱ 
  * @{
  */ 
#define FLASH_Latency_1                ((uint32_t)0x00000000)  /*!< FLASH One Latency cycle */
#define FLASH_Latency_2                ((uint32_t)0x00000001)  /*!< FLASH Two Latency cycles */
#define FLASH_Latency_3                ((uint32_t)0x00000002)  /*!< FLASH THREE Latency cycles */
#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2) || \
                                   ((LATENCY) == FLASH_Latency_3)) 

/** @defgroup FETCH���� 
  * @{
  */
#define FLASH_Prefetch_Enable    ((uint32_t)0x00000008)  /*!< FLASH Prefetch Enable */
#define FLASH_Prefetch_Disable   ((uint32_t)0x00000000)  /*!< FLASH Prefetch Disable */
#define IS_FLASH_PREFETCH_STATE(STATE) (((STATE) == FLASH_Prefetch_Enable) || \
                                              ((STATE) == FLASH_Prefetch_Disable)) 

/** @defgroup CACHE���� 
  * @{
  */
#define FLASH_Cache_Enable    ((uint32_t)0x00000010)  /*!< FLASH Buffer Enable */
#define FLASH_Cache_Disable   ((uint32_t)0x00000000)  /*!< FLASH Buffer Disable */
#define IS_FLASH_CACHE_STATE(STATE) (((STATE) == FLASH_Cache_Enable) || \
                                              ((STATE) == FLASH_Cache_Disable)) 

/** @defgroup �������ȼ� 
  * @{
  */
#define FLASH_RDLEVEL0  ((uint16_t)0x00)    
#define FLASH_RDLEVEL1  ((uint16_t)0x01)
#define FLASH_RDLEVEL2  ((uint16_t)0x02)
#define FLASH_RDLEVEL3  ((uint16_t)0x03)
#define IS_FLASH_RDLEVEL(LEVEL)  (((LEVEL) == FLASH_RDLEVEL0) || \
                                  ((LEVEL) == FLASH_RDLEVEL1) || \
                                  ((LEVEL) == FLASH_RDLEVEL2) || \
                                  ((LEVEL) == FLASH_RDLEVEL3))

/** @defgroup �жϱ�־λ 
  * @{
  */
#define FLASH_IT_PROG                     (bv4)
#define FLASH_IT_PAGELOCK                 (bv1)
#define FLASH_IT_PC                       (bv0)
#define IS_FLASH_IT(IT)                   (((IT) & 0xFFFFFFEC == 0x0UL) && ((IT) != 0x0UL))
#define IS_FLASH_GET_IT(IT)              (((IT) == FLASH_IT_PROG) || \
                                          ((IT) == FLASH_IT_PAGELOCK) || \
                                          ((IT) == FLASH_IT_PC)) 

 /** @defgroup FLASHҳ 
  * @{
  */ 
#define FLASH_WRProt_AllPages            ((uint32_t)0x0000FFFF) /*!< Write protection of all Pages */
#define IS_FLASH_PAGE_Number(PAGENUMBER) (((PAGENUMBER) >= 0) && ((PAGENUMBER) <= 127))
#define IS_FLASH_ADDRESS(ADDRESS)        (((ADDRESS) >= 0x00000000) && ((ADDRESS) < 0x00010000))

//============================================================ 
//����FLASH����������
void FLASH_SetLatency( uint32_t FLASH_Latency );
//����Ԥȡʹ��
void FLASH_PrefetchCmd(uint32_t FLASH_Prefetch);
//����BUFFERʹ��
void FLASH_CacheCmd(uint32_t FLASH_Buffer);
//��ȡFLASH��Fetch״̬
FlagStatus FLASH_GetPrefetchStatus(void);
//��ȡFLASH��Cache״̬
FlagStatus FLASH_GetCacheStatus(void);
//��ȡFLASH�Ķ������ȼ�
uint8_t FLASH_GetReadOutLevel( void );
//����FLASH�Ķ������ȼ�
void FLASH_SetReadOutLevel( uint16_t RdLevel );
//����FLASH����ҳ��
void FLASH_UnlockAllPages(void);
//����FLASH����ҳ��
void FLASH_LockAllPages( void );
//����FLASHָ��ҳ�棺����ҳ��Ž�����0~127
uint8_t FLASH_UnlockPage( uint8_t Page_Number );
//����FLASHָ��ҳ�棺������ʼ����ֹ��ַ����
uint8_t FLASH_UnlockPages( uint32_t StartAddr , uint32_t EndAddr );
//����FLASHָ��ҳ�棺����ҳ��Ų�����0~127
uint8_t FLASH_ErasePage( uint8_t Page_Number );
//����FLASHָ��ҳ�棺������ʼ����ֹ��ַ����
uint8_t FLASH_ErasePages( uint32_t StartAddr , uint32_t EndAddr );
//ָ����ַ��ʼдһ�����ȵ����ݣ������ֽ�д
uint8_t FLASH_WirteBytes( uint32_t WriteAddr, uint8_t *pWrBuf , uint16_t WrByteCnt );
//����FLASHָ��ҳ�棺����ҳ���������0~127
uint8_t FLASH_LockPage( uint8_t Page_Number );
//����FLASHָ��ҳ�棺������ʼ����ֹ��ַ����
uint8_t FLASH_LockPages( uint32_t StartAddr , uint32_t EndAddr );
//FLASHָ���ж�ʹ������
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
//��ȡָ��FLASH�жϱ�־λ
ITStatus FLASH_GetITStatus(uint32_t FLASH_IT);
//���ָ��FLASH�жϱ�־λ
void FLASH_ClearITPendingBit(uint32_t FLASH_IT);
//��ȡFLASHģ�鵱ǰ״̬//
uint32_t FLASH_GetStatus(void);

//============================================================

#ifdef __cplusplus
}
#endif

#endif
