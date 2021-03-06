/* LineSensor.h
 * This file contains code related to the line sensors, including
 * initialization and reading the sensors. 
 * Code adapted for the application "Automated Parking"
 
Copyright (C) 2012 - 2017 Texas Instruments Incorporated - http://www.ti.com/
Copyright 2019 Christopher Andrews
*/

#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

void LineSensor_Init();
uint8_t LineSensor_Read();

#endif /** LINE_SENSOR_H **/
