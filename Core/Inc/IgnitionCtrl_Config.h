/*
 * @file      IgnitionCtrl_Config.h
 * @authors   Miroslav Mitrović
 * Created on 24 July 2022, 17:40
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
#ifndef IGNITIONCTRL_CONFIG_H
#define IGNITIONCTRL_CONFIG_H

/*If ATMEL MCU is used uncomment below define*/
//#define ATMEL_MCU

/*If STM and Interrupts are used uncomment below define*/
//#define STM_INTERRUPT

#define STM32_MCU
#ifdef ATMEL_MCU
#define F_CPU                        1000000UL           ///< 8MHz
#endif /*ATMEL_MCU*/
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include <stdio.h>
#include <stdint.h>
/*******************************************************************************
 * Defines
 *******************************************************************************/

#define IGNITION_ANGLE_TABLE_COLUMNS 2U
#define IGNITION_ANGLE_TABLE_ROWS	 10U
#define IGNITION_DWELL_TIME_US       2500U                ///< Ignition coil dwell time in uS
#define IS_ENGINE_ODD_FIRE
#define USING_CRANK_SIGNAL								///< Using signal from Crankshaft for RPM calculation
//#define USING_CAM_SIGNAL								///< Using signal from Camshaft for RPM calculation
#define USING_ADVANCE_TIMING							///< Using Advance timing for calculation of firing angles
//#define USING_FIXED_TIMING							///< Using Fixed timing for calculation of firing angles
#define IGNITION_STATIC_ADVANCE_ANGLE	11U				///< Static ignition advance angle
#ifdef USING_FIXED_TIMING
#define FIXED_TIMING_ANGLE		30U						///< Fixed timing angle value in deg
#endif /*USING_FIXED_TIMING*/
#define MAX_TIME_FOR_SIGNAL_AVAILABILITY 2000000U		///< Time(uS) in which signal should appear, if not reset the timings and return RPM to 0
#define SIGNAL_DEBOUNCE_MULTIPLIER		 0U				///< Multiplier for signal debounce time 256uS times multiplier
#define MAX_RPM							 8500U			///< Maximum RPM value
/*Macro check is engine even or odd firing*/
#ifdef IS_ENGINE_ODD_FIRE
#define ODD_FIRE_ANGLE_IN_DEG        225U                ///< Engine Fire Angle in degrees           
#else
#define EVEN_FIRE_ANGLE_IN_DEG       180U                ///< Even Fire distribution
#endif
#define CRANKING_RPM				450U				///< Max Cranking RPM
#define CRANKING_DWELL_TIME_US		5000U				///< Cranking ignition coil dwell time in uS
/*Status defines*/
#define E_OK    0U
#define E_NOK   1U 
#define E_BUSY  2U 

/*Definitions for Sensor Availability flag*/
#define SENSOR_1_AVAILABLE 0U
#define SENSOR_2_AVAILABLE 1U

#define SENSOR_NOT_AVAILABLE 0xFFU

// #define SENSOR_POLLING_MODE  						///< Sensors are configured in polling mode
#define SENSOR_INTERRUPT_MODE							///< Sensors are configured in interrupt mode


#define IN_SYNC            1U							///< Engine RPMs are synchronized
#define OUT_OF_SYNC        0U							///< Engine RPMs are not synchronized


/*Configuration error handling*/
#ifdef CRANK_SIGNAL
	#ifdef CAM_SIGNAL
		#error "CRANK and CAM both signals defined, please choose only one!"
	#endif
#endif
#ifdef USING_ADVANCE_TIMING
	#ifdef USING_FIXED_TIMING
		#error "USING_ADVANCE_TIMING and USING_FIXED_TIMING both options defined, please choose only one!"
	#endif
#endif

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




#endif /* ${include_guard_symbol} */
