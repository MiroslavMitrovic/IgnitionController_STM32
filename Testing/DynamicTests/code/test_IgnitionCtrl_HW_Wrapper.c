/**
 * @file      test_IgnitionCtrl_HW_Wrapper.c
 * @authors   Miroslav Mitrovic
 * Created on September 16, 2022, 7:33 PM
 * @Copyright 2022 by Miroslav Mitrovic <mmitrovicmas13@gmail.com>
 *
 * This file is part of open source application.
 * 
 * Open source application is free software: you can redistribute 
 * it and/or modify it under the terms of the GNU General Public 
 * License as published by the Free Software Foundation, either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Open source application is distributed in the hope that it will 
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this application.  If not, see <http://www.gnu.org/licenses>.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 *
 * @brief [description]
 */
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "test_IgnitionCotrol_Main.h"
/*******************************************************************************
 * Defines
 *******************************************************************************/

/*******************************************************************************
 * Local Types and Typedefs
 *******************************************************************************/

/*******************************************************************************
 * Global Variables
 *******************************************************************************/

/*******************************************************************************
 * Static Function Prototypes
 *******************************************************************************/

/*******************************************************************************
 * Static Variables
 *******************************************************************************/

/*******************************************************************************
 * Functions
 *******************************************************************************/
void HW_GPIO_v_Init(void)
{
  /*Set Pins 5 and 6 as Output High */
DDRB |= ((1 << PB1) | (1 << PB0) | (1 << PB2) | (1 << PB3) | (1 << PB4));
PORTB &= ( ~(1 << PB1) & ~(1 << PB0) & ~(1 << PB2) & ~(1 << PB3) & ~(1 << PB4));
/*Set Pins 3 and 2 as Input pins*/
DDRB &= (~(1 << PB3) & ~(1 << PB4) & ~(1 << PB2) );
}

void HW_Timer_v_Init(void)
{
    TCCR0B |= (1 << CS01);				//Select the clock source-Internal Oscillator clk_io/8 - overflow happens at 256uS(counts)
	TCNT0 = 0;						
	TIMSK |=  (1 << TOIE0);				//Enable Timer0 overflow interrupt 
}