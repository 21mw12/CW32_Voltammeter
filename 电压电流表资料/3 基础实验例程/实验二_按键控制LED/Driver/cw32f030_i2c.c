/**
 * @file cw32f030_i2c.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-27
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
#include "cw32f030_i2c.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

//I2C���豸��ַ������8 BIT���ã����λ0����1���ɡ�
#define I2C_SLAVEADDRESS 0xA0

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief I2C �����ʷ�����ʹ��
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_BaudGeneratorEnable(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2Cx->BRREN_f.EN = 1;
  }
  else
  {
    /* Peripheral not under reset */
    I2Cx->BRREN_f.EN = 0;
  }
}

/**
 * @brief  I2C�����ò����ʼ��������üĴ�������
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param u8TBaud   : ����ֵ= fPCLK/(8*fSCL) - 1
 *                  : ����ֵ��Ҫ����fPCLK��fSCL����          
 */
void I2C_SetBaud(I2C_TypeDef *I2Cx, uint8_t u8TBaud)
 {
     assert_param(IS_I2C_ALL_PERIPH(I2Cx));
     assert_param(IS_I2C_Baud_BRR(u8TBaud));
     I2Cx->BRR = u8TBaud;
 }

/**
 * @brief ����START�ź�
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    //I2Cx->CR_f.STA = 1;
		
		if( I2Cx->STAT != 0xF8 )
    {
        I2Cx->CR_f.STA = 1;  //set start 
        I2Cx->CR_f.SI = 0;    //clear si
    }
    else
    {
        I2Cx->CR_f.STA = 1;  //set start 
    }
		
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CR_f.STA = 0;
  }
}

/**
 * @brief ����STOP�ź�
 * 
 * @param I2Cx       : I2C1  I2C2
 * @param NewState   : ENABLE  DISABLE
 */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CR_f.STO = 1;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CR_f.STO = 0;
  }
}

/**
 * @brief ACKӦ������
 * 
 * @param I2Cx      : I2C1  I2C2 
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2Cx->CR_f.AA = 1;
  }
  else
  {
    /* Disable the acknowledgement */
    I2Cx->CR_f.AA = 0;
  }
}

/**
 * @brief �˲�������
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 * ��Ϊ����ʱ�����BRR��ֵС�ڻ����9����I2Cx_CR.FLT����ΪENABLE��
 * ���BRR��ֵ����9���� I2Cx_CR.FLTΪDISABLE��
 * 
 * ���ӻ�ʱ�����PCLK��SCL��Ƶ�ʱ�ֵС�ڻ����40����I2Cx_CR.FLT����ΪENABLE��
 * ���PCLK��SCL��Ƶ�ʱ�ֵ����40����I2Cx_CR.FLT����ΪDISABLE��
 */
void I2C_FilterConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2Cx->CR_f.FLT = 1;
  }
  else
  {
    /* Peripheral not under reset */
    I2Cx->CR_f.FLT = 0;
  }
}

/**
 * @brief ���ӻ�ʱ��I2C��ַ0����
 * 
 * @param I2Cx          : I2C1  I2C2
 * @param I2CSlaveAddr  ������ȫ0�������÷�ΧΪ0x01 - 0x7F
 */
void I2C_SetOwnSlaveAddress0(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddr)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  I2Cx->ADDR0_f.ADDR0 = ( I2CSlaveAddr >> 1);
	
	
}

/**
 * @brief ���ӻ�ʱ��I2C��ַ1����
 * 
 * @param I2Cx            : I2C1  I2C2
 * @param I2CSlaveAddr    ������ȫ0�������÷�ΧΪ0x01 - 0x7F
 */
void I2C_SetOwnSlaveAddress1(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddr)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
	I2Cx->ADDR1_f.ADDR1 = ( I2CSlaveAddr >> 1);
}

