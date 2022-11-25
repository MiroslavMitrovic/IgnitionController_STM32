/**
 * @file      IgnitionCtrl_CalculateTimesAndAngles.h
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


#ifndef IGNITIONCTRL_CALCULATETIMESANDANGLES_H_
#define IGNITIONCTRL_CALCULATETIMESANDANGLES_H_
#include "IgnitionCotrol_Main.h"
/** @brief Function that will perform the calculation of Time based on RPMs and given Angle\n
 *  @param  [in] in_u16_RPM
 *  @param  [in] in_u16_Angle
 *  @return Angle value
 */
uint32_t CalculateTime_u_FromAngle(uint16_t in_u16_RPM, uint16_t in_u16_Angle);
/** @brief Function that will perform the calculation of Angle based on RPMs and given Time\n
 *  @param  [in] in_u16_RPM
 *  @param  [in] in_u32_Time
 *  @return Angle value
 */
uint16_t CalculateAngle_u_FromTime(uint16_t in_u16_RPM, uint32_t in_u32_Time);
/** @brief Function that will perform the calculation of RPM based on time between two High Signals\n
 *  @param  [none]
 *  @return RPM value
 */
extern uint16_t Calculate_u_RPM(void);
/** @brief Function that gets the Advance angle value based on RPMs mapped in LUT\n
 *  @param  [in] in_u16_RPM 
 *  @return Advance Angle 
*/ 
uint8_t get_u_AdvanceAngle(uint16_t in_u16_RPM);

long map(long x, long in_min, long in_max, long out_min, long out_max);
/** @brief Function for calculation of ignition firing time\n
 *  Calculation performed by taking time for 360deg f(t) - Advance Angle f(t) 
 *  Signal must be raised to HIGH before this calculated time for the value of IGNITION_DWELL_TIME_US
 *  to charge the ignition coil then to return it to LOW pin state.
 *  Pin HIGH start time -  360deg f(t) - Advance Angle f(t) - IGNITION_DWELL_TIME_US
 *  Pin LOW start time  -  360deg f(t) - Advance Angle f(t)       
 *  @param [in] in_u16_AdvanceAngleTime 
 *  @param [in] in_u32_360degRevolutionTime 
 *  @return FiringTime
 */

 uint32_t Calculate_u_FiringTimeCylinder(uint32_t in_u32_AdvanceAngleTime,  uint32_t in_u32_360degRevolutionTime);
/** @brief Function for Firing Cylinder1\n
 *  Firing will be performed According to the Calculated time - IGNITION_DWELL_TIME_US
 *  Signal must be raised to HIGH before this calculated time for the value of IGNITION_DWELL_TIME_US
 *  to charge the ignition coil then to return it to LOW pin state.
 *  Pin HIGH start time -  360deg f(t) - Advance Angle f(t) - IGNITION_DWELL_TIME_US
 *  Pin LOW start time  -  360deg f(t) - Advance Angle f(t)       
 */
  void Firing_v_Cylinder1(void);
/** @brief Function for Firing Cylinder2\n
 *  Firing will be performed According to the Calculated time - IGNITION_DWELL_TIME_US
 *  Signal must be raised to HIGH before this calculated time for the value of IGNITION_DWELL_TIME_US
 *  to charge the ignition coil then to return it to LOW pin state.
 *  Pin HIGH start time -  360deg + 90deg f(t) - Advance Angle f(t) - IGNITION_DWELL_TIME_US
 *  Pin LOW start time  -  360deg + 90deg f(t) - Advance Angle f(t)       
 */
  void Firing_v_Cylinder2(void);

#endif /* IGNITIONCTRL_CALCULATETIMESANDANGLES_H_ */