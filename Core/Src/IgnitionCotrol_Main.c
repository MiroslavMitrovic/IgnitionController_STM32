/**
 * @file      IgnitionCotrol_Main.c
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

extern volatile uint32_t g_usSinceDetection;
extern volatile uint32_t g_uSDebouncingSignalCounter;
extern tst_GlobalData GlobalDataValues;
uint32_t g_FirstSensorTimePrevious_us = 0;
uint32_t g_FirstSensorTimeCurrent_us = 0;
uint32_t g_SensorActivationCounter = 0;
uint32_t g_FirstSensorTime_us = 0;
uint32_t g_SecondSensorTime_us = 0;
/*Flag with the signal status*/
uint8_t  g_SignalFlag = 0;
/*Signal state Flag*/
uint8_t g_SignalState = 0;
/*Flag with the sync status*/
uint8_t  g_SyncFlag = 0;
/*Flag for check if the sensor Value is already taken*/
uint8_t g_FirstSensorSignalAvailable = false;
/*Handler for Calculation States*/
static void Calculation_v_Handler(void);
/*Handler for Firing States*/
static  void Firing_v_Handler(void);
/*Check for the first sensor is available, and if it is, it returns the status and 
 sets the time for first sensor*/
static uint8_t IgnitionControl_FirstSensorCheck(void);

static uint8_t IgnitionControl_u_FirstSensorCheck_IT(void);
/*Check for the second sensor is available, and if it is, it returns the status and 
 sets the time for first sensor*/
//static uint8_t IgnitionControl_SecondSensorCheck(void);
/*To check if the sensors are in sync*/
static uint8_t IgntionControl_SyncCheck(void);

inline uint32_t Calculate_u_Microseconds(uint32_t MicrosecondsTicks)
{
	return MicrosecondsTicks << 8; //Frequency is set @ 168MHz and prescaler is 168. Counter is 255->256uS per tick.
}

void IgnitionControl_v_Main(void)
{

	if(en_IdleStateCalculation != GlobalDataValues.CalculationState)
	{
	Calculation_v_Handler();
	}
	else
	{
	Firing_v_Handler();
	}
}
static uint8_t IgnitionControl_FirstSensorCheck(void)
{
	uint8_t l_status = E_NOK;
	static uint8_t l_isSignalToggled = 0;

	if(0 == l_isSignalToggled)
	{
		if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Signal_1_GPIO_Port, Signal_1_Pin) )//(PIN_SET == PIN_CHECK(PIN_PINB, MASK_PB_3_PIN_SET, PIN_PINB3) && ( g_SignalFlag == 0 ) ) )
		{

			if(10 < g_uSDebouncingSignalCounter)
			{
				g_uSDebouncingSignalCounter = 0;
				if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Signal_1_GPIO_Port, Signal_1_Pin) )
				{
					l_isSignalToggled = 1;
					g_usSinceDetection = 0; //reset to zero to start calculating time to first cylinder firing
					g_FirstSensorTime_us = Calculate_u_Microseconds(g_uSCounter);
					l_status = E_OK;
					g_SignalFlag |=  1 << SENSOR_1_AVAILABLE;
					g_SyncFlag |= 1 << SENSOR_1_AVAILABLE;
					g_SensorActivationCounter++; //counter to measure how many times Signal occurred

					if(g_SignalState == 0)
					{
						g_FirstSensorTimePrevious_us = g_FirstSensorTime_us;
						g_SignalState = 1;
					}
					else if ( (g_SignalState == 1) /*&& (GPIO_PIN_SET == HAL_GPIO_ReadPin(Signal_1_GPIO_Port, Signal_1_Pin))*/)
					{
						g_FirstSensorTimeCurrent_us = g_FirstSensorTime_us;
						g_SignalState = 2;

					}

				}
				else{}
			}
			else{}
		}
		else
		{

		}
	}
	if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(Signal_1_GPIO_Port, Signal_1_Pin)) //PIN_RESET == PIN_CHECK(PIN_PINB, MASK_PB_3_PIN_SET, PIN_PINB3) )
	{
		//To clear a BIT to have status when it is OFF

		l_isSignalToggled = 0;
		l_status = E_OK;
		g_SignalFlag &=  ~(1 << SENSOR_1_AVAILABLE);
	}
	else
	{  }
	return l_status;
}

