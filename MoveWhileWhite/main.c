/* TI_RSLK_LineFollwer
 * T. Lorenzen
 * 08/17/20
 * Code for TI RSLK follwing the black line on the ground
 * with its 8 photo transistors it can distinquish bright/dark surfaces
 * v1.0 08/17/20 Thorsten 
 */

#include "msp.h"
#include <stdint.h>
#include "celebration.h"
unsigned long i;
unsigned int time=1000;
unsigned long readout=0;
unsigned long readoutleft=0;
unsigned long readoutright=0;

int main(void) {                            // this code checks the line sensor signal and decides to activate the left motor, the right motor, or both
    volatile uint32_t i;                    // It should move forward turn left, turn right and go back to start position

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;

    P5->DIR = 0x38;                         // P5.4 and P4.5 motor drive as output and set P5.3 IR LED output driver
    P2->DIR = 0xC0;                         // P2.6 and P3.7 as output set to output driving the motor
    P3->DIR = 0xC0;                         // P3.6 and P3.7 as output to control motor deriver sleep mode
    P5->OUT = 0x00;                         // P5.4 and P5.5 set to low -> set direction to forward for left (P5.4) and right (5.5) motor
    P3->OUT = 0xC0;                         // P3.6 and P3.7 set to high -> disable sleep mode for left (P3.7) and right (3.6) motor
    P2->OUT = 0x00;                         // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
    P9->DIR = 0x04;                         // P9.2 LED driver control set to output driver
    P9->OUT = 0x00;                         // P9.2 clear LED driver control

    while(1)
    {                                       // read line sensor signal after charging the caps and waiting for 1ms.
        P5->DIR = 0x38;                     // set P5.3 (IR LED) as output
        P5->OUT = 0x08;                     // turn on P5.3 (IR LED)
        P9->OUT = 0x04;                     // turn on P9.2 (IR LED)
        P7->DIR = 0xFF;                     // P7.0 to P7.7 (IR Sensors) as output
        P7->OUT = 0xFF;                     // turn on P7 to charge caps
        __delay_cycles(10);                 // wait 10 x 1us before start
        P7->DIR = 0x00;                     // P7.0 to P7.7 (IR Sensors) as inputs
        __delay_cycles(2000);               // wait 1000 x 1us for caps to discharge
         readout = P7->IN;                  // read IR sensor values
        P5->OUT = 0x00;                     // turn off P5.3 (IR LED)

        readoutleft = readout/16;           // separate left and right side of line sensor
        readoutright = readout%16;

        if(readout== 0xFF)// it stops if it is black
        {
                P2->OUT = 0;// P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
                celebration();
                __delay_cycles(100);                // wait x cycles

        }
        else if(readoutleft>readoutright*2)
        {
            i = 1000;                               // set i to 1000 -> number of cycles
            while(i > 0)                            // in this loop the left moving is realized with a PWM signal
            {
                P2->OUT = 0;                        // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
                __delay_cycles(100);                // wait x cycles
                P2->OUT = 0xC0;                     // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
                P2->OUT = 0x40;                     // P2.6 set to high -> enable signal for right (2.6) motor
                __delay_cycles(2);                  // wait x cycles
                P2->OUT = 0;                        // P2.6 set to low -> no signal for right (2.6) motor
                i--;                                // decrement cycle counter
            }
        }
        else if(readoutleft<readoutright*2)
        {
            i = 1000;                               // set i to 100000 -> number of cycles
            while(i > 0)                            // in this loop the right moving is realized with a PWM signal
            {
                P2->OUT = 0;                        // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
                __delay_cycles(100);                // wait 30 cycles
                P2->OUT = 0xC0;                     // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
                P2->OUT = 0x80;                     // P2.7 set to high -> enable signal for left (P2.7) motor
                __delay_cycles(2);                  // wait 30 cycles
                P2->OUT = 0;                        // P2.7 set to low -> no signal for left motor
                i--;                                // decrement cycle counter
            }
        }
        else if(readoutleft==readoutright)
        {
            i = 1000;                               // set i to 100000 -> number of cycles
            while(i > 0)                            // in this loop the forward moving is realized with a PWM signal
            {
                P2->OUT = 0;                        // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
                __delay_cycles(5);                  // wait 30 cycles
                P2->OUT = 0xC0;                     // P2.6 and P2.7 set to high -> enable signal for left (P2.7) and right (2.6) motor
                P2->OUT = 0;                        // P2.6 and P2.7 set to low -> no signal for left (P2.7) and right (2.6) motor
                i--;                                // decrement cycle counter
            }
        }

    }
}