/**
 * @brief ���ӻ�ʱ��I2C��ַ2����
 * 
 * @param I2Cx           : I2C1  I2C2
 * @param I2CSlaveAddr   ������ȫ0�������÷�ΧΪ0x01 - 0x7F
 */
void I2C_SetOwnSlaveAddress2(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddr)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
	I2Cx->ADDR2_f.ADDR2 = ( I2CSlaveAddr >> 1);
}

/**
 * @brief  �㲥��ַ��Ӧλ����
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_GcConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* ������Ӧ�㲥 */
    I2Cx->ADDR0_f.GC = 1;
  }
  else
  {
    /* ��ֹ��Ӧ�㲥 */
    I2Cx->ADDR0_f.GC = 0;
  }
}

/**
 * @brief I2Cģ��ʹ�ܿ���
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CR_f.EN = 1;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CR_f.EN = 0;
  }
}

/**
 * @brief I2C����ȡ�жϱ�־λ����
 * 
 * @param I2Cx        : I2C1  I2C2
 * @return ITStatus  : Ϊ0��ʾ���жϱ�־(SI = 0)��Ϊ1��Ϊ���жϱ�־(SI = 1)
 */
ITStatus I2C_GetIrq(I2C_TypeDef *I2Cx)
{
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    return (I2Cx->CR & bv3) ? SET : RESET;
}

/**
 * @brief I2C������жϱ�־λ����
 * 
 * @param I2Cx   : I2C1  I2C2
 */
void I2C_ClearIrq(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  I2Cx->CR_f.SI = 0; 
}

/**
 * @brief I2C����ȡ״̬�Ĵ�������
 * 
 * @param I2Cx      : I2C1  I2C2
 * @return uint8_t  : 26�ַ���ֵ�������ڲ�ͬģʽ�²�ͬ
 * 
 */
uint8_t I2C_GetState(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  return ((uint8_t)(I2Cx->STAT));
}

/**
 * @brief I2C:MASTER��ʼ������
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param I2C_InitStruct 
 */
void I2C_Master_Init(I2C_TypeDef* I2Cx,I2C_InitTypeDef *I2C_InitStruct)
{
   I2C_SetBaud(I2Cx,I2C_InitStruct->I2C_Baud);
	 I2C_BaudGeneratorEnable(I2Cx,I2C_InitStruct->I2C_BaudEn);
   I2C_FilterConfig(I2Cx,I2C_InitStruct->I2C_FLT);
   I2C_AcknowledgeConfig(I2Cx,I2C_InitStruct->I2C_AA);

   if(I2C_InitStruct->I2C_Baud<=9)    
   {
       I2C_FilterConfig(I2Cx,ENABLE);
   }
	
}

/**
 * @brief I2C:SLAVE��ʼ������
 * 
 * @param I2Cx      : I2C1  I2C2
 * @param I2C_InitStruct 
 */
void I2C_Slave_Init(I2C_TypeDef* I2Cx,I2C_InitTypeDef *I2C_InitStruct)
{
   I2C_FilterConfig(I2Cx,ENABLE);
   I2C_AcknowledgeConfig(I2Cx,I2C_InitStruct->I2C_AA);
	
	 I2C_SetOwnSlaveAddress0(I2Cx,I2C_InitStruct->I2C_OwnSlaveAddr0);
   I2C_GcConfig(I2Cx,I2C_InitStruct->I2C_OwnGc);
	 I2C_SetOwnSlaveAddress1(I2Cx,I2C_InitStruct->I2C_OwnSlaveAddr1);
	 I2C_SetOwnSlaveAddress2(I2Cx,I2C_InitStruct->I2C_OwnSlaveAddr2);
	
}

/**
 * @brief I2C1 �رճ�ʼ��
 * 
 */
void I2C1_DeInit(void)
 {
    CW_SYSCTRL->APBRST1_f.I2C1 = 0;
    CW_SYSCTRL->APBRST1_f.I2C1 = 1;
    CW_I2C1->CR = 0x00;
 }
 
