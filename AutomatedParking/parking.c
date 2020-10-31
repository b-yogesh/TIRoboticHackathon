/*THIS CODE IS NOT TESTE -WAITING FOR THE MOTOR.H LIBRARY AND BUMPER LIBRARY
It will implement the main function
This code is based on codes provided by the Texas Instruments and Christopher Andrews

Copyright (C) 2012 - 2017 Texas Instruments Incorporated - http://www.ti.com/
Copyright 2019 Christopher Andrews
*/


#include "msp.h"
#include "LineSensor.h"
#include "MoveRobot.h"

uint8_t lineSensors; // value last read from the line sensors

// State variables
enum State
{
    SEARCHING, // searching for a parking slot
    OBSTACLE, // find a parking slot occupied
    PARKED // showing the solution
};
enum State state; // the robot's state

#define MOVE_SPEED 2200 // the standard movement speed of the robot while going to the free parking slot

// Moves the robot forward approximately half its length.
inline void MoveForwardHalfCar()
{
    Motor_Forward(MOVE_SPEED, 27 * 1675 / MOVE_SPEED);
}


// Moves the robot forward slightly under half its length.
inline void MoveForwardUnderHalfCar()
{
    Motor_Forward(MOVE_SPEED, 22 * 1675 / MOVE_SPEED);
}

// Moves the robot backward twice its length.
inline void MoveBackwardTwiceCar(){
    Motor_Backward(MOVE_SPEED, 4*27 * 1675 / MOVE_SPEED);
    
}

