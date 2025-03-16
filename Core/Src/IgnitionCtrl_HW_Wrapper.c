/**
 * @file      IgnitionCtrl_HW_Wrapper.c
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
#include "IgnitionCotrol_Main.h"
/*******************************************************************************
 * Defines
 *******************************************************************************/

/*******************************************************************************
 * Local Types and Typedefs
 *******************************************************************************/

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
 volatile uint32_t g_usSinceDetectionCyl1;
 volatile uint32_t g_usSinceDetectionCyl2;
 volatile uint32_t g_uSCounter;
 volatile uint32_t g_uSDebouncingSignalCounter;
 volatile uint8_t  g_signalDebouncingTimerStarted;
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
#ifdef ATMEL_MCU
  /*Set Pins 5 and 6 as Output High */
DDRB |= ((1 << PB1) | (1 << PB0) | (1 << PB2) | (1 << PB3) | (1 << PB4)) | (1 << PB5);
/*Set Pins 3 and 2 as Input pins*/
DDRB &= (~(1 << PB3) & ~(1 << PB2) );
DDRB |= (1 << PB4);
PORTB &= ~(1 << PB1 );
PORTB &= ~(1 << PB0 );
#else
/*TODO: Implement STM32Fxx handling of GPIO INIT*/
#endif /*ATMEL_MCU*/
}

void HW_Timer_v_Init(void)
{
#ifdef ATMEL_MCU
    TCCR0B |= (1 << CS00);   	//Select the clock source-Internal Oscillator clk_io/8 = 1MHz ClockDivider is C00(no divsion) - overflow happens at 256uS(counts)
	TCNT0 = 0;
	TIMSK |=  (1 << TOIE0);				//Enable Timer0 overflow interrupt
#else
/*TODO: Implement STM32Fxx handling of Timer INIT*/
#endif /*ATMEL_MCU*/
	g_uSCounter = 0;
	g_usSinceDetectionCyl1 = 0;
	g_uSDebouncingSignalCounter = 0;
}

void HW_FiringPin_v_Cylinder_1_Set(void)
{
#ifdef ATMEL_MCU
	PORTB |= ( 1<< PB1);
#else
	// HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TestLED1_GPIO_Port, TestLED1_Pin, GPIO_PIN_SET);
#endif /*ATMEL_MCU*/


}

void HW_FiringPin_v_Cylinder_1_Reset(void)
{
#ifdef ATMEL_MCU
    PORTB &= ~( 1<< PB1);
#else
	// HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TestLED1_GPIO_Port, TestLED1_Pin, GPIO_PIN_RESET);
#endif /*ATMEL_MCU*/
}

void HW_FiringPin_v_Cylinder_2_Set(void)
{
#ifdef ATMEL_MCU
	PORTB |= ( 1<< PB0);
#else
	// HAL_GPIO_WritePin(GPIOD, LD5_Pin, GPIO_PIN_SET);
#endif /*ATMEL_MCU*/
}

void HW_FiringPin_v_Cylinder_2_Reset(void)
{
#ifdef ATMEL_MCU
    PORTB &= ~( 1<< PB0);
#else
	// HAL_GPIO_WritePin(GPIOD, LD5_Pin, GPIO_PIN_RESET);
#endif /*ATMEL_MCU*/
}

GPIO_PinState HW_FiringPin_v_Cylinder_1_Status_Read(void)
{
	return	HAL_GPIO_ReadPin(TestLED1_GPIO_Port,TestLED1_Pin);
}

GPIO_PinState HW_FiringPin_v_Cylinder_2_Status_Read(void)
{
	//HAL_GPIO_ReadPin(TestLED1_GPIO_Port,TestLED1_Pin);
}

#ifdef STM32_MCU
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Prevent unused argument(s) compilation warning */
	if(Signal1_IntPin_Pin == GPIO_Pin)
	{
		if(5U < g_uSDebouncingSignalCounter) /* Check if the signal was triggered in time less than 50uS */
		{
			IgnitionControl_v_UpdateSignalTime();
			g_uSDebouncingSignalCounter = 0;
			g_signalDebouncingTimerStarted = 1;
		}
	}
	else if (Signal2_IntPin_Pin == GPIO_Pin)
	{
		if(5U < g_uSDebouncingSignalCounter) /* Check if the signal was triggered in time less than 50uS */
		{
			// IgnitionControl_v_UpdateSignalTime();
			// g_uSDebouncingSignalCounter = 0;
		}
	}
	else{}
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}
#endif /* STM32_MCU */
