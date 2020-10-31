#include "msp.h"
#include "LineSensor.h"
#include "MoveRobot.h"
#include "Clock.h"


#define MOVE_SPEED 2200 // the standard movement speed of the robot while going to the free parking slot


// State variables
enum State
{
    SEARCHING, // searching for a parking slot
    OBSTACLE, // find a parking slot occupied
    PARKED // showing the solution
};
enum State state; // the robot's state

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
   
    LineSensor_Init(); // initialize the line/light sensors
	unsigned long lineDetected; // value last read from the line sensors
	
	InitMotor();
	// It starts to searching for a parking place
	state = SEARCHING; 
	//MoveForward(10,50);
	
	while(1){
    	if (state ==  SEARCHING) 
    	{
    	   lineDetected = LineDetection(); // re-read the line sensor so that we don't use an outdated value    

    	   if (lineDetected < 0x3C) // if the sensors are all white (off the line)- it parked! I am assuming it will follow a line
            {
                MotorStop();
                state = PARKED;
            }
            else if (lineDetected >= 0xFA) // if the sensors are all black (T or 4-way intersection)
            {
                TurnLeft();
            }
            else 
            {
                MoveForward(10,50); 
            }
     	}
	}
}
