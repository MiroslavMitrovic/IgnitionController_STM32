/*
 * @file      IgnitionCtrl_HW_Wrapper.h
 * @authors   Miroslav Mitrović
 * Created on 16 September 2022, 19:09
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
#ifndef IGNITIONCTRL_HW_WRAPPER_
#define IGNITIONCTRL_HW_WRAPPER_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#ifndef __UNIT_TEST__
#include <stddef.h>
#endif /*__UNIT_TEST__*/
#include "IgnitionCotrol_Main.h"
/*******************************************************************************
 * Defines
 *******************************************************************************/
//#define PIN_PINB                PINB
//#define PIN_PINB0               PINB0
//#define PIN_PINB1               PINB1
//#define PIN_PINB2               PINB2
//#define PIN_PINB3               PINB3
//#define PIN_PINB4               PINB4
//#define PIN_PINB5               PINB5

#define PIN_SET					1U
#define PIN_RESET				0U
#define MASK_PB_3_PIN_SET		8U
#define MASK_PB_4_PIN_SET		16U

#define PIN_CHECK(PIN,MASK,PIN_NO)	((PIN & MASK) >> (PIN_NO))
#ifdef __UNIT_TEST__
#define PIN_PINB                0U
#define PIN_PINB0               0U
#define PIN_PINB1               1U
#define PIN_PINB2               2U
#define PIN_PINB3               3U
#define PIN_PINB4               4U
#define PIN_PINB5               5U
#define DDRB                    0U
#define PORTB                   0U
#define TCCR0B                  0U
#define CS01                    0U
#define TCNT0                   0U
#define TIMSK                   0U
#define TOIE0                   0U
#endif/*__UNIT_TEST__*/

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
/** @brief Initialization of Timer for microseconds Counter\n
 *
 *  @params none
 *  @return none
 */
void HW_Timer_v_Init(void);
/** @brief Initialization of GPIO registers and Interrupt for input/output Pins\n
 *
 *  @params none
 *  @return none
 */
void HW_GPIO_v_Init(void);
/** @brief Firing Pin for Cylinder 1 set to HIGH\n
 *
 *  @params none
 *  @return none
 */
void HW_FiringPin_v_Cylinder_1_Set(void);
/** @brief Firing Pin for Cylinder 1 set to LOW\n
 *
 *  @params none
 *  @return none
 */
void HW_FiringPin_v_Cylinder_1_Reset(void);
/** @brief Firing Pin for Cylinder 2 set to HIGH\n
 *
 *  @params none
 *  @return none
 */
void HW_FiringPin_v_Cylinder_2_Set(void);
/** @brief Firing Pin for Cylinder 2 set to LOW\n
 *
 *  @params none
 *  @return none
 */
void HW_FiringPin_v_Cylinder_2_Reset(void);


#endif /* ${include_guard_symbol} */