/**
void main(void){
    
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    
    //Initialize everything
    
    LineSensor_Init(); // initialize the line/light sensors
    state = SEARCHING; //  default
    Motor_ForwardSimple(MOVE_SPEED, 25);
    

    while(1){
        uint8_t sensors = lineSensors; // get the current value of lineSensors in case it is updated mid-loop
        
        if (state == SEARCHING) {
            
            if (sensors == 0x00) // if the sensors are all white (off the line)- it parked! I am assuming it will follow a line
            {
                Motor_StopSimple();
                state = PARKED;
            }
            
    
            else if (sensors == 0xFF) // if the sensors are all black (T or 4-way intersection)
            {
                MoveForwardHalfCar(); // align the wheels with the crossing line
                lineSensors = LineSensor_Read(); // re-read the line sensor so that we don't use an outdated value

            }
            
            
            else if ((sensors & 0xE0) == 0xE0) // if there's a left turn available
            {
                MoveForwardHalfCar(); // align the wheels with the crossing line
                sensors = lineSensors = LineSensor_Read(); // re-read the line sensors
                Motor_SpinLeft90(); // take the left path
                Clock_Delay1ms(10); // wait 0.1 sec
                lineSensors = LineSensor_Read(); // re-read the line sensor so that we don't use an outdated value
            }
            
            
            else if ((sensors & 0x07) == 0x07) // if there's a possible straightAndRight intersection or a right turn
            {
                Motor_ForwardSimple(MOVE_SPEED, 5); // move forward a bit and check if it's still only a right turn or a horizontal line (still won't know if straight is an option yet)
                sensors = lineSensors = LineSensor_Read(); // re-read the line sensors
                if ((sensors & 0xE0) != 0xE0) // if it's still a straightAndRight intersection or a right turn (the left 3 sensors are not all on)
                {
                    MoveForwardUnderHalfCar(); // align the wheels with the crossing line
                    Clock_Delay1ms(10); // wait 0.1 sec
                    sensors = lineSensors = LineSensor_Read(); // re-read the line sensors
                    if (sensors == 0x00) // if the line sensors are all white, meaning there's no forward option
                    {
                        Motor_SpinRight90(); // there was only a right turn, so turn right
                        Clock_Delay1ms(10); // wait 0.1 sec
                        lineSensors = LineSensor_Read(); // re-read the line sensor so that we don't use an outdated value
                    }

                }
            }
            
            
            else if ((sensors & 0xE0) == 0xE0) // if there's a left turn available
            {
                MoveForwardHalfCar(); // align the wheels with the crossing line
                sensors = lineSensors = LineSensor_Read(); // re-read the line sensors
                Motor_SpinLeft90(); // take the left path
                Clock_Delay1ms(10); // wait 0.1 sec
                lineSensors = LineSensor_Read(); // re-read the line sensor so that we don't use an outdated value
            }
            
            
            else if ((sensors & 0x07) == 0x07) // if there's a possible straightAndRight intersection or a right turn
            {
                Motor_ForwardSimple(MOVE_SPEED, 5); // move forward a bit and check if it's still only a right turn or a horizontal line (still won't know if straight is an option yet)
                sensors = lineSensors = LineSensor_Read(); // re-read the line sensors
                if ((sensors & 0xE0) != 0xE0) // if it's still a straightAndRight intersection or a right turn (the left 3 sensors are not all on)
                {
                    MoveForwardUnderHalfCar(); // align the wheels with the crossing line
                    Clock_Delay1ms(10); // wait 0.1 sec
                    sensors = lineSensors = LineSensor_Read(); // re-read the line sensors
                    if (sensors == 0x00) // if the line sensors are all white, meaning there's no forward option
                    {
                        Motor_SpinRight90(); // there was only a right turn, so turn right
                        Clock_Delay1ms(10); // wait 0.1 sec
                        TimerA0_Stop(); // stop flashing the top right LED
                        lineSensors = LineSensor_Read(); // re-read the line sensor so that we don't use an outdated value
                    }

                }
            }
            
            
            // None of the special if-clauses above were taken, so now just follow the black line.
            else if ((sensors & 0x80) == 0x80) // if sensor 7 is black
            {
                Motor_RightSimple(MOVE_SPEED, 2); // turn left a significant amount
                Motor_ForwardSimple(MOVE_SPEED, 2); // go forward a bit
            }
            
            else if ((sensors & 0x40) == 0x40) // if sensor 6 is black
            {
                Motor_RightSimple(MOVE_SPEED, 2); // turn left a medium amount
                Motor_ForwardSimple(MOVE_SPEED, 3); // go forward a bit
            }
            
            else if ((sensors & 0x20) == 0x20) // if sensor 5 is black
            {
                Motor_RightSimple(MOVE_SPEED, 1); // turn left a small amount
                Motor_ForwardSimple(MOVE_SPEED, 2); // go forward a bit
            }
            
            else if ((sensors & 0x01) == 0x01) // if sensor 0 is black
            {
                Motor_LeftSimple(MOVE_SPEED, 2); // turn right a significant amount
                Motor_ForwardSimple(MOVE_SPEED, 2); // go forward a bit
            }
            
            else if ((sensors & 0x02) == 0x02) // if sensor 1 is black
            {
                Motor_LeftSimple(MOVE_SPEED, 2); // turn right a medium amount
                Motor_ForwardSimple(MOVE_SPEED, 3); // go forward a bit
            }
            
            else if ((sensors & 0x04) == 0x04) // if sensor 2 is black
            {
                Motor_LeftSimple(MOVE_SPEED, 1); // turn right a small amount
                Motor_ForwardSimple(MOVE_SPEED, 2); // go forward a bit
            }
            
            else if (((sensors & 0x10) == 0x10) || // if sensor 4 is black
                     ((sensors & 0x08) == 0x08)) // or if sensor 3 is black
            {
                Motor_ForwardSimple(MOVE_SPEED, 2);
            }
            

	    }
        }else if (state == OBSTACLE){
            // it moves backwards and tries to find the next spot
            MoveBackwardTwiceCar()
            // KEEP IT SIMPLE: TRY TO KEEP THE DISTANCE BETWEEN THE PARKING SLOTS FIXED (SECOND PARAMETER)!!!!!!
            // need to be less than the distance to the obstacle
            Motor_LeftSimple(MOVE_SPEED, 2);// we need to ajust the amount of time - second parameter
            Motor_LeftSimple(MOVE_SPEED, 2);// we need to ajust the amount of time - second parameter
            Motor_ForwardSimple(MOVE_SPEED, 2);
            state = SEARCHING;
            
        }    
        
        else if(state == PARKED){
                Motor_StopSimple(); // stop the motors
                CelebrationSatisfaction();
        }
        
    }

    
    
    
     }     
     */
