/*
 * @file      test_IgnitionCtrl_Config.h
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
#ifndef TEST_IGNITIONCTRL_CONFIG_H
#define TEST_IGNITIONCTRL_CONFIG_H

#define F_CPU                        8000000UL           ///< 8MHz
/*******************************************************************************
 * Includes
 *******************************************************************************/
#ifdef __UNIT_TESTING__
#include <avr/delay.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <xc.h>
#endif /*__UNIT_TESTING__*/
#include <stdio.h>
#include <stdint.h>
/*******************************************************************************
 * Defines
 *******************************************************************************/

#define IGNITION_ANGLE_TABLE_COLUMNS 2U
#define IGNITION_ANGLE_TABLE_ROWS	 10U
#define IGNITION_DWELL_TIME_US       2500U                ///< Ignition coil dwell time in uS
#define IS_ENGINE_ODD_FIRE

/*Macro check is engine even or odd firing*/
#ifdef IS_ENGINE_ODD_FIRE
#define ODD_FIRE_ANGLE_IN_DEG        225U                ///< Engine Fire Angle in degrees           
#else
#define EVEN_FIRE_ANGLE_IN_DEG       180U                ///< Even Fire distribution
#endif
/*Status defines*/
#define E_OK    0U
#define E_NOK   1U 
#define E_BUSY  2U 

/*Definitions for Sensor Availability flag*/
#define SENSOR_1_AVAILABLE 0U
#define SENSOR_2_AVAILABLE 1U


#define IN_SYNC            1U
#define OUT_OF_SYNC        0U
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




#endif /* TEST_IGNITIONCTRL_CONFIG_H */
