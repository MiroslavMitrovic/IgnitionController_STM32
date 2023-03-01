/*
 * @file      test_IgnitionCtrl_Init.h
 * @authors   Miroslav Mitrović
 * Created on 25 Jun 2022, 17:40
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
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0>
 *
 * @brief [description]
 */

#ifndef TEST_IGNITIONCTRL_INIT_H_
#define TEST_IGNITIONCTRL_INIT_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
//#include <xc.h>
#include <stddef.h>
//#include "avr/interrupt.h"
/*******************************************************************************
 * Defines
 *******************************************************************************/

#define PIN_SET					1U
#define PIN_RESET				0U
#define MASK_PB_3_PIN_SET		8U
#define MASK_PB_4_PIN_SET		16U

#define PIN_CHECK(PIN,MASK,PIN_NO)	((PIN & MASK) >> (PIN_NO))

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
extern uint32_t g_PulseCounter;
extern uint32_t g_uSCounter;
/*******************************************************************************
 * Functions
 *******************************************************************************/
/** @brief Initialization function\n
 *
 *  @params none
 *  @return none
 */
void IgnitionCtrl_Init(void);
/** @brief Initialization of Timer for microseconds Counter\n
 *
 *  @params none
 *  @return none
 */
void Timer_Init(void);
/** @brief Initialization of GPIO registers and Interrupt for input/output Pins\n
 *
 *  @params none
 *  @return none
 */
void GPIO_Init(void);
/** @brief Initialization of clock\n
 *
 *  @params none
 *  @return none
 */
void Clock_Init(void);
/** @brief Initialization of global data and set of its states to default values\n
 *
 *  @params none
 *  @return none
 */
void Data_Init(void);

#endif /* TEST_IGNITIONCTRL_INIT_H_ */