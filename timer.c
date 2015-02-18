/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 14745600
#define ONE_MILLISECOND 57
#define ONE_MICROSECOND 14

    //TODO: Create a delay for "delay" micro seconds using timer 2
    void delayUs(unsigned int delay)
{
    TMR2 = 0; //According to the datasheet this should be reset automatically, but it does not sometimes.
    PR2 = delay*ONE_MICROSECOND; //Period register value calculated from lecture
    T2CONbits.TCKPS = 0; //prescalar 1
    IFS0bits.T2IF = 0; // Timer 2 interrupt flag down
    T2CONbits.TON = 1; // Turn timer 2 on


    // Wait until the timer 1 interrupt flag goes up. This is done in hardware.
    while(IFS0bits.T2IF == 0);

    IFS0bits.T2IF = 0; // Put the flag down afterwards.
    T2CONbits.TON = 0; // Turn the timer off so it does not keep counting.
}


/* Delay 1 millisecond * the input (delay)
 */
void delayMs(unsigned int delay)
{
    TMR1 = 0; //According to the datasheet this should be reset automatically, but it does not sometimes.
    PR1 = delay*ONE_MILLISECOND; //Period register value calculated from lecture
    T1CONbits.TCKPS = 0b11; //prescalar 256
    IFS0bits.T1IF = 0; // Timer 2 interrupt flag down
    T1CONbits.TON = 1; // Turn timer 2 on


    // Wait until the timer 1 interrupt flag goes up. This is done in hardware.
    while(IFS0bits.T1IF == 0);

    IFS0bits.T1IF = 0; // Put the flag down afterwards.
    T1CONbits.TON = 0; // Turn the timer off so it does not keep counting.
}