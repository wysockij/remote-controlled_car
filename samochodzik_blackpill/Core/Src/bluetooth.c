/**
 * @file bluetooth.c
 * @author Jacek Bielski && Jakub Wysocki
 * @brief This file contains all functions used to connect to the Bluetooth.
 * @version 0.1
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "main.h"
#define LINE_MAX_LENGTH 64
static char line_buffer[LINE_MAX_LENGTH + 1]; /**< Buffer for storing the received line of data. */
static uint32_t line_length;				  /**< Current length of the data in the line buffer. */

extern UART_HandleTypeDef huart2;
extern uint8_t received; /**< Variable to store the received data byte. */

/**
 * @brief This function is called as interrupt when receiving data.
 *
 * It checks if the received data is from USART2 and processes the received byte.
 *
 * @param huart
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if (huart->Instance == USART2)
	{
		line_append(received);
		HAL_UART_Receive_IT(&huart2, &received, 1);
	}
}

/**
 * @brief Function to process the received line of data.
 *
 * This function processes the command received from the Bluetooth module.
 * Depending on the command, it adjusts the car's:
 * - turn angle (left, right, idle),
 * - toggles lights (on, off),
 * - ride mode (foreward, backward, idle).
 */
void read_logic(void)
{
	if (line_buffer[0] == 'y')
	{
		car.turn_angle = atof(line_buffer + 2);
		if (car.turn_angle <= -3)
		{
			car.turn = 'l';
		}
		else if (car.turn_angle >= 3)
		{
			car.turn = 'r';
		}
		else
		{
			car.turn = 'i';
		}
	}
	else if (line_buffer[0] == 'd')
	{
		//  turning on/off the light
		HAL_GPIO_TogglePin(blue_led_GPIO_Port, blue_led_Pin);
	}
	else
	{
		car.ride = (uint8_t)line_buffer[0];
	}
}

/**
 * @brief Function to append a received byte to the line buffer.
 *
 * This function adds a received byte to the line buffer. If the byte is a
 * newline or carriage return, it processes the complete line.
 *
 * @param value
 */
void line_append(uint8_t value)
{
	if (value == '\r' || value == '\n')
	{

		if (line_length > 0)
		{
			line_buffer[line_length] = '\0';
			read_logic();
			line_length = 0;
		}
	}
	else
	{
		if (line_length >= LINE_MAX_LENGTH)
		{
			line_length = 0;
		}
		line_buffer[line_length++] = value;
	}
}

uint8_t message[64];	   /**< Buffer for storing the message to be sent over Bluetooth. */
uint16_t message_size = 0; /**< Size of the message stored in the buffer. */

/**
 * @brief Function to send a Bluetooth message.
 *
 * This function formats and sends a message containing the car's obstacle
 * distance over Bluetooth using the UART transmit interrupt.
 */
void bluetooth_send(void)
{
	message_size = sprintf(message, "log %.1f cm\n", car.obstacle_distance);
	HAL_UART_Transmit_IT(&huart2, message, message_size);
}
