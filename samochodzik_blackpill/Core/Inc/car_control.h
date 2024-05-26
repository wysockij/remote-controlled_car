/**
 * @file car_control.h
 * @author Jacek Bielski
 * @brief Header file containing function prototypes and structure definition for car control.
 * @version 0.1
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __CAR_CONTROL_H
#define __CAR_CONTROL_H

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Structure representing the state of the car.
     */
    typedef struct carStruct
    {
        float obstacle_distance; /**< Distance to the nearest obstacle */
        uint8_t ride;            /**< Direction of movement: forward 'f' or backward 'b' */
        uint8_t turn;            /**< Direction of turning: left 'l' or right 'r' */
        float turn_angle;        /**< Angle of turning */
    } carStruct;

    extern carStruct car; /**< External reference to the car state */

    /**
     * @brief Set the car to idle state.
     */
    void go_idle(void);

    /**
     * @brief Set the car to move forward.
     */
    void go_foreward(void);

    /**
     * @brief Set the car to move backward.
     */
    void go_backward(void);

    /**
     * @brief Set the car to idle state for turning.
     */
    void turn_idle(void);

    /**
     * @brief Turn the car to the left.
     */
    void turn_left(void);

    /**
     * @brief Turn the car to the right.
     */
    void turn_right(void);

    /**
     * @brief Initialize the car by setting it to idle state.
     */
    void car_init(void);

    /**
     * @brief Control the car based on its current state.
     *
     * This function contains logic for steering the car, based on the current state of the car struct.
     */
    void car_control(void);

#ifdef __cplusplus
}
#endif

#endif /* __CAR_CONTROL_H */
