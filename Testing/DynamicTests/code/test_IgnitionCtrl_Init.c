/*
 * IgnitionCtrl_Init.c
 *
 * Created: 25/06/2022 21:31:00
 *  Author: Miroslav Mitrovic 
 */

    
#include "test_IgnitionCotrol_Main.h"

tst_GlobalData GlobalDataValues;

void Data_Init(void)
{
	GlobalDataValues.RPM = 0;
	GlobalDataValues.AdvanceAngle = 0;
	GlobalDataValues.IgnitionControlState = en_InitState; 
	GlobalDataValues.IsSynchronised = 0;
	GlobalDataValues.Microseconds = 0;
}


void IgnitionCtrl_Init(void)
{
	GPIO_Init();
	Clock_Init();
	Timer_Init();
	sei();
	GlobalDataValues.IgnitionControlState = en_InitFinished;
	
	
}


void GPIO_Init(void)
{
/*Set Pins 5 and 6 as Output High */
DDRB |= ((1 << PB1) | (1 << PB0) | (1 << PB2) | (1 << PB3) | (1 << PB4));
PORTB &= ( ~(1 << PB1) & ~(1 << PB0) & ~(1 << PB2) & ~(1 << PB3) & ~(1 << PB4));
/*Set Pins 3 and 2 as Input pins*/
DDRB &= (~(1 << PB3) & ~(1 << PB4) & ~(1 << PB2) );

/* No interrupts will be used -Set Pin 7 as Interrupt input*/
//GIMSK = (1 << INT0);					//Set as interrupt on Rising edge
//MCUCR = (1 << ISC00)  | (1 << ISC01 );	//Set Pin as Rising Edge-Sense Register
}
void Clock_Init(void)
{
	
}
/*For one interrupt routine there is a need for about 10 cycles, if we set it up to 1uS at 1 or 8MHz losses are significant.
To be seen if there is a possibility to fetch around 250uS or even 500uS at each ISR and then multiply the counter respectively */
void Timer_Init(void)
{
	TCCR0B |= (1 << CS01);				//Select the clock source-Internal Oscillator clk_io/8 - overflow happens at 256uS(counts)
	TCNT0 = 0;						
	TIMSK |=  (1 << TOIE0);				//Enable Timer0 overflow interrupt 
}