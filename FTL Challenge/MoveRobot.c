#include "msp.h"
#include <stdint.h>
#include <MoveRobot.h>
#include "Clock.h"

#define PWM_SCALE 8 // used in the motor functions to make PWM smoother (not so clicky). Higher scale = increased smoothness but higher minimum duty.

void InitMotor()
{
    P5->DIR = 0x30;                             // P5.4 and P5.5 as output
    P2->DIR = 0xC0;                             // P2.6 and P2.7 as output
    P3->DIR = 0xC0;                             // P3.6 and P3.7 as output
    P5->OUT = 0x00;                             // P5.4 and P5.5 set to low   -> set direction to forward for left (P5.4) and right (5.5) motor
    P3->OUT = 0xC0;                             // P3.6 and P3.7 set to high  -> disable sleep mode for left (P3.7) and right (3.6) motor
    P2->OUT = 0xC0;                             // P2.6 and P2.7 set to high  
}

void MoveRobot(int degree, long int duty, long int cycles)
{
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
    while (i > 0)                                // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        __delay_cycles(5);
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        __delay_cycles(5);
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }

    /**
    P5->OUT = 0x00; // both motors forward
    //P3->OUT |= 0xC0; // don't sleep
    int duty1 = 10000 - duty;

    int i;
    int max = 0.23 * cycles * PWM_SCALE;
    for (i = 0; i < max; i++) // run max times
    {
        P2->OUT |= 0xC0; // turn the motor on
        Clock_Delay1ms(1.0f * duty / 10000 * 48 / PWM_SCALE * 1000);
        //P2->OUT &= ~0xC0; // turn the motor off
        //Clock_Delay1us(1.0f * duty1 / 10000 * 48 / PWM_SCALE * 1000);
    }
     **/
}

void MoveBackward(long int duty, long int cycles)
{
    P5->OUT = 0x30;                             // P5.4 and P5.5 set to low   -> set direction to backward for left (P5.4) and right (5.5) motor
    long int i = cycles;
    while (i > 0)                                // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        __delay_cycles(5);                      // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        __delay_cycles(5);
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void TurnRight()
{
    P5->OUT = 0x10;                             // P5.4 to low and P5.5 set to high   -> set direction to forward for left (P5.4) and backward for right (5.5) motor
    long int i = 120;
    while (i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        __delay_cycles(5);                      // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        __delay_cycles(5);
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void TurnLeft()
{
    P5->OUT = 0x20;                             // P5.4 to high and P5.5 set to low   -> set direction to backward for left (P5.4) and forward for right (5.5) motor
    long int i = 120;
    while (i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        __delay_cycles(5);                    // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        __delay_cycles(5);
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

void Turn180()
{
    P5->OUT = 0x20;                             // P5.4 to high and P5.5 set to low   -> set direction to backward for left (P5.4) and forward for right (5.5) motor
    long int i = 120;
    while (i > 0)                               // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        __delay_cycles(5);                    // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        __delay_cycles(5);
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        i--;
    }
}

// Stops both motors, puts driver to sleep.
void MotorStop(void)
{
    P5->OUT &= ~0x00; // direction = 0 (forward)
    P2->OUT &= ~0xC0; // PWM = 0
    P3->OUT &= ~0xC0; // low current sleep mode
}
