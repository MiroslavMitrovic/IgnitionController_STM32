/*
 * IgnitionCtrl_CalculateTimesAndAngles.h
 *
 * Created: 25/06/2022 22:00:32
 *  Author: mmitr
 */ 


#ifndef TEST_IGNITIONCTRL_CALCULATETIMESANDANGLES_H_
#define TEST_IGNITIONCTRL_CALCULATETIMESANDANGLES_H_
#include "test_IgnitionCotrol_Main.h"
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
extern uint16_t CalculateRPM(void);
/** @brief Function that gets the Advance angle value based on RPMs mapped in LUT\n
 *  @param  [in] in_u16_RPM 
 *  @return Advance Angle 
*/ 
uint8_t getAdvanceAngle(uint16_t in_u16_RPM);

long map(long x, long in_min, long in_max, long out_min, long out_max);
/** @brief Function for calculation of ignition firing angle\n
 *  Calculation performed by taking time for 360deg f(t) - Advance Angle f(t) - IGNITION_DWELL_TIME_US
 *  Signal must be raised to HIGH before this calculated time for the value of IGNITION_DWELL_TIME_US
 *  to charge the ignition coil then to return it to LOW pin state.
 *  Pin HIGH start time -  360deg f(t) - Advance Angle f(t) - IGNITION_DWELL_TIME_US
 *  Pin LOW start time  -  360deg f(t) - Advance Angle f(t)       
 *  @param [in] in_u16_AdvanceAngleTime 
 *  @param [in] in_u32_Time 
 *  @return FiringTime
 */
// <editor-fold defaultstate="collapsed" desc="comment">
inline// </editor-fold>
 uint32_t Calculate_u_FiringTimeCylinder1(uint32_t in_u32_AdvanceAngleTime,  uint32_t in_u32_Time);



#endif /* IGNITIONCTRL_CALCULATETIMESANDANGLES_H_ */