/**
 * @file cw32f030_flash.c
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
#include "cw32f030_flash.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief ����FLASH�Ķ��ȴ�����
 * 
 * @param FLASH_Latency ��FLASH_Latency_1  FLASH_Latency_2  FLASH_Latency_3
 */
void FLASH_SetLatency( uint32_t FLASH_Latency )
{
    uint32_t tmp8;

    /* Check the parameters */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));

    tmp8 = FLASH_Latency>0 ? ( FLASH_Latency|bv3|bv4 ) : 0;   //WAIT��Ϊ0ʱ����Ҫ����FETCH��CACHE
    CW_FLASH->CR2 = 0x5A5A0000 | tmp8;
}

/**
 * @brief Ԥȡ��������
 * 
 * @param FLASH_Prefetch ��FLASH_Prefetch_Enable  FLASH_Prefetch_Disable
 */
void FLASH_PrefetchCmd(uint32_t FLASH_Prefetch)
{
  /* Check the parameters */
  assert_param(IS_FLASH_PREFETCH_STATE(FLASH_Prefetch));
  
  /* Enable or disable the Prefetch Buffer */
  REGBITS_MODIFY(CW_FLASH->CR2,bv3,FLASH_Prefetch);
}

/**
 * @brief CACHE��������
 * 
 * @param FLASH_Cache :FLASH_Cache_Enable   FLASH_Cache_Disable
 */
void FLASH_CacheCmd(uint32_t FLASH_Cache)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CACHE_STATE(FLASH_Cache));
  
  /* Enable or disable the Prefetch Buffer */
  REGBITS_MODIFY(CW_FLASH->CR2,bv4,FLASH_Cache);
}

/**
 * @brief ��ȡPrefetch �������
 * 
 * @return FlagStatus ��SET  RESET
 */
FlagStatus FLASH_GetPrefetchStatus(void)
{ 
    return( CW_FLASH->CR2_f.FETCH ?  SET : RESET); 
}

/**
 * @brief ��ȡBuffer �������
 * 
 * @return FlagStatus ��SET  RESET
 */
FlagStatus FLASH_GetCacheStatus(void)
{ 
     /* Get the  status */
    return( CW_FLASH->CR2_f.CACHE ?  SET : RESET);
}

/**
 * @brief ��ȡ��ǰ�Ķ������ȼ�
 * 
 * @return uint8_t  ��0/1/2/3
 */
uint8_t FLASH_GetReadOutLevel( void )
{
    return( CW_FLASH->CR1_f.SECURITY );
}

/**
 * @brief ����MCU�Ķ������ȼ�,RdLevel����Чȡֵ��ΧΪ0,1,2,3
 * //���ȼ�д��MCU��MCU���Զ���������ɶ������ȼ��޸�
 * //����ӷ�0�ȼ���Ϊ�ȼ�0����MCU�����FLASH�ڵ���������
 * //Level0��ISP�ɶ�д��SWD�ɶ�д
 * //Level1��ISP�ɽ�����SWD�ɽ��������ݲ��ɶ���
 * //Level2��ISP�ɽ�����SWD�޹��ܣ����ݲ��ɶ���
 * //Level3��ISP�޹��ܣ�SWD�޹��ܣ����ݲ��ɶ���
 * @param RdLevel  : FLASH_RDLEVEL0   FLASH_RDLEVEL1
 *                 : FLASH_RDLEVEL2   FLASH_RDLEVEL3  
 */
void FLASH_SetReadOutLevel( uint16_t RdLevel )
{
    assert_param(IS_FLASH_RDLEVEL(RdLevel) );

    if( FLASH_GetReadOutLevel() != RdLevel )
    {
        RdLevel = 0x5A50 | ( RdLevel & 0x03u );
        *((volatile uint32_t *)(0x4001031C)) = RdLevel;
        *((volatile uint32_t *)(0x40010370)) = 0x5A5AABCD;   //MCU�����Ը��¶������ȼ�
        while(1);  //MCU�����Ը��±����ȼ�
    }
}