/**
 * @brief I2C2 �رճ�ʼ��
 * 
 */
 void I2C2_DeInit(void)
 {
    CW_SYSCTRL->APBRST1_f.I2C2 = 0;
    CW_SYSCTRL->APBRST1_f.I2C2 = 1;
    CW_I2C2->CR = 0x00;
 }

/**
 * @brief ����1�ֽ�����
 * 
 * @param I2Cx    : I2C1  I2C2
 * @param Data    : 0x00 - 0xFF
 */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Write in the DR register the data to be sent */
  I2Cx->DR = Data;
}

/**
 * @brief ����1�ֽ�����
 * 
 * @param I2Cx      : I2C1  I2C2
 * @return uint8_t  : 0x00 - 0xFF
 */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the data in the DR register */
  return (uint8_t)I2Cx->DR;
}

/**
 * @brief ����ʱ���ʹӻ���ַ�ֽ�
 * 
 * @param I2Cx           : I2C1  I2C2
 * @param Address        : ����8BIT���ã����bitΪ0����1������
 * @param I2C_Direction  : I2C_Direction_Transmitter  I2C_Direction_Receiver
 */
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));
  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction != I2C_Direction_Transmitter)
  {
    /* Set the address bit0 for read */
    Address |= 0x01;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= 0xfe;
  }
  /* Send the address */
  I2Cx->DR = Address;
}

/**
 * @brief ��λI2C1
 * 
 * @param NewState   : ENABLE  DISABLE
 */
void I2C1_SoftwareResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    CW_SYSCTRL->APBRST1_f.I2C1 = 1;
  }
  else
  {
    /* Peripheral not under reset */
    CW_SYSCTRL->APBRST1_f.I2C1 = 0;
  }
}

/**
 * @brief ��λI2C2
 * 
 * @param NewState   : ENABLE  DISABLE
 */
void I2C2_SoftwareResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    CW_SYSCTRL->APBRST1_f.I2C2 = 1;
  }
  else
  {
    /* Peripheral not under reset */
    CW_SYSCTRL->APBRST1_f.I2C2 = 0;
  }
}

/**
 ******************************************************************************
 * @brief  �������պ��������ö�ȡEEPROM��ʽ���������ȡ��ʽ����Ҫ��д��EEPROM�ĵ�ַ
 *
 * @param I2Cx           : I2C1  I2C2
 * @param u8Addr         : ��ȡEEPROM�ڴ�����ַ
 * @param pu8Data        : ��ȡ����EEPROM�����ݵ�ַ
 * @param u32Len         : ��ȡ����EEPROM�����ݳ���
 *
 ******************************************************************************/
 void I2C_MasterReadEepomData(I2C_TypeDef *I2Cx,uint8_t u8Addr,uint8_t *pu8Data,uint32_t u32Len)
{
    uint8_t u8i=0,u8State;
    
	I2C_GenerateSTART(I2Cx, ENABLE);
    
	while(1)
	{
		while(0 == I2C_GetIrq(I2Cx))
        {}
		u8State = I2C_GetState(I2Cx);
		switch(u8State)
		{
			case 0x08:   //������START�ź�
				I2C_GenerateSTART(I2Cx, DISABLE);
				I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS,0X00);   //���ʹӻ���ַ
				break;
			case 0x18:    //������SLA+W/R�ֽ�
				I2C_SendData(I2Cx,u8Addr);
				break;
			case 0x28:   //������1�ֽ����ݣ�����EEPROM��memory��ַҲ����������ͺ��������Ҳ�����
				I2C_GenerateSTART(I2Cx, ENABLE);
				break;
			case 0x10:   //�������ظ���ʼ�ź�
				I2C_GenerateSTART(I2Cx, DISABLE);
				I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS, 0X01);
				break;
			case 0x40:   //������SLA+R�źţ���ʼ��������
				if(u32Len>1)
				{
					I2C_AcknowledgeConfig(I2Cx,ENABLE);
				}
				break;
			case 0x50:   //������һ�ֽ����ݣ��ڽ������1�ֽ�����֮ǰ����AA=0;
				pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
				if(u8i==u32Len-1)
				{
					I2C_AcknowledgeConfig(I2Cx,DISABLE);
				}
				break;
			case 0x58:   //���յ�һ�������ֽڣ���NACK�ѻظ�
				pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
				I2C_GenerateSTOP(I2Cx, ENABLE);
				break;	
			case 0x38:   //�����ڷ��� SLA+W �׶λ��߷������ݽ׶ζ�ʧ�ٲ�  ����  �����ڷ��� SLA+R �׶λ��߻�Ӧ NACK �׶ζ�ʧ�ٲ�
				I2C_GenerateSTART(I2Cx, ENABLE);
				break;
			case 0x48:   //������SLA+R��ӻ�����NACK
				I2C_GenerateSTOP(I2Cx, ENABLE);
				I2C_GenerateSTART(I2Cx, ENABLE);
				break;
			default:
				I2C_GenerateSTART(I2Cx, ENABLE);//��������״̬�����·�����ʼ����
				break;
		}
		I2C_ClearIrq(I2Cx);
		if(u8i==u32Len)
		{
			break;
		}
	}
}