static uint8_t IgnitionControl_u_FirstSensorCheck_IT(void)
{
	/*
	 * 1. Update the current time
	 * 2. Update the previous time
	 * 3. Update the sync data
	 * 4. Reset the firing time
	 *
	 * */

}

//static uint8_t IgnitionControl_SecondSensorCheck(void)
//{
//    uint8_t l_status = E_NOK;
//
//    if(PIN_SET == PIN_CHECK(PINB, MASK_PB_4_PIN_SET, PINB4) )
//	{
//		g_SecondSensorTime_us = Calculate_u_Microseconds(g_uSCounter);
//        l_status = E_OK;
//        g_SyncFlag |=  1 << SENSOR_2_AVAILABLE;
//	}
//    else
//    {
//
//    }
//  return l_status;
//}

uint8_t IgntionControl_SyncCheck(void)
{
     uint8_t l_status = E_OK; 
     
     if( g_SyncFlag == (1 << SENSOR_1_AVAILABLE) )
     {
         g_SyncFlag = 0; //Clear the flag 
         l_status = E_OK;
         /*Sensor Activated 2 times */
         if( (g_SensorActivationCounter >= 2) && (g_FirstSensorTimePrevious_us != g_FirstSensorTimeCurrent_us) )
         {
              GlobalDataValues.IsSynchronised = IN_SYNC;
         }
         else
         {
             //do nothing
         }
     }
     else
     {
         GlobalDataValues.IsSynchronised = OUT_OF_SYNC;
         l_status = E_NOK;
     }
     return l_status; 
    
}

static void Calculation_v_Handler(void)
{
    uint8_t l_Result = 0; 
    const uint16_t OneRevolutionAngleInDeg = 360; 
    const uint16_t SecondCylinderAngleinDeg = 90;
    volatile static uint32_t OneRevolutionTimeCylinder1 = 0;
    volatile static uint32_t OneRevolutionTimeCylinder2 = 0;
    static volatile uint8_t FirstCalculationFlag = 0;

    
    switch(GlobalDataValues.CalculationState)
    {
        case en_InitFinished:
        GlobalDataValues.CalculationState = en_SynchronizationOngoing;
        break;
        case    en_SynchronizationOngoing:
        //GlobalDataValues.Microseconds = CalculateMicroseconds(g_uSCounter);
        l_Result = IgnitionControl_FirstSensorCheck();
        l_Result = IgntionControl_SyncCheck();
        if( IN_SYNC == GlobalDataValues.IsSynchronised)
        {
             GlobalDataValues.CalculationState = en_Synchronized;
          //   g_usSinceDetection = 0; //reset to zero to start calculating time to first cylinder firing
        }
        else
        {

            ///
        }
        break; //remove breaks to try to save execution time
        case en_Synchronized:
         l_Result = IgnitionControl_FirstSensorCheck();
         if(g_FirstSensorTimeCurrent_us != g_FirstSensorTimePrevious_us)
         {
         GlobalDataValues.RPM = Calculate_u_RPM();
         }
         if(30 <  GlobalDataValues.RPM )
         {
         GlobalDataValues.CalculationState = en_CalculationOngoing;
         }
         break; //remove breaks to try to save execution time
        case en_CalculationOngoing:
            // 1. Get the Advance angle
            GlobalDataValues.AdvanceAngle = get_u_AdvanceAngle(GlobalDataValues.RPM);
            // 2. Calculate Firing time Cyl-1
           OneRevolutionTimeCylinder1 =  CalculateTime_u_FromAngle(GlobalDataValues.RPM, OneRevolutionAngleInDeg );
           OneRevolutionTimeCylinder2 = CalculateTime_u_FromAngle(GlobalDataValues.RPM, (OneRevolutionAngleInDeg + SecondCylinderAngleinDeg) );
           GlobalDataValues.FiringTimeCyl_1 = Calculate_u_FiringTimeCylinder(0, OneRevolutionTimeCylinder1);
            // 3. Calculate Firing time Cyl-2
            GlobalDataValues.FiringTimeCyl_2 = Calculate_u_FiringTimeCylinder(0, OneRevolutionTimeCylinder2 );
            // 4. set state to en_CalculationFinished
            if( (0 <= GlobalDataValues.FiringTimeCyl_1) && (0 <= GlobalDataValues.FiringTimeCyl_2))
            {
            GlobalDataValues.CalculationState = en_CalculationFinished;
            }
            break;
        case en_CalculationFinished:
//            if( (0 == GlobalDataValues.FiringTimeCyl_1) ||(0 == GlobalDataValues.FiringTimeCyl_2))
//            {
//                GlobalDataValues.CalculationState = en_Synchronized; //calculate again
//            }
             if((GlobalDataValues.FiringState == en_IdleStateFiring) || ( 0 == FirstCalculationFlag) ) //first time trigger or firing finished
            {
                FirstCalculationFlag = 1;
                GlobalDataValues.FiringState = en_FiringCylinder1;
                GlobalDataValues.CalculationState = en_IdleStateCalculation;
            }
            else
            {
                            
            }
                          //  GlobalDataValues.CalculationState = en_Synchronized;
            //             GlobalDataValues.CalculationState = en_SynchronizationOngoing;
          //do nothing
            break;
        case en_IdleStateCalculation:
            //do nothing 
            //GlobalDataValues.CalculationState = en_SynchronizationOngoing;
            break;
        default: 
            // should not be reached.
            break; 
                   
    }
    
}

