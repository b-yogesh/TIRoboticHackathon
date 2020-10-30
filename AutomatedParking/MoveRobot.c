#include "msp.h"
#include <stdint.h>
#include <MoveRobot.h>


void InitMotor()
{
    P5->DIR = 0x30;                             // P5.4 and P5.5 as output
    P2->DIR = 0xC0;                             // P2.6 and P2.7 as output
    P3->DIR = 0xC0;                             // P3.6 and P3.7 as output
    P5->OUT = 0x00;                             // P5.4 and P5.5 set to low   -> set direction to forward for left (P5.4) and right (5.5) motor
    P3->OUT = 0xC0;                             // P3.6 and P3.7 set to high  -> disable sleep mode for left (P3.7) and right (3.6) motor
    P2->OUT = 0x00;                             // P2.6 and P2.7 set to low   -> no signal for left (P2.7) and right (2.6) motor
}

void MoveRobot(int degree, long int cycles)
{
    //case degree:
    //FORWARD: MoveForward(); exit;
    //RIGHT: MoveRight(); exit;
    //BACKWARD: MoveBackward
    
    if (degree == FORWARD)
    {
        MoveForward(cycles);
    }
    else if (degree == BACKWARD)
    
    {
        MoveBackward(cycles);
    }
}

void MoveForward(long int cycles)
{
    P5->OUT = 0x00;                             // P5.4 and P5.5 set to low   -> set direction to forward for left (P5.4) and right (5.5) motor
    long int i = cycles;
    while(i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        __delay_cycles(5);                      // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void MoveBackward(long int cycles)
{
    P5->OUT = 0x30;                             // P5.4 and P5.5 set to low   -> set direction to backward for left (P5.4) and right (5.5) motor
    long int i = cycles;
    while(i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        __delay_cycles(5);                      // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}