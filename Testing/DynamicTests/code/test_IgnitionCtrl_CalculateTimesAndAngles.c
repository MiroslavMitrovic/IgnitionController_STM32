/*
 * test_IgnitionCtrl_CalculateTimesAndAngles.c
 *
 * Created: 25/06/2022 22:00:17
 *  Author: mmitr
 */ 
#include "test_IgnitionCotrol_Main.h"


/*Global constant for RPM and ignition angle*/
const uint16_t g_cIgnitionAngleTable [IGNITION_ANGLE_TABLE_COLUMNS] [IGNITION_ANGLE_TABLE_ROWS] =
{   {0, 1000, 2000, 3000, 4000,  5000, 6000, 7000,  8000,  9000 },
    {0, 0,    8,    20,   28,    32,   31,   30,    29,    28   }
};

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


uint8_t getAdvanceAngle(uint16_t in_u8_RPM)
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
	 float  l_AdvanceAngle = 0;
     int8_t l_AdvanceAngleInt = 0;
     float l_p1 = -8.0306e-18;
     float l_p2 =  2.4472e-13;;
     float l_p3 = -2.6638e-09;
     float l_p4 = 1.1505e-05;
     float l_p5 = -0.010326; 
     float l_p6 = 0.22854;
     // Check for implausability, this setup shouldn't have values more then 10000RPM.
     if (10000 <= in_u8_RPM)
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
     l_AdvanceAngleInt = (int8_t) round( ( ( l_p1 * pow(in_u8_RPM,5) ) + (l_p2 * pow(in_u8_RPM,4))
             + (l_p3 * pow(in_u8_RPM,3)) + (l_p4 * pow(in_u8_RPM,2)) + (l_p5 * in_u8_RPM) + l_p6  ));
     if (0 > l_AdvanceAngleInt)
     {
         l_AdvanceAngleInt = 0;
     }
     else
     {
         //do nothing
     }
/*To be checked what is faster Polynomial calculation or read from memory, investigate Pros and Cons*/	 
/*	 if (!(( in_u8_RPM >= l_RPMMinValue) && ( in_u8_RPM <= l_RPMMaxValue))) //Value range check
	 {
		  while(1); //error WDT will reset the MCU
	 }
	 
	 for(int i =0, j = 1 ; i < IGNITION_ANGLE_TABLE_ROWS; i++ , j++ )
	 {
		 if( (g_cIgnitionAngleTable[0][i] <= in_u8_RPM) && ( in_u8_RPM <= g_cIgnitionAngleTable[0][j] ) && (j <= IGNITION_ANGLE_TABLE_ROWS ) )
		 {
			l_AdvanceAngle =  map(in_u8_RPM, g_cIgnitionAngleTable[0][i], g_cIgnitionAngleTable[0][j],
                    g_cIgnitionAngleTable[1][i], g_cIgnitionAngleTable[1][j] );
         }
         else if( g_cIgnitionAngleTable[0][i] == in_u8_RPM )
         {
             l_AdvanceAngle = g_cIgnitionAngleTable[1][i];
         }
         else
         {
             //This case should not happen, variable put just in case
             l_AdvanceAngle = 0;
         }
	 }
*/
	 return (uint8_t)l_AdvanceAngleInt;
}

uint32_t CalculateTime_u_FromAngle(uint16_t in_u16_RPM, uint16_t in_u16_Angle)
{
    uint16_t l_AngularVelocity = 0;                         //[1/s]
    uint16_t l_TimeFor1DegreeTravel = 0;                    //[uS]
    uint32_t l_CalculatedTime = 0;

    l_AngularVelocity = in_u16_RPM / 60; 
    
    l_TimeFor1DegreeTravel =(uint16_t) ((1.0 / l_AngularVelocity /360.0) * 1000000.0);
    
    l_CalculatedTime = l_TimeFor1DegreeTravel * in_u16_Angle; 
    
    return l_CalculatedTime;
}

inline uint32_t Calculate_u_FiringTimeCylinder1(uint32_t in_u32_AdvanceAngleTime,  uint32_t in_u32_Time)
{
    uint32_t l_FiringTimeCylinder1 = in_u32_Time - in_u32_AdvanceAngleTime; 
    
    return l_FiringTimeCylinder1;
}