/**
 * @brief ��������ҳ��
 * 
 */
void FLASH_UnlockAllPages(void)
{
  CW_FLASH->PAGELOCK =  0x5A5Affff;   //��������ҳ��
}

/**
 * @brief ��������ҳ��
 * 
 */
void FLASH_LockAllPages( void )
{
    CW_FLASH->PAGELOCK = 0x5A5A0000;
}

/**
 * @brief ����ָ��ҳ��
 * 
 * @param Page_Number : 0 - 127 
 * @return uint8_t    : ��������0x00
 */
uint8_t FLASH_UnlockPage( uint8_t Page_Number )
{
    uint16_t Currentlockstatus;

    assert_param(IS_FLASH_PAGE_Number(Page_Number));

    Currentlockstatus = CW_FLASH->PAGELOCK;   //��ȡ��ǰ����λ
    CW_FLASH->PAGELOCK = 0x5A5A0000 | Currentlockstatus | ( 1UL<<(Page_Number/8));   //����ָ��ҳ��
    return( 0x00 );
}

/**
 * @brief ����ָ����ַ��Χ������ҳ��,����0x00����ɹ�����0����ʧ��
 * 
 * @param StartAddr : 0x00000000 - 0x0000FFFF
 * @param EndAddr   : 0x00000000 - 0x0000FFFF
 * @return uint8_t  �����󷵻�0x80����ȷ����0x00
 */
uint8_t FLASH_UnlockPages( uint32_t StartAddr , uint32_t EndAddr )
{
    uint16_t Currentlockstatus;
    uint16_t UnlockMask, UnlockIdx;

    UnlockMask = 0x00;
    while( StartAddr <= EndAddr )
    {
        UnlockIdx = StartAddr / 512 / 8;
        UnlockMask |= (1UL<<UnlockIdx);
        StartAddr  += 512;
    }
    if( UnlockMask==0x00 )
    {
        return( FLASH_ERROR_ADDR );     //������ҳ���ַ����
    }
    Currentlockstatus = CW_FLASH->PAGELOCK;   //��ȡ��ǰ����λ
    CW_FLASH->PAGELOCK = 0x5A5A0000 | Currentlockstatus | UnlockMask;   //����ҳ�����ڵ�����
    return( 0x00 );
}

/**
 * @brief ����ָ��ҳ
 * 
 * @param Page_Number : 0 - 127
 * @return uint8_t    �����󷵻�0x80����ȷ����0x00
 */
uint8_t FLASH_ErasePage( uint8_t Page_Number )
{
    uint16_t  CR1BAK,CR2BAK;

    if( ( Page_Number > 127 ) )
    {
        return( FLASH_ERROR_ADDR );
    }

    while( CW_FLASH->CR1 & bv5 );                       //�ȴ���1�β�����ɣ�δ����ʱ����
    CW_FLASH->ICR = 0x00;                                  //clear all int flag
    CR2BAK = CW_FLASH->CR2;
    CR1BAK = CW_FLASH->CR1;
    CW_FLASH->CR2 = 0x5A5A0000 | ( CR2BAK & 0xffe7 );        //�ص�FETCH��BUFFER����
    CW_FLASH->CR1 = 0x5A5A0000 | ( CR1BAK | 0x02u  );        // ����Ϊҳ��ģʽ

    *((volatile uint8_t *)(Page_Number * 512)) = 0x00;       //erase page
    while( CW_FLASH->CR1 & bv5 );                            //�ȴ��������

    CW_FLASH->CR1 = 0x5A5A0000 | CR1BAK;    
    CW_FLASH->CR2 = 0x5A5A0000 | CR2BAK;
    return( CW_FLASH->ISR );
}


/**
 * @brief ������STARTADDR��ENDADDR���ڵ�ҳ��,����0x00����ɹ�����0����ʧ��
 * 
 * @param StartAddr   : 0x00000000 - 0x0000FFFF
 * @param EndAddr     : 0x00000000 - 0x0000FFFF
 * @return uint8_t    �����󷵻�0x80����ȷ����0x00
 */
