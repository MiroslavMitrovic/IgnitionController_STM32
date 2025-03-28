/*
 * @file      IgnitionCotrol_Main.h
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
#ifndef IGNITIONCOTROL_MAIN_H_
#define IGNITIONCOTROL_MAIN_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "IgnitionCtrl_Config.h"
#include "main.h"
#include "IgnitionCtrl_HW_Wrapper.h"
#include "stdbool.h"
#include "stdint.h"
#include "math.h"
/*******************************************************************************
 * Local Types and Typedefs
 *******************************************************************************/
typedef enum en_Calculation_States
{
	en_InitState,                   ///< Initialization State                   0
	en_InitFinished,                ///< Initialization Finished                1
    en_SynchronizationOngoing,      ///< Synhronization is ongoing              2 
    en_Synchronized,                ///< Synchronization finished               3
	en_CalculationOngoing,          ///< Ignition Angle calculation ongoing     4 
    en_CalculationFinished,         ///< Ignition Angle calculation finished    5
	en_IdleStateCalculation,        ///< Idle state                             6
    en_EngineCrankingCylinder1,     ///< Engine Cranking state                  7
    en_EngineCrankingCylinder2,     ///< Engine Cranking state                  8
	en_MaxNumberOfCalculationStates
}ten_Calculation_States;

typedef enum en_Firing_States
{
	en_FiringStateInit,                     ///< Initialization of state handler        0
    en_IdleStateFiringState,                ///< Idle state                             1
	en_FiringCylinder1,                     ///< Firing cylinder 1 ongoing              2
    en_FiringCylinder1Cranking,             ///< Firing cylinder 1 during cranking      3
    en_FiringCylinder1Completed,            ///< Firing cylinder 1 completed            4
    en_FiringCylinder2Cranking,             ///< Firing cylinder 2 during cranking      5
    en_FiringCylinder2,                     ///< Firing cylinder 2 ongoing              6
    en_FiringCylinder2Completed,            ///< Firing cylinder 2 completed            7   
    en_RPMHardLimitState,                   ///< Hard Limit state                       8
    en_FiringCylinder1CrankingCompleted,    ///< Firing cylinder 1 during cranking      9
   	en_MaxNumberOfFiringStates
}ten_Firing_States;

typedef volatile struct 
{
	ten_Calculation_States CalculationState;
    ten_Firing_States       FiringState;
    ten_Firing_States       FiringStateCylinder2;
	uint16_t RPM;
    uint16_t RPM2;
	uint8_t SynchronizationStatus;
	uint8_t AdvanceAngle;
	uint32_t Microseconds;
    uint32_t FiringTimeCyl_1;
    uint32_t FiringTimeCyl_2;
    uint32_t TimeElapsedSinceDetectionCylinder1;
    uint32_t TimeElapsedSinceDetectionCylinder2;
    bool  isCylinder1CoilCharging;
    bool  isCylinder2CoilCharging;
}tst_GlobalData;

typedef enum
{
    en_IgnCtrl_OK,                  ///< Status is OK
    en_IgnCtrl_NOK,                 ///< Status is Not OK
    en_StatusMaxNumber
}ten_IgnitionControl_Status;
typedef enum
{
    en_FiringStateInactive,         ///< Firing State not active-Coil not charging
    en_FiringStateActive,           ///< Firing State active-Coil is charging
    en_FiringFinished,              ///< Firing State finished-coil discharged
    en_FiringStateMaxNumber
}ten_IgnitionControl_FiringCylinderState;

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
extern volatile tst_GlobalData GlobalDataValues;
extern volatile uint32_t g_uSDebouncingSignalCounter;
/*******************************************************************************
 * Functions
 *******************************************************************************/
/** @brief /*Function to calculate microseconds based on Timer counter increment for each 256uS.\n
 *  @param  [in] u32_MicrosecondsTicks
 *  @return Microseconds
 */
extern uint32_t Calculate_u_Microseconds(uint32_t u32_MicrosecondsTicks);
/** @brief Main Function that will be called synchroniously and will check the states\n
 *  @param  none
 *  @return none
 */
void IgnitionControl_v_Main(void);
/** @brief /* Check for the first sensor is available, and if it is, it returns the status and
 * sets the time for first sensor \n
 *  @param  none
 *  @return Sensor Status
 */
extern uint8_t IgnitionControl_u_FirstSensorCheck_IT(void);
/** @brief /* Check for the second sensor is available, and if it is, it returns the status and
 * sets the time for first sensor \n
 *  @param  none
 *  @return Sensor Status
 */
extern uint8_t IgnitionControl_u_SecondSensorCheck_IT(void);
/** @brief /* Updates the time value and sets the availability of sensor  \n
 *  @param  none
 *  @return Sensor Status
 */
extern void IgnitionControl_v_UpdateSignalTime(void);
/** @brief /* Updates the time value and sets the availability of sensor for second cylinder.  \n
 *  @param  none
 *  @return Sensor Status
 */
extern void IgnitionControl_v_UpdateSignalTimeCylinder2(void);

/*******************************************************************************
 * Specific Includes
 *******************************************************************************/
#include "IgnitionCtrl_CalculateTimesAndAngles.h"
#include "IgnitionCtrl_IgnAngleTable.h"
#include "IgnitionCtrl_Init.h"

#endif /* IGNITIONCOTROL_MAIN_H_ */
