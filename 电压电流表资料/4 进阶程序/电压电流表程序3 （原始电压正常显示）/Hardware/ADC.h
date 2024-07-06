#ifndef _ADC_H_
#define _ADC_H_

#define ADC_SAMPLE_SIZE (20)
#define ADC_REF_VALUE (1500)
#define R2            (220) //��λ��K��
#define R1            (10)

#include "stdint.h"
#include "cw32f003_gpio.h"
#include "cw32f003_adc.h"
#include "cw32f003_rcc.h"

void ADC_init(void);
void Get_ADC_Value(void);
	
#endif
