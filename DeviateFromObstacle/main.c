/* TI_RSLK_bumper
 * T. Lorenzen
 * 08/17/20
 * Code for TI RSLK using 6 bumper switches
 * v1.4 08/17/20 Thorsten 
 */

#include "msp.h"
unsigned long cycles;
unsigned long direction;
unsigned long drive;

int main(void) {                                // this code uses its bumper switches to walk around obstacles while moving around.
    volatile uint32_t i;

    WDT_A->CTL = WDT_A_CTL_PW |                 // Stop WDT
                 WDT_A_CTL_HOLD;

    P5->DIR = 0x30;                             // P5.4 and P5.5 as output -> set direction to forward for left (P5.4) and right (5.5) motor
    P2->DIR = 0xC0;                             // P2.6 and P3.7 as output -> no signal for left (P2.7) and right (2.6) motor
    P3->DIR = 0xC0;                             // P3.6 and P3.7 as output -> disable sleep mode for left (P3.7) and right (3.6) motor
    P4->DIR = 0x00;                             // P4.0 to P4.7 as input -> Interrupt setup for bumper switches
    P4->OUT = 0xED;                             // set pull-up function on P4.0 to P4.7 without P4.1 and P4.4
    P4->REN = 0xFF;                             // enable pull-up/pull-down on P4.0 to P4.7
    P4->IES = 0xFF;                             // Input edge select 1->0
    P4->IFG = 0x00;                             // clear pending interrupt flags

    P5->OUT = 0x00;                             // P5.4 and P5.5 set to low -> set output to forward for left (P5.4) and right (5.5) motor
    P3->OUT = 0xC0;                             // P3.6 and P3.7 set to high -> disable sleep mode for left (P3.7) and right (3.6) motor
    P2->OUT = 0x00;                             // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor

    NVIC->ISER[1] = 1 << ((PORT4_IRQn) & 31);   // Enable Port 4 interrupt on the NVIC
    P4->IE = 0xED;                              // Set Port 4 interrupt enable bits

    while(1)                                    // in this loop the forward moving is realized with a PWM signal
    {                                           // it looks like: l lllll h l l -> 6 cycles low and 1 cycle high
        P5->OUT = 0;                            // P5.4 and P5.5 set to low -> reset output to forward for left (P5.4) and right (5.5) motor
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        __delay_cycles(5);                      // wait 5 cycles
        P2->OUT = 0xC0;                         // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
    }
}

int drive_back(void){
    while(cycles > 0)                           // cycles defined in ISR
    {
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        __delay_cycles(10);                      // wait 5 cycles
        P5->OUT = direction;                    // change direction of left/right motor to backwards
        P2->OUT = drive;                   		// set left/right motor signal (P2.6/7) to high
        P2->OUT = 0;                            // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
        cycles--;                               // decrement cycle counter
    }
    return;
}

void PORT4_IRQHandler(void)                     // Port4 ISR //
{
    if(P4->IFG){                                // check if one bumpers switch high
        cycles = 40000;                    	    // Turn 70000 cycles ~ 90 degrees
        direction = 0x20;                       // Used for turn bit of one motor P5 to make a turn
        drive = 0xC0;                           // Motor drive bit P2
        drive_back();                           // call function for driving backward
        P4->IFG =0;                             // clear all interrupt flags
    }
}