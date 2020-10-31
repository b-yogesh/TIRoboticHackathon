#include "msp.h"
#include <stdint.h>
#include <MoveRobot.h>
#include "Clock.h"


void InitMotor()
{
    P5->DIR = 0x30;                             // P5.4 and P5.5 as output
    P2->DIR = 0xC0;                             // P2.6 and P2.7 as output
    P3->DIR = 0xC0;                             // P3.6 and P3.7 as output
    P5->OUT = 0x00;                             // P5.4 and P5.5 set to low   -> set direction to forward for left (P5.4) and right (5.5) motor
    P3->OUT = 0xC0;                             // P3.6 and P3.7 set to high  -> disable sleep mode for left (P3.7) and right (3.6) motor
    P2->OUT = 0x00;                             // P2.6 and P2.7 set to low   -> no signal for left (P2.7) and right (2.6) motor
}

void MoveRobot(int degree, long int duty, long int cycles)
{
    //case degree:
    //FORWARD: MoveForward(); exit;
    //RIGHT: MoveRight(); exit;
    //BACKWARD: MoveBackward
    
    if (degree == FORWARD)
    {
        MoveForward(duty, cycles);
    }
    else if (degree == BACKWARD)
    {
        MoveBackward(duty, cycles);
    }
}

void MoveForward(long int duty, long int cycles)
{
    P5->OUT = 0x00;                             // P5.4 and P5.5 set to low   -> set direction to forward for left (P5.4) and right (5.5) motor
    long int i = cycles;
    while(i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        Clock_Delay1ms(10);                       // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        Clock_Delay1ms(10); 
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void MoveBackward(long int duty, long int cycles)
{
    P5->OUT = 0x30;                             // P5.4 and P5.5 set to low   -> set direction to backward for left (P5.4) and right (5.5) motor
    long int i = cycles;
    while(i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        Clock_Delay1ms(10);                      // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        Clock_Delay1ms(10); 
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void TurnRight()
{
    P5->OUT = 0x10;                             // P5.4 to low and P5.5 set to high   -> set direction to forward for left (P5.4) and backward for right (5.5) motor
    long int i = 35;
    while(i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        Clock_Delay1ms(10);                      // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        Clock_Delay1ms(10); 
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void TurnLeft()
{
    P5->OUT = 0x20;                             // P5.4 to high and P5.5 set to low   -> set direction to backward for left (P5.4) and forward for right (5.5) motor
    long int i = 35;
    while(i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        Clock_Delay1ms(10);                     // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        Clock_Delay1ms(10); 
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void Turn180()
{
    P5->OUT = 0x20;                             // P5.4 to high and P5.5 set to low   -> set direction to backward for left (P5.4) and forward for right (5.5) motor
    long int i = 70;
    while(i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        Clock_Delay1ms(10);                     // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        Clock_Delay1ms(10); 
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}




