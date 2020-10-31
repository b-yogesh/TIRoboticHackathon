/* TI_RSLK_LineFollwer
 * T. Lorenzen
 * 08/17/20
 * Code for TI RSLK follwing the black line on the ground
 * with its 8 photo transistors it can distinquish bright/dark surfaces
 * v1.0 08/17/20 Thorsten 
 */

#include "msp.h"
#include <stdint.h>
#include "MoveRobot.h"

int main(void) {                            // this code checks the line sensor signal and decides to activate the left motor, the right motor, or both

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;
    InitMotor();
    while (1)
    {
    MoveRobot(FORWARD, 15, 100000);
    __delay_cycles(2000);
    MoveRobot(BACKWARD, 15, 100000);
    __delay_cycles(2000);
    Turn180();
    __delay_cycles(2000); 
    MoveRobot(BACKWARD, 15, 100000);
     __delay_cycles(2000);
    MoveRobot(FORWARD, 15, 100000);
     __delay_cycles(2000);
     TurnLeft();
    __delay_cycles(2000);
    MoveRobot(FORWARD, 15, 100000);
     __delay_cycles(2000);
       TurnRight();
    __delay_cycles(2000);
    MoveRobot(FORWARD, 15, 100000);
     __delay_cycles(2000);
    //__delay_cycles(2000); 
    }
}

