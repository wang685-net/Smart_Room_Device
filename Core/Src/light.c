#include "adc.h"
#include "light.h"


uint32_t Light_Get(void)
{
	uint32_t val;
	
	HAL_ADC_Start(&hadc1);
	
	HAL_ADC_PollForConversion(&hadc1, 5);
	
	val = HAL_ADC_GetValue(&hadc1);
	
	HAL_ADC_Stop(&hadc1);
	
	return (4095 - val);
}



