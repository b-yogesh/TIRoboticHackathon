

// #include <stdint.h>               // uncomment if testing as main 1/3
// #include "msp.h"                  // uncomment if testing as main 3/3



// main (void){                     // uncomment if testing as main 3/3
    
    
blinking (void){
    unsigned long i;
    unsigned long j;
    
// Front right P8.5 Yellow LED : 0x20
// Front left  P8.0 Yellow LED : 0x10
// Back right  P8.7 Red LED : 0x80
// Back left   P8.6 Red LED : 0x40
    
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
 
    P5->DIR = 0x30;                             // P5.4 and P5.5 as output
    P2->DIR = 0xC0;                             // P2.6 and P2.7 as output
    P3->DIR = 0xC0;                             // P3.6 and P3.7 as output
    

    P2->OUT = 0x00;                             // no PWM signal for motor -> stopping after reaching the parking slot


    P8->DIR |= 0xE1;                            // P8 LED pins as output
    P8->OUT = 0x00;                             // disabeling all LEDs



    P8->OUT = 0xE1;
    j = 190000;                                 
    while( j > 0)                               //
    {                                           // 
        __delay_cycles(5);                      // wait 5 cycles
        P5->OUT = 0x20;                         // directions: 0x20 360 right
        P2->OUT = 0xC0;                         // enabeling PWM
        P2->OUT = 0;                            // disabeling PWM
       j--;                                    // decrement cycle counter
    }
    
    j = 190000;
        while( j > 0)                           //
    {                                           // 
        __delay_cycles(5);                      // wait 5 cycles
        P5->OUT = 0x10;                         // directions: 0x10 360 left
        P2->OUT = 0xC0;                         // enabeling PWM
        P2->OUT = 0;                            // disabeling PWM
       j--;                                     // decrement cycle counter
    }
    
    
    while(1){               // blinking sequence
    for(i=10000; i>0; i--); // delay
    P8->OUT = 0x70;
    
    
    for(i=10000; i>0; i--); // delay
    P8->OUT = 0x91;

    
    for(i=10000; i>0; i--); // delay
    P8->OUT = 0x00;
    
//   for(i=100000; i>0; i--); // delay
//    P8->OUT = 0xE1;
    

    }
   

}



