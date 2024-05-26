/**
 * @file car_control.c
 * @author Jacek Bielski && Jakub Wysocki
 * @brief This file contains all functions to control the car.
 * @version 0.1
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "car_control.h"

#define blue_led_Pin GPIO_PIN_13
#define blue_led_GPIO_Port GPIOC
#define foreward_Pin GPIO_PIN_5
#define foreward_GPIO_Port GPIOA
#define backward_Pin GPIO_PIN_6
#define backward_GPIO_Port GPIOA
#define left_Pin GPIO_PIN_9
#define left_GPIO_Port GPIOA
#define right_Pin GPIO_PIN_10
#define right_GPIO_Port GPIOA

/**
 * @brief Set the car to idle state.
 */
void go_idle(void)
{
    HAL_GPIO_WritePin(foreward_GPIO_Port, foreward_Pin, 0);
    HAL_GPIO_WritePin(backward_GPIO_Port, backward_Pin, 0);
}

/**
 * @brief Set the car to move forward.
 */
void go_foreward(void)
{
    HAL_GPIO_WritePin(backward_GPIO_Port, backward_Pin, 0);
    HAL_GPIO_WritePin(foreward_GPIO_Port, foreward_Pin, 1);
}

/**
 * @brief Set the car to move backward.
 */
void go_backward(void)
{
    HAL_GPIO_WritePin(foreward_GPIO_Port, foreward_Pin, 0);
    HAL_GPIO_WritePin(backward_GPIO_Port, backward_Pin, 1);
}

/**
 * @brief Set the car to idle state for turning.
 */
void turn_idle(void)
{
    HAL_GPIO_WritePin(right_GPIO_Port, right_Pin, 0);
    HAL_GPIO_WritePin(left_GPIO_Port, left_Pin, 0);
}

/**
 * @brief Turn the car to the left.
 */
void turn_left(void)
{
    HAL_GPIO_WritePin(right_GPIO_Port, right_Pin, 0);
    HAL_GPIO_WritePin(left_GPIO_Port, left_Pin, 1);
}

/**
 * @brief Turn the car to the right.
 */
void turn_right(void)
{
    HAL_GPIO_WritePin(left_GPIO_Port, left_Pin, 0);
    HAL_GPIO_WritePin(right_GPIO_Port, right_Pin, 1);
}

/**
 * @brief Initialize the car by setting it to idle state.
 */
void car_init(void)
{
    go_idle();
    turn_idle();
}

/**
 * @brief Control the car based on its current state.
 *
 * This function contains logic for steering the car, based on the current state of the car struct. It checks the `car.ride` state to
 * determine the movement of the car (forward, backward, or idle).
 * It also checks the `car.turn` state to determine the direction of the car (left, right, or idle).
 */
void car_control(void)
{
    // Control car's movement based on ride state
    switch (car.ride)
    {
    case 'f':
        if (car.obstacle_distance <= 10)
        {
            go_idle();
        }
        else
        {
            go_foreward();
        }
        break;
    case 'b':
        go_backward();
        break;
    case 's':
        go_idle();
        break;
    default:
        go_idle();
        break;
    }

    // Control car's turning based on turn state
    switch (car.turn)
    {
    case 'l':
        turn_left();
        break;
    case 'r':
        turn_right();
        break;
    default:
        turn_idle();
    }
}