uint8_t FLASH_ErasePages( uint32_t StartAddr , uint32_t EndAddr )
{
    uint16_t  CR1BAK,CR2BAK;

    if( ( StartAddr > 65535 ) || ( EndAddr > 65535 ) )
    {
        return( FLASH_ERROR_ADDR );
    }

    while( CW_FLASH->CR1 & bv5 );                          //�ȴ���1�β�����ɣ�δ����ʱ����
    CW_FLASH->ICR = 0x00;                                  //clear all int flag
    CR2BAK = CW_FLASH->CR2;
    CR1BAK = CW_FLASH->CR1;
    CW_FLASH->CR2 = 0x5A5A0000 | ( CR2BAK & 0xffe7 );        //�ص�FETCH��BUFFER����
    CW_FLASH->CR1 = 0x5A5A0000 | ( CR1BAK | 0x02u  );        // ����Ϊҳ��ģʽ
    while( StartAddr <= EndAddr )
    {
        *((volatile uint8_t *)(StartAddr)) = 0x00;             //erase page
        while( CW_FLASH->CR1 & bv5 );                          //�ȴ��������
        StartAddr  += 512;
    }

    CW_FLASH->CR1 = 0x5A5A0000 | CR1BAK;    
    CW_FLASH->CR2 = 0x5A5A0000 | CR2BAK;
    return( CW_FLASH->ISR );
}


/**
 * @brief ��WriteAddr��Ϊ��ʼ��ַ������д��pWrBuf�ڵ�WrByteCnt���ֽڵ�����
 * //��д����ʼ��ַ�ͽ�����ַ��Ҫλ��ͬһ��ҳ������
 * //��д���ַ��ҳ���������������������
 * //����0x00����ɹ�����0����ʧ��
 * @param WriteAddr   : 0x00000000 - 0x0000FFFF
 * @param pWrBuf      
 * @param WrByteCnt   ��1 - 512 
 * @return uint8_t    �����󷵻�0x80����ȷ����0x00
 */
uint8_t FLASH_WirteBytes( uint32_t WriteAddr, uint8_t *pWrBuf , uint16_t WrByteCnt )
{
    uint16_t  CR1BAK,CR2BAK;

    if( WriteAddr + WrByteCnt > 65535  )
    {
        return( FLASH_ERROR_ADDR );
    }

    while( CW_FLASH->CR1 & bv5 );                          //�ȴ���1�β�����ɣ�δ����ʱ����
    CW_FLASH->ICR = 0x00;                                    //clear all int flag
    CR2BAK = CW_FLASH->CR2;
    CR1BAK = CW_FLASH->CR1;
    CW_FLASH->CR2 = 0x5A5A0000 | ( CR2BAK & 0xffe7u );       //�ص�FETCH��BUFFER����
    CW_FLASH->CR1 = 0x5A5A0000 | ( CR1BAK | 0x01u  );        // ����Ϊҳдģʽ
    while( WrByteCnt )
    {
        *((volatile uint8_t *)(WriteAddr)) = *pWrBuf;        //write byte
        while( CW_FLASH->CR1 & bv5 );                        //�ȴ��������
        WriteAddr++;
        WrByteCnt--;
        pWrBuf++;
    }
    CW_FLASH->CR1 = 0x5A5A0000 | CR1BAK; 
    CW_FLASH->CR2 = 0x5A5A0000 | CR2BAK;
    return( CW_FLASH->ISR );
}

/**
 * @brief ����ָ��ҳ��,����0x00����ɹ�����0����ʧ��
 * 
 * @param Page_Number : 0 - 127 
 * @return uint8_t    : ��������0x00
 */
uint8_t FLASH_LockPage( uint8_t Page_Number )
{
    uint16_t Currentlockstatus;

    assert_param(IS_FLASH_PAGE_Number(Page_Number));

    Currentlockstatus = CW_FLASH->PAGELOCK;   //��ȡ��ǰ����λ
    CW_FLASH->PAGELOCK = ( (0x5A5A0000 | Currentlockstatus) & ( ~(1UL<<(Page_Number/8))) );   //����ָ��ҳ��
    return( 0x00 );
}

