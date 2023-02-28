/*
 * @file      test_IgnitionCotrol_Main.h
 * @authors   Miroslav Mitrović
 * Created on 26 Jun 2022, 13:26
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
#ifndef TEST_IGNITIONCOTROL_MAIN_H_
#define TEST_IGNITIONCOTROL_MAIN_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "test_IgnitionCtrl_Config.h"
#include "stdbool.h"
#include "stdint.h"
#include "math.h"

#define PINB    0U
#define PINB5   5U
#define PINB4   4U
#define PINB3   3U
#define PINB2   2U
#define PINB1   1U
#define PINB0   0U
/*******************************************************************************
 * Local Types and Typedefs
 *******************************************************************************/
typedef enum en_IgntionControl_States
{
	en_InitState,
	en_InitFinished,
    en_SynchronizationOngoing,
    en_Synchronized, 
	en_CalculationOngoing,
    en_CalculationFinished,
	en_FiringCylinder1,
	en_FiringCylinder2,
    en_IdleState,
	en_MaxNumberOfStates
}ten_IgntionControl_States;

typedef struct 
{
	ten_IgntionControl_States IgnitionControlState;
	uint16_t RPM;
	uint8_t IsSynchronised;
	uint8_t AdvanceAngle;
	uint32_t Microseconds;
}tst_GlobalData;
/*******************************************************************************
 * Global Variables
 *******************************************************************************/
extern tst_GlobalData GlobalDataValues; 
/*******************************************************************************
 * Functions
 *******************************************************************************/

extern uint32_t CalculateMicroseconds(uint32_t u32_MicrosecondsTicks);
/*Main Function that will be called synchroniously and will check the states*/
void IgnitionControl_Main(void);

/*******************************************************************************
 * Specific Includes
 *******************************************************************************/
#include "test_IgnitionCtrl_CalculateTimesAndAngles.h"
#include "test_IgnitionCtrl_IgnAngleTable.h"
#include "test_IgnitionCtrl_Init.h"

#endif /* IGNITIONCOTROL_MAIN_H_ */