static void Firing_v_Handler(void)
{
  
  /*NOTE: PROVE at integration test level if no race condition will occur during
    firing of both cylinders due to faulty handling in FSM or time overlaps
    Additional idea, put both handlers inside of 1 case en_FiringCylinders...*/
   
       GlobalDataValues.TimeElapsedSinceDetection = g_usSinceDetection << 8;

        switch(GlobalDataValues.FiringState)
        {
            case en_FiringCylinder1:
               Firing_v_Cylinder1();
           break;  //remove breaks for runtime improvement
            case en_FiringCylinder1Completed:
                GlobalDataValues.FiringState = en_IdleStateFiring;
               // GlobalDataValues.FiringState = en_FiringCylinder2;
            break;
            case en_FiringCylinder2:
                 Firing_v_Cylinder2();
            break;
            case en_FiringCylinder2Completed:
                GlobalDataValues.FiringState = en_IdleStateFiring;
                
               
            break;
            case en_IdleStateFiring:
            	  GlobalDataValues.CalculationState = en_Synchronized;
            
                // do nothing
            break;
            default:
             // should not be reached.
            break;
        }
   
}



extern uint16_t Calculate_u_RPM(void)
{
    uint32_t l_TimeDifference_us = 0;
    uint32_t l_TimeDifference_ms = 0;
    float l_AngularVelocity = 0.0; 
    uint16_t l_CalculatedRPM = 0;
    
 l_TimeDifference_us = g_FirstSensorTimeCurrent_us - g_FirstSensorTimePrevious_us;
 l_TimeDifference_ms = l_TimeDifference_us / 1000; 
 l_AngularVelocity = (2 * M_PI * 1000) /(l_TimeDifference_ms ); //[rad/S]
 l_CalculatedRPM = (uint16_t) (l_AngularVelocity * 30.0 / M_PI); 
 
 /*Case when the RPM signal is already known, so we need just to update currentTime*/
 if( 2 == g_SignalState )
 {
    g_FirstSensorTimePrevious_us = g_FirstSensorTimeCurrent_us;
    g_SignalState = 1;
 }

 return      l_CalculatedRPM;

}


