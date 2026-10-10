/*
 * led.h
 *
 *  Created on: 15 sept 2026
 *      Author: agust
 */

#ifndef UCC_INC_LED_H_
#define UCC_INC_LED_H_

#include "stm32f4xx_hal.h"

#define MAX_NUMBRE_LEDS	64

typedef enum
{
  LED_OFF = 0,
  LED_ON
}LED_LedState;

typedef struct{
	GPIO_TypeDef* 	ledPort;
	uint16_t 		ledPin;
	LED_LedState	ledState;
	uint16_t 		ledCont_ms;
}led_TypeDef;



void ledService1msIsr(void);

void ledInit(led_TypeDef* led, GPIO_TypeDef * ledPort, uint16_t ledPin, LED_LedState initialState);
void ledBlink_ms(led_TypeDef* led, uint16_t ms);
void ledBlink_us(led_TypeDef* led, uint32_t us);
void ledOn(led_TypeDef* led);
void ledOff(led_TypeDef* led);

#endif /* UCC_INC_LED_H_ */