/**
 * @brief ����ָ����ַ��Χ������ҳ��,����0x00����ɹ�����0����ʧ��
 * 
 * @param StartAddr  : 0x00000000 - 0x0000FFFF
 * @param EndAddr    : 0x00000000 - 0x0000FFFF
 * @return uint8_t   : ���󷵻�0x80����������0x00
 */
uint8_t FLASH_LockPages( uint32_t StartAddr , uint32_t EndAddr )
{
    uint16_t UnlockMask, UnlockIdx;
    uint16_t Currentlockstatus;

    UnlockMask = 0x00;
    while( StartAddr <= EndAddr )
    {
        UnlockIdx = StartAddr / 512 / 8;
        UnlockMask |= (1UL<<UnlockIdx);
        StartAddr  += 512;
    }
    if( UnlockMask==0x00 )
    {
        return( FLASH_ERROR_ADDR );     //������ҳ���ַ����
    }
    Currentlockstatus = CW_FLASH->PAGELOCK;   //��ȡ��ǰ����λ
    CW_FLASH->PAGELOCK = ( (0x5A5A0000 | Currentlockstatus) & (~UnlockMask) );   //����ҳ�����ڵ�����
    return( 0x00 );
}


/**
 * @brief FLASH�ж�����
 * 
 * @param FLASH_IT :  FLASH_IT_PROG
 *                    FLASH_IT_PAGELOCK
 *                    FLASH_IT_PC
 * @param NewState  : ENABLE  DISABLE
 */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
    assert_param(IS_FLASH_IT(FLASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
   
    if (NewState != DISABLE)
    {
        CW_FLASH->IER |= FLASH_IT;
    }
    else
    {
        CW_FLASH->IER &= (~FLASH_IT);
    }
}

/**
 * @brief ��ȡFLASHָ���ж�״̬
 * 
 * @param FLASH_IT :  FLASH_IT_PROG
 *                    FLASH_IT_PAGELOCK
 *                    FLASH_IT_PC
 * @return ITStatus : SET  RESET
 */
ITStatus FLASH_GetITStatus(uint32_t FLASH_IT)
{
    assert_param(IS_FLASH_GET_IT(FLASH_IT));

    return (CW_FLASH->ISR & FLASH_IT) ? SET : RESET;
}


/**
 * @brief ���FLASHָ���жϱ�־
 * 
 * @param FLASH_IT  : FLASH_IT_PROG
 *                    FLASH_IT_PAGELOCK
 *                    FLASH_IT_PC
 */
void FLASH_ClearITPendingBit(uint32_t FLASH_IT)
{
    assert_param(IS_FLASH_IT(FLASH_IT));

    CW_FLASH->ICR &= (~FLASH_IT);
}

/**
 * @brief ��ȡFLASHģ���״̬
 * 
 * @return uint8_t 00:����  
 *         FLASH_FLAG_BSY æ
 *         FLASH_FLAG_PCERR  ��дPCָ������ҳ����  
 *         FLASH_FLAG_WRPRTERR ��дδ��������ҳ����
 *         FLASH_FLAG_PGERR   ���Ŀ���ַ���ݲ�ȫΪ0XFF����     
 */
uint32_t FLASH_GetStatus(void)
{
    uint32_t flashstatus;
    if(1 == CW_FLASH->CR1_f.BUSY) 
    {
        return FLASH_FLAG_BSY;
    }

    flashstatus = CW_FLASH->ISR;

    if (flashstatus & FLASH_FLAG_PCERR)
    {
        return FLASH_FLAG_PCERR;
    }
       
    if (flashstatus & FLASH_FLAG_WRPRTERR)
    {
        return FLASH_FLAG_WRPRTERR;
    }
    
    if (flashstatus & FLASH_FLAG_PGERR)
    {
        return FLASH_FLAG_PGERR;
    }
    
    return FLASH_FLAG_OK;
}

