/**
 * @file      IgnitionCtrl_CalculateTimesAndAngles.c
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

extern volatile uint32_t g_usSinceDetectionCyl1;
extern uint8_t g_CrankingFiringFlag;
/*Global constant for RPM and ignition angle*/
const uint16_t g_cIgnitionAngleTable [IGNITION_ANGLE_TABLE_COLUMNS] [IGNITION_ANGLE_TABLE_ROWS] =
{   {0, 1000, 2000, 3000, 4000,  5000, 6000, 7000,  8000,  9000 },
    {0, 0,    8,    20,   28,    32,   31,   30,    29,    28   }
};

 static uint32_t l_errorCounter = 0;
inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


uint8_t get_u_AdvanceAngle(uint16_t in_u8_RPM)
{
 
      /*   Linear model Poly4:
     val(x) = p1*x^4 + p2*x^3 + p3*x^2 + p4*x + p5
       where x is normalized by mean 5225 and std 3002
     Coefficients (with 95% confidence bounds):
        p1 = -8.0306e-18;
        p2 = 2.4472e-13;
        p3 = -2.6638e-09;
        p4 = 1.1505e-05;
        p5 = -0.010326;
        p6 = 0.22854;
*/
	 uint16_t l_RPMMaxValue = 8500;
	 uint16_t l_RPMMinValue = 0; 
     int8_t l_AdvanceAngleInt = 0;
     const uint16_t RPMS_OUT_OF_RANGE = 10000u;
     #ifdef USE_POLY_CALC_IGN_ANGLE
     float l_p1 = -8.0306e-18;
     float l_p2 =  2.4472e-13;;
     float l_p3 = -2.6638e-09;
     float l_p4 = 1.1505e-05;
     float l_p5 = -0.010326; 
     float l_p6 = 0.22854;
     #else 
     /*Perform linear calculations based on y = kx + n up to 4000 RPM, afterwards value can remain the same */
     const float K = 0.0107;
     const float N = -10.07;
     const uint16_t LINEAR_ANGLE_MAX_RPM = 4000u;
     #endif /* USE_POLY_CALC_IGN_ANGLE*/

     // Check for implausability, this setup shouldn't have values more then 10000RPM.
     if (RPMS_OUT_OF_RANGE <= in_u8_RPM)
     {
         in_u8_RPM = 0;
     }
     else if(l_RPMMaxValue <= in_u8_RPM)
     {
         in_u8_RPM = l_RPMMaxValue;
     }
     else if(in_u8_RPM <= l_RPMMinValue)
     {
         in_u8_RPM = l_RPMMinValue;
     }
     else
     {
    	 //Do nothing
     }
    #ifdef USE_POLY_CALC_IGN_ANGLE
     l_AdvanceAngleInt = (int8_t) round( ( ( l_p1 * pow(in_u8_RPM,5) ) + (l_p2 * pow(in_u8_RPM,4))
    		 + (l_p3 * pow(in_u8_RPM,3)) + (l_p4 * pow(in_u8_RPM,2)) + (l_p5 * in_u8_RPM) + l_p6  ));
    #else 
    if( LINEAR_ANGLE_MAX_RPM >= in_u8_RPM)
    {
        l_AdvanceAngleInt = K * in_u8_RPM + N;
    }
    else
    {
        /* Always Calculate the same value as in the case of 4000RPM due to ignition curve  */
        in_u8_RPM = LINEAR_ANGLE_MAX_RPM;
        l_AdvanceAngleInt = K * in_u8_RPM + N;
    }
    #endif /* USE_POLY_CALC_IGN_ANGLE*/

     if (0 > l_AdvanceAngleInt)
     {
    	 l_AdvanceAngleInt = 0;
     }
     else
     {
         //do nothing
     }

	 return (uint8_t)l_AdvanceAngleInt;

#undef LINEAR_ANGLE_MAX_RPM
}

uint32_t CalculateTime_u_FromAngle(uint16_t in_u16_RPM, uint16_t in_u16_Angle)
{
  volatile  float_t l_AngularVelocity = 0;                 //[1/s]
   uint32_t l_TimeFor1DegreeTravel = 0;                    //[uS]
   volatile uint32_t l_CalculatedTime = 0;
  
    
   l_AngularVelocity = in_u16_RPM / 60.0; 
   
   if(0 == in_u16_RPM)
   {
       l_errorCounter++;
   }
   
    l_TimeFor1DegreeTravel =(uint32_t) ((1.0 / l_AngularVelocity /360.0) * 1000000.0);
    
    l_CalculatedTime = l_TimeFor1DegreeTravel * in_u16_Angle; 
    
    return l_CalculatedTime;
}

