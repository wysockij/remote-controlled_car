/**
 * @file hc-sr04_read.h
 * @author https://forbot.pl/blog/kurs-stm32l4-czujnik-odleglosci-wyswietlacz-7-seg-id48628
 * @brief Header file containing function prototypes for HC-SR04 ultrasonic sensor reading.
 * @version 0.1
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef INC_HC_SR04_READ_H_
#define INC_HC_SR04_READ_H_

/**
 * @brief Initialize HC-SR04 sensor for distance measurement.
 */
void hcsr04_read_init(void);

/**
 * @brief Perform obstacle detection using HC-SR04 sensor.
 *
 * @return The distance to the nearest obstacle in centimeters.
 */
float obstacle_detection(void);

#endif /* INC_HC_SR04_READ_H_ */
