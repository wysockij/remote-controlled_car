/**
 * @file hc-sr04_read.c
 * @brief Contains all functions for reading distances from the HC-SR04 module.
 * @version 0.1
 * @date 2024-05-09
 *
 * @details
 * The file contains functions necessary for initialization and reading distances from the HC-SR04 module
 * using STM32 microcontroller and TIM2 timer.
 *
 * @authors
 * https://forbot.pl/blog/kurs-stm32l4-czujnik-odleglosci-wyswietlacz-7-seg-id48628
 *
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim2;

/**
 * @brief Initializes the three TIM2 channels used to correctly read distances from the HC-SR04 module.
 *
 * The function activates three TIM2 channels: two for capturing the Echo signal (start and stop) and one
 * to generate a trigger pulse for the HC-SR04 module.
 */
void hcsr04_read_init(void)
{
	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_3);  // echo start
	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_4);  // echo end
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // trigger hc-sr04, 10us pulse
}

/**
 * @brief Calculates distance based on the width of the Echo signal.
 *
 * The function calculates the distance based on the time difference between the moment the Echo signal appears
 * and its disappearance. The result is converted to centimeters.
 *
 * @return float Calculated distance in centimeters.
 */
float obstacle_detection(void)
{

	uint32_t start = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_3); // rising edge of echo
	uint32_t stop = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_4);  // falling edge of echo
	return (stop - start) / 58.0f;
}