inline uint32_t Calculate_u_FiringTimeCylinder(uint32_t in_u32_AdvanceAngleTime,  uint32_t in_u32_360degRevolutionTime)
{
    uint32_t l_FiringTimeCylinder = in_u32_360degRevolutionTime - in_u32_AdvanceAngleTime; 
    
    return l_FiringTimeCylinder;
}

void Firing_v_Cylinder1(void)
{
    if( !(GlobalDataValues.FiringState == en_FiringCylinder1Completed) )
    {
        if((GlobalDataValues.TimeElapsedSinceDetectionCylinder1 >= ((GlobalDataValues.FiringTimeCyl_1 - IGNITION_DWELL_TIME_US) )
                && (false == GlobalDataValues.isCylinder1CoilCharging ) ) )
        {
            //Raise Firing Pin to HIGH 
            HW_FiringPin_v_Cylinder_1_Set();
            GlobalDataValues.isCylinder1CoilCharging = true;
        }
        else if ( (GlobalDataValues.TimeElapsedSinceDetectionCylinder1 >= GlobalDataValues.FiringTimeCyl_1) )
        {
            //Set Firing Pin to LOW 
            HW_FiringPin_v_Cylinder_1_Reset();
            GlobalDataValues.isCylinder1CoilCharging = false;
            GlobalDataValues.FiringState = en_FiringCylinder1Completed;
        }
    }
}
  void Firing_v_Cylinder2(void)
  { 
   // static uint8_t l_firingState = 0U;
    if( !(GlobalDataValues.FiringStateCylinder2 == en_FiringCylinder2Completed) )
    {
    
        if( (GlobalDataValues.TimeElapsedSinceDetectionCylinder2 >= (GlobalDataValues.FiringTimeCyl_2 - IGNITION_DWELL_TIME_US) )
                 &&  (false == GlobalDataValues.isCylinder2CoilCharging) )
        {
            //Raise Firing Pin to HIGH 
            HW_FiringPin_v_Cylinder_2_Set();
            GlobalDataValues.isCylinder2CoilCharging = true;          
        }
        else if ((GlobalDataValues.TimeElapsedSinceDetectionCylinder2 >= GlobalDataValues.FiringTimeCyl_2)  )
        {
            //Set Firing Pin to LOW 
            HW_FiringPin_v_Cylinder_2_Reset();
            GlobalDataValues.isCylinder2CoilCharging = false;
            GlobalDataValues.FiringStateCylinder2 = en_FiringCylinder2Completed;
            //l_firingState = 1U;
        }
    }

}

void Firing_v_Cylinder1Cranking(void)
{
    if( !(GlobalDataValues.FiringState == en_FiringCylinder1Completed) )
    {
    
        if((GlobalDataValues.TimeElapsedSinceDetectionCylinder1 > 0U )
                && (false == GlobalDataValues.isCylinder1CoilCharging ) ) 
        {
            //Raise Firing Pin to HIGH 
            HW_FiringPin_v_Cylinder_1_Set();
            GlobalDataValues.isCylinder1CoilCharging = true;
        }
        else if ( (GlobalDataValues.TimeElapsedSinceDetectionCylinder1 >= CRANKING_DWELL_TIME_US) )
        {
            //Set Firing Pin to LOW 
            HW_FiringPin_v_Cylinder_1_Reset();
            GlobalDataValues.isCylinder1CoilCharging = false;
            GlobalDataValues.FiringState = en_FiringCylinder1Completed;
            if(2U == g_CrankingFiringFlag)
            {
                g_CrankingFiringFlag = 3U;
            }
            
        }
    }
}

void Firing_v_Cylinder2Cranking(void)
{
    if( !(GlobalDataValues.FiringStateCylinder2 == en_FiringCylinder2Completed) )
    {
    
        if((GlobalDataValues.TimeElapsedSinceDetectionCylinder2 > 0U )
                && (false == GlobalDataValues.isCylinder2CoilCharging ) ) 
        {
            //Raise Firing Pin to HIGH 
            HW_FiringPin_v_Cylinder_2_Set();
            GlobalDataValues.isCylinder2CoilCharging = true;
        }
        else if ( (GlobalDataValues.TimeElapsedSinceDetectionCylinder2 >= CRANKING_DWELL_TIME_US) )
        {
            //Set Firing Pin to LOW 
            HW_FiringPin_v_Cylinder_2_Reset();
            GlobalDataValues.isCylinder2CoilCharging = false;
            GlobalDataValues.FiringStateCylinder2 = en_FiringCylinder2Completed;
        }
    }
}