/**
 ******************************************************************************
 * @brief  �������ͺ��������ö�ȡEEPROM��ʽ���������ȡ��ʽ����Ҫ��д��EEPROM�ĵ�ַ
 *
 * @param I2Cx           : I2C1  I2C2
 * @param u8Addr         : д��EEPROM�ڴ�����ַ
 * @param pu8Data        : д�����ݴ�ŵ�ַ
 * @param u32Len         : д�����ݳ���
 *
 ******************************************************************************/
 
void I2C_MasterWriteEepromData(I2C_TypeDef *I2Cx,uint8_t u8Addr,uint8_t *pu8Data,uint32_t u32Len)
{
    uint8_t u8i=0,u8State;
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(1)
	{
		while(0 == I2C_GetIrq(I2Cx))
		{;}
		u8State = I2C_GetState(I2Cx);
		switch(u8State)
		{
			case 0x08:   //������START�ź�
				I2C_GenerateSTART(I2Cx, DISABLE);
				I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS,0X00);  //���豸��ַ����
				break;
			case 0x18:   //������SLA+W�ź�,ACK���յ�
				I2C_SendData(I2Cx,u8Addr);//���豸�ڴ��ַ����
				break;
			case 0x28:   //������1�ֽ����ݣ�����EEPROM��memory��ַҲ����������ͺ��������Ҳ�����	
				I2C_SendData(I2Cx,pu8Data[u8i++]);
				break;
			case 0x20:   //������SLA+W��ӻ�����NACK
			case 0x38:    //�����ڷ��� SLA+W �׶λ��߷������ݽ׶ζ�ʧ�ٲ�  ����  �����ڷ��� SLA+R �׶λ��߻�Ӧ NACK �׶ζ�ʧ�ٲ�
				I2C_GenerateSTART(I2Cx, ENABLE);
				break;
			case 0x30:   //������һ�������ֽں�ӻ�����NACK
				I2C_GenerateSTOP(I2Cx, ENABLE);
				break;
			default:
				break;
		}			
		if(u8i>u32Len)
		{
			I2C_GenerateSTOP(I2Cx, ENABLE);//��˳���ܵ�������ֹͣ����
			I2C_ClearIrq(I2Cx);
			break;
		}
		I2C_ClearIrq(I2Cx);			
	}
}

