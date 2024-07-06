/**
  ******************************************************************************
  * @file    CW030xx_gpio.c
  * @author  
  * @version 
  * @date    2021-03-16
  * @brief   GPIO HAL module driver.
  *         This file provides firmware functions to manage the following 
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *
***/         
  

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_gpio.h"



//=============================================================================
//GPIO ��ʼ�����������
/**
 * @brief GPIO ��ʼ������ͬʱ���ö�����Ż򵥸�����
 * 
 * @param GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Init �μ�GPIO_InitTypeDef�Ķ���
 */
void GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    if( GPIO_Init->Mode == GPIO_MODE_ANALOG )                        //ģ�⹦��
    {
       REGBITS_SET( GPIOx->ANALOG , GPIO_Init->Pins );
    }
    else
    {
        REGBITS_CLR( GPIOx->ANALOG , GPIO_Init->Pins );               //���ֹ���
        if( (GPIO_Init->Mode & GPIO_MODE_INPUT) == GPIO_MODE_INPUT )  //����ģʽ
        {
           REGBITS_SET( GPIOx->DIR , GPIO_Init->Pins );
           if( GPIO_Init->Mode == GPIO_MODE_INPUT_PULLUP )
           {
               REGBITS_SET( GPIOx->PUR , GPIO_Init->Pins );
               REGBITS_CLR( GPIOx->PDR , GPIO_Init->Pins );
           }
           if( GPIO_Init->Mode == GPIO_MODE_INPUT_PULLDOWN )
           {
               REGBITS_SET( GPIOx->PDR , GPIO_Init->Pins );
               REGBITS_CLR( GPIOx->PUR , GPIO_Init->Pins );
           }
           
           REGBITS_CLR( GPIOx->RISEIE , GPIO_Init->Pins );
           REGBITS_CLR( GPIOx->FALLIE , GPIO_Init->Pins );
           REGBITS_CLR( GPIOx->HIGHIE , GPIO_Init->Pins );
           REGBITS_CLR( GPIOx->LOWIE  , GPIO_Init->Pins );
           if( ( GPIO_Init->IT & GPIO_IT_RISING ) == GPIO_IT_RISING ) 
           {
               REGBITS_SET( GPIOx->RISEIE , GPIO_Init->Pins );
           }
           if( ( GPIO_Init->IT & GPIO_IT_FALLING ) == GPIO_IT_FALLING ) 
           {
               REGBITS_SET( GPIOx->FALLIE , GPIO_Init->Pins );
           }
           if( ( GPIO_Init->IT & GPIO_IT_HIGH ) == GPIO_IT_HIGH ) 
           {
               REGBITS_SET( GPIOx->HIGHIE , GPIO_Init->Pins );
           }
           if( ( GPIO_Init->IT & GPIO_IT_LOW ) == GPIO_IT_LOW ) 
           {
               REGBITS_SET( GPIOx->LOWIE , GPIO_Init->Pins );
           }
        }
        else                                                           //���ģʽ
        {
            REGBITS_CLR( GPIOx->DIR , GPIO_Init->Pins );
            if( GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP )
            {
                REGBITS_CLR( GPIOx->OPENDRAIN , GPIO_Init->Pins );
            }
            else
            {
                REGBITS_SET( GPIOx->OPENDRAIN , GPIO_Init->Pins );
            }
            if( GPIO_Init->Speed == GPIO_SPEED_HIGH )
            {
                REGBITS_SET( GPIOx->SPEED , GPIO_Init->Pins );
            }
            else
            {
                REGBITS_CLR( GPIOx->SPEED , GPIO_Init->Pins );
            }
        }
    }
}

//=============================================================================
//GPIO ����ʼ���� �������
/**
 * @brief GPIO ȥ��ʼ������ͬʱ���ö�����Ż򵥸�����
 * 
 * @param GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * 
 * @param GPIO_Pins ����ȡֵ����
 *        @arg GPIO_PIN_0/1/2.../15/ALL ��ͨ��������ͬʱ�����������
 */
void GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pins)
{ 
    REGBITS_SET( GPIOx->ANALOG , GPIO_Pins );
    REGBITS_SET( GPIOx->DIR    , GPIO_Pins );
    REGBITS_CLR( GPIOx->PUR    , GPIO_Pins );
    REGBITS_CLR( GPIOx->PDR    , GPIO_Pins );
    REGBITS_CLR( GPIOx->RISEIE , GPIO_Pins );
    REGBITS_CLR( GPIOx->FALLIE , GPIO_Pins );
    REGBITS_CLR( GPIOx->HIGHIE , GPIO_Pins );
    REGBITS_CLR( GPIOx->LOWIE  , GPIO_Pins );
    REGBITS_CLR( GPIOx->OPENDRAIN , GPIO_Pins );
}
//=============================================================================
//��ȡָ�����ŵ�ƽ��һ������
//ע�⣺������ú꺯������ȡ���ŵ�ƽ����PA00_GETVALUE()
/**
 * @brief ��ȡһ�����ŵĵ�ƽ
 * 
 * @param GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pin ����ȡֵ����
 *        @arg GPIO_PIN_0/1/2.../15
 * @return GPIO_PinState ȡֵ����:
 *        @arg GPIO_Pin_SET
 *        @arg GPIO_Pin_RESET
 */
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if( GPIOx->IDR & GPIO_Pin )
    {
        return( GPIO_Pin_SET );
    }
    
    return( GPIO_Pin_RESET );
}

//=============================================================================
//����ָ�����ŵ�ƽ���������
//ע�⣺��ֻ����һֻ���ţ�������ú꺯������PA00_SETHIGH(), PA00_SETLOW()
/**
 * @brief ����ָ�����ŵ�ƽ����ͬʱ���ö������
 * 
 * @param GPIOx GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins ����ȡֵ����
 *        @arg GPIO_PIN_0/1/2.../15/ALL;
 * @param PinState ȡֵ����:
 *        @arg GPIO_Pin_SET
 *        @arg GPIO_Pin_RESET
 */
void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pins, GPIO_PinState PinState)
{
    if( PinState == GPIO_Pin_SET )
    {
        GPIOx->BSRR = GPIO_Pins;
    }
    else
    {
        GPIOx->BRR = GPIO_Pins;
    }
}

//=============================================================================
//���ö˿ڵ��ֽڣ�B0-B7�����ŵ�ƽ
/**
 * @brief ���ö˿ڵ��ֽڣ�B0-B7�����ŵ�ƽ
 * 
 * @param GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOF
 * @param Value ȡֵ��Χ��0x00~0xFF
 */
void GPIO_LowByte_Write(GPIO_TypeDef* GPIOx, uint8_t Value )
{
    GPIOx->ODRLOWBYTE = Value;
}

//=============================================================================
//���ö˿ڸ��ֽڣ�B8-B15�����ŵ�ƽ
/**
 * @brief ���ö˿ڸ��ֽڣ�B8-B15�����ŵ�ƽ
 * 
 * @param GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param Value ȡֵ��Χ��0x00~0xFF
 */
void GPIO_HighByte_Write(GPIO_TypeDef* GPIOx, uint8_t Value )
{
    GPIOx->ODRHIGHBYTE = Value;
}

//=============================================================================
//��תָ�����ŵ�ƽ���������
//ע�⣺��ֻ����һֻ���ţ�������ú꺯������PA00_TOG()
/**
 * @brief ��תָ�����ŵ�ƽ����ͬʱ���ö������
 * 
 * @param GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins 
 */
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pins)
{
    GPIOx->TOG = GPIO_Pins;
}

//=============================================================================
//����ָ������������������
/**
 * @brief ����ָ�������������ͬʱ���ö������
 * 
 * @param GPIOx  ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins 
 */
void GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pins)
{
    REGBITS_SET( GPIOx->LOCK , GPIO_Pins );
}

//=============================================================================
//��PA13/PA14���ó�GPIO
/**
 * @brief ��PA13/PA14���ó�GPIO
 * 
 */
void GPIO_SWD2GPIO( void )
{
    CW_SYSCTRL->CR2 =  CW_SYSCTRL->CR2 | ( 0x5A5A0000 | bv1 );
}

//=============================================================================
//��PA13/PA14���ó�SWD
/**
 * @brief ��PA13/PA14���ó�SWD��PA13/SWDIO PA14/SWCLK
 * 
 */
void GPIO_GPIO2SWD( void )
{
    CW_SYSCTRL->CR2 =  0x5A5A0000 | ( CW_SYSCTRL->CR2 & (~(bv1)) );
}

//=============================================================================
//���ö˿��˲�
// FltClk ֻ���Ǻ궨���ж���Ĳ���
/**
 * @brief ���ö˿��˲�
 * 
 * @param GPIOx ����Ϊ���в���֮һ��
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins 
 * @param FltClk ֻ���Ǻ궨���ж���Ĳ��� GPIO_FLTCLK_xxx
 */
void GPIO_ConfigFilter( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pins, uint32_t FltClk )
{
    GPIOx->FILTER = FltClk | GPIO_Pins;
}

//=============================================================================
//���ö˿ڸ�������
//��ʹ��CW32f030_gpio.h�еĺ궨��������ÿ���˿ڵĸ�������

