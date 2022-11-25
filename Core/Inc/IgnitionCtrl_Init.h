/*
 * @file      IgnitionCtrl_Init.h
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

#ifndef IGNITIONCTRL_INIT_H_
#define IGNITIONCTRL_INIT_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "IgnitionCotrol_Main.h"
/*******************************************************************************
 * Defines
 *******************************************************************************/

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
extern uint32_t g_PulseCounter;
extern volatile uint32_t g_uSCounter;
/*******************************************************************************
 * Functions
 *******************************************************************************/
/** @brief Initialization function\n
 *
 *  @params none
 *  @return none
 */
void IgnitionCtrl_v_Init(void);
/** @brief Initialization of Timer for microseconds Counter\n
 *
 *  @params none
 *  @return none
 */
void Timer_v_Init(void);
/** @brief Initialization of GPIO registers and Interrupt for input/output Pins\n
 *
 *  @params none
 *  @return none
 */
void GPIO_v_Init(void);
/** @brief Initialization of clock\n
 *
 *  @params none
 *  @return none
 */
void Clock_v_Init(void);
/** @brief Initialization of global data and set of its states to default values\n
 *
 *  @params none
 *  @return none
 */
void Data_v_Init(void);

#endif /* IGNITIONCTRL_INIT_H_ */