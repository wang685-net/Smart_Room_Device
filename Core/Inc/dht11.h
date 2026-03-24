#ifndef _DHT11_H_
#define _DHT11_H_

#include <stdint.h>

// 在不同 STM32 的板子上
#define DHT11_GPIO_PORT   GPIOC
#define DHT11_PIN         GPIO_PIN_10


void DHT11_Init(void);


uint8_t DHT11_Get(float* temp, uint8_t* humi);

#endif

