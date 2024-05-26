/**
 * @file bluetooth.h
 * @author Jakub Wysocki
 * @brief Header file for Bluetooth communication and control functions.
 * @version 0.1
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

/**
 * @brief Callback function for UART receive complete interrupt.
 *
 * @param huart
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/**
 * @brief Function to process the received line of data.
 */
void read_logic(void);

/**
 * @brief Function to append a received byte to the line buffer.
 *
 * @param value
 */
void line_append(uint8_t value);

/**
 * @brief Function to send a Bluetooth message.
 */
void bluetooth_send(void);

#endif /* INC_BLUETOOTH_H_ */
