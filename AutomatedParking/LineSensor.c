/* LineSensor.c
 * This file contains code related to the line sensors, including
 * initialization and reading the sensors. 
 * Code adapted for the application "Automated Parking"
 
Copyright (C) 2012 - 2017 Texas Instruments Incorporated - http://www.ti.com/
Copyright 2019 Christopher Andrews
*/

#include "msp.h"
#include "LineSensor.h"


uint8_t lineSensors; // value last read from the line sensors

// State variables
enum State
{
    STOPPED, // was just turned on or was stopped part-way through running
    RUNNING, // solving the maze
    WIN, // found the treasure
    SOLUTIONING // showing the solution
};
enum State state; // the robot's state

#define MOVE_SPEED 2200 // the standard movement speed of the robot while maze solving


void Clock_Delay1us(uint32_t n){
    // Simple delay function which delays about n microseconds at 48MHz.
    n = (382*n) / 100;; // 1 us, tuned at 48 MHz
    while (n) // while n > 0 (run n times)
    {
        n--; // decrement n so while-loop runs n times
    }
}
    

// Initializes the line sensor bar.
void LineSensor_Init()
{
    // P5.3 is the IR LED
    P5->SEL0 &= ~0x08;
    P5->SEL1 &= ~0x08; // set P5.3 to GPIO
    P5->DIR |= 0x08; // set P5.3 to output
    P5->OUT &= ~0x08; // set P5.3 low

    // P7.0 to P7.7 are the light sensors
    P7->SEL0 = 0;
    P7->SEL1 = 0; // set all P7 pins to GPIO
    P7->DIR = 0; // set all P7 pins to input
    P7->REN = 0; // disable pull resistors on P7 pins
}

// Read the line sensors and returns the value as an 8-bit unsigned int.
// 0 = white, 1 = black.
// Bit 0 = right-most sensor.
// Bit 7 = left-most sensor.
uint8_t LineSensor_Read()
{
    P5->OUT |= 0x08; // set P5.3 high (turn on LED)
    P7->DIR = 0xFF; // set P7 as output
    P7->OUT = 0xFF; // set P7 pins high
    Clock_Delay1us(10); // delay 10us to charge the capacitors
    P7->DIR = 0; // set P7 as input
    Clock_Delay1us(800); // delay 0.8ms to discharge the capacitors slightly
    uint8_t result = P7->IN; // read P7
    P5->OUT &= ~0x08; // set P5.3 low (turn off LED)
    return result;
}
