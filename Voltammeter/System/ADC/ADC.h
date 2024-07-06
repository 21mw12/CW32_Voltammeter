#ifndef __ADC_H__
#define __ADC_H__

///////////////////////////////////////////////////////////
//
// 文件功能：ADC读取
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/12
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/* ADC引脚 */
#define ADC_Port			CW_GPIOB
#define ADC_Pin_9			GPIO_PIN_1
#define ADC_Pin_11		GPIO_PIN_5

/* ADC采集到的数据，分别来源于通道0和通道1 */
extern uint16_t ADCValue[2];

/**
  * @brief ADC通道初始化
  * @return 无
  */
void ADC_ChannelInit(void);

/**
  * @brief 获取ADC序列对应数据
  * @return ADC原始数据
  */
void ADC_GetValue(void);

#endif
