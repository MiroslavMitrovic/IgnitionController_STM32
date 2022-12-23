/**
 * @file      IgnitionCtrl_Init.c
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
 *
 *******************************************************************************/
    
#include "IgnitionCotrol_Main.h"

volatile tst_GlobalData GlobalDataValues;

void Data_v_Init(void)
{
	GlobalDataValues.RPM = 0;
	GlobalDataValues.AdvanceAngle = 0;
	GlobalDataValues.CalculationState = en_InitState; 
	GlobalDataValues.SynchronizationStatus = 0;
	GlobalDataValues.Microseconds = 0;
    GlobalDataValues.FiringState = en_FiringStateInit;
    GlobalDataValues.FiringTimeCyl_1 = 0;
    GlobalDataValues.FiringTimeCyl_2 = 0;
    GlobalDataValues.TimeElapsedSinceDetection = 0;
    GlobalDataValues.isCylinder1CoilCharging = false;
    GlobalDataValues.isCylinder2CoilCharging = false;
    
}


void IgnitionCtrl_v_Init(void)
{
	GPIO_v_Init();
	Clock_v_Init();
	Timer_v_Init();
#ifdef ATMEL_MCU
	sei();
#endif /*ATMEL_MCU*/
	GlobalDataValues.CalculationState = en_InitFinished;
	
	
}


void GPIO_v_Init(void)
{
    HW_GPIO_v_Init();
}
void Clock_v_Init(void)
{
	
}

void Timer_v_Init(void)
{
	HW_Timer_v_Init();
}