/**
 ******************************************************************************
 * @brief  �������պ���������MCU֮���������ͨ��
 *
 * @param I2Cx           : I2C1  I2C2
 * @param pu8Data        : �������ݴ�ŵ�ַ
 * @param u32Len         : �������ݳ���
 *
 ******************************************************************************/
 void I2C_MasterRecDataFromSlave(I2C_TypeDef *I2Cx,uint8_t *pu8Data,uint32_t u32Len)
{
    uint8_t u8i=0,u8State;
    
	I2C_GenerateSTART(I2Cx, ENABLE);
    
	while(1)
	{
		while(0 == I2C_GetIrq(I2Cx))
        {}
		u8State = I2C_GetState(I2Cx);
		switch(u8State)
		{
			case 0x08:   //������START�ź�
			case 0x10:   //�������ظ���ʼ�ź�
				I2C_GenerateSTART(I2Cx, DISABLE);
				I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS,0X01);   //���ʹӻ���ַ+R�ֽ�
				break;
			case 0x40:   //������SLA+R�źţ���ʼ��������
				if(u32Len>1)
				{
					I2C_AcknowledgeConfig(I2Cx,ENABLE);
				}
				break;
			case 0x50:   //������һ�ֽ����ݣ��ڽ������1�ֽ�����֮ǰ����AA=0;
				pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
				if(u8i==u32Len-1)
				{
					I2C_AcknowledgeConfig(I2Cx,DISABLE);
				}
				break;
			case 0x58:   //���յ�һ�������ֽڣ���NACK�ѻظ�
				pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
				I2C_GenerateSTOP(I2Cx, ENABLE);
				break;	
			case 0x38:   //�����ڷ��� SLA+W �׶λ��߷������ݽ׶ζ�ʧ�ٲ�  ����  �����ڷ��� SLA+R �׶λ��߻�Ӧ NACK �׶ζ�ʧ�ٲ�
				I2C_GenerateSTART(I2Cx, ENABLE);
				break;
			case 0x48:   //������SLA+R��ӻ�����NACK
				I2C_GenerateSTOP(I2Cx, ENABLE);
				I2C_GenerateSTART(I2Cx, ENABLE);
				break;
			default:
				I2C_GenerateSTART(I2Cx, ENABLE);//��������״̬�����·�����ʼ����
				break;
		}
		I2C_ClearIrq(I2Cx);
		if(u8i==u32Len)
		{
			break;
		}
	}
}

/**
 ******************************************************************************
 * @brief  �������ͺ���������MCU֮���������ͨ��
 *
 * @param I2Cx           : I2C1  I2C2
 * @param pu8Data        : �������ݴ�ŵ�ַ
 * @param u32Len         : �������ݳ���
 *
 ******************************************************************************/
void I2C_MasterSendDataToSlave(I2C_TypeDef *I2Cx,uint8_t *pu8Data,uint32_t u32Len)
{
  uint8_t u8i = 0;
	uint8_t u8State;
	
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(1)
	{
		while(0 == I2C_GetIrq(I2Cx))
		{;}
		u8State = I2C_GetState(I2Cx);
		switch(u8State)
		{
			case 0x08:   //������START�ź�
				I2C_GenerateSTART(I2Cx, DISABLE);
				I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS,0X00);  //���豸��ַ+W����
				break;
			case 0x18:   //������SLA+W�ź�
			case 0x28:   //������1�ֽ����ݣ�����EEPROM��memory��ַҲ����������ͺ��������Ҳ�����	
				I2C_SendData(I2Cx,pu8Data[u8i++]);
				break;
			case 0x20:   //������SLA+W��ӻ�����NACK
			case 0x38:   //�����ڷ��� SLA+W �׶λ��߷������ݽ׶ζ�ʧ�ٲ�  ����  �����ڷ��� SLA+R �׶λ��߻�Ӧ NACK �׶ζ�ʧ�ٲ�
				I2C_GenerateSTART(I2Cx, ENABLE);
				break;
			case 0x30:   //������һ�������ֽں�ӻ�����NACK
				I2C_GenerateSTOP(I2Cx, ENABLE);
				break;
			default:
				break;
		}			
		if(u8i>u32Len)
		{
			I2C_GenerateSTOP(I2Cx, ENABLE);//��˳���ܵ�������ֹͣ����
			I2C_ClearIrq(I2Cx);
			break;
		}
		I2C_ClearIrq(I2Cx);			
	}
}


