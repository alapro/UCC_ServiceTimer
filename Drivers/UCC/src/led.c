/*
 * led.c
 *
 *  Created on: 15 sept 2026
 *      Author: agust
 */


#include "led.h"




led_TypeDef *contLedArray[MAX_NUMBRE_LEDS];

void ledInit(led_TypeDef* led, GPIO_TypeDef * ledPort, uint16_t ledPin, LED_LedState initialState){

	led->ledPort = ledPort;
	led->ledPin = ledPin;

	HAL_GPIO_WritePin(led->ledPort, led->ledPin, initialState);
	led->ledState = initialState;
}

void ledBlink_ms(led_TypeDef* led, uint16_t ms){

	uint8_t i;

	ledOn(led);
	led->ledCont_ms = ms;
	for(i=0; i<MAX_NUMBRE_LEDS;i++){
		if(contLedArray[i] == 0){
			contLedArray[i] = led;
			break;
		}
	}

}

//void ledBlink_us(led_TypeDef* led, uint32_t us){
//	ledOn(led);
//
//	HAL_TIM_OC_DelayElapsedCallback(htim);
//
//	__HAL_TIM_GET_COUNTER(__HANDLE__);
//	__HAL_TIM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__);
//}

void ledService1msIsr(void){

	uint8_t i;

	for(i=0; i<MAX_NUMBRE_LEDS;i++){
		if(contLedArray[i] != 0){
			if(contLedArray[i]->ledCont_ms){
				contLedArray[i]->ledCont_ms--;
				if(!contLedArray[i]->ledCont_ms){
					ledOff(contLedArray[i]);
					contLedArray[i] = 0;
				}
			}
		}
	}
}

void ledOn(led_TypeDef* led){
	HAL_GPIO_WritePin(led->ledPort, led->ledPin, GPIO_PIN_SET);
	led->ledState = LED_ON;
}
void ledOff(led_TypeDef* led){
	HAL_GPIO_WritePin(led->ledPort, led->ledPin, GPIO_PIN_RESET);
	led->ledState = LED_OFF;
}