/**
 * @brief �ӻ����ͺ���������MCU֮���������ͨ��
 * 
 * @param I2Cx           : I2C1  I2C2 
 * @param pu8Data        : �������ݴ�ŵ�ַ
 * @param u32Len         : �������ݳ��� 
 */
void I2C_SlaveSendDataToMaster(I2C_TypeDef* I2Cx,uint8_t *pu8Data,uint32_t *u32Len)
{
    uint8_t u8i=0,u8State;
    while(1)
    {
        while(0 == I2C_GetIrq(I2Cx))
        {}
        u8State = I2C_GetState(I2Cx);
        switch(u8State)
        {
            case 0xA8:   //���յ�SLA+R,ACK�ѻ�Ӧ
            case 0xB0:   //������ʧ�ٲú�ת�ӻ�����SLA+RѰַ��ACK�ѻ�Ӧ
                I2C_SendData(I2Cx,pu8Data[u8i++]);
                break;
            case 0xB8:   //�ӻ��ѷ���1�ֽ����ݣ�ACK���յ�
								I2C_SendData(I2Cx,pu8Data[u8i++]);            
                break; 
            case 0xC8:    //�ӻ����һ�������ֽ��ѱ�����(����ǰ����AA������Ϊ0)�����ѽ��յ�ACK            
//                I2C_SendData(I2Cx,pu8Data[u8i++]);   //����Ҫ��
//                break;          
						case 0xC0:    //�ѷ��������ֽڣ��ѽ��� NACK
								break;
						default:               
                break; 
        }
				
				I2C_ClearIrq(I2Cx);
				
				if((0xC0 == u8State) || (0xC8 == u8State))
				{
					 break; 
				}
				
    } 
 }

/**
 * @brief �ӻ����պ���������MCU֮���������ͨ��
 * 
 * @param I2Cx           : I2C1  I2C2 
 * @param pu8Data        : �������ݴ�ŵ�ַ
 * @param u32Len         : �������ݳ��� 
 */
void I2C_SlaveRecDataFromMaster(I2C_TypeDef* I2Cx,uint8_t *pu8Data,uint32_t *pu32Len)
{
    uint8_t u8i=0,u8State;
    while(1)
   {
        while(0 == I2C_GetIrq(I2Cx))
        {}
        u8State = I2C_GetState(I2Cx);
        switch(u8State)
        {
            case 0x60:   //���յ�SLA+W��ACK�ѻ�Ӧ
            case 0x68:   //������ʧ�ٲú�SLA+WѰַ��ACK�ѻ�Ӧ
            case 0x70:   //���յ�SLA���㲥��ַ��+W��ACK�ѻ�Ӧ
            case 0x78:   //������ʧ�ٲú�SLA���㲥��ַ��+WѰַ��ACK�ѻ�Ӧ
              break;
            case 0x80:   //�ӻ��ѽ��յ�1�ֽ����ݣ�ACK�ѻظ�
            case 0x90:   //�ӻ��ѽ��յ�1�ֽڹ㲥���ݣ�ACK�ѻظ�	
						case 0x88:   //�ӻ��ѽ��յ�1�ֽ����ݣ�NACK�ѻ�Ӧ  
						case 0x98:   //�ӻ��ѽ��յ�1�ֽ����ݣ�NACK�ѻ�Ӧ   
                pu8Data[u8i++] = I2C_ReceiveData(I2Cx);               
                break;
            case 0xA0:  //�ظ�START�źŻ���STOP�ź����յ�   
                *pu32Len = u8i;
                break;	
            default:
                break;	
        }
				I2C_ClearIrq(I2Cx);
				if(0xA0 == u8State)
        {
          break;
        }
   }
}

