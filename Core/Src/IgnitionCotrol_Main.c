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
extern UART_HandleTypeDef huart2;
extern volatile uint32_t g_usSinceDetectionCyl1;
uint32_t g_FirstSensorTimePrevious_us = 0;
uint32_t g_FirstSensorTimeCurrent_us = 0;
uint32_t g_SensorActivationCounter = 0;
uint32_t g_LostSyncCounter = 0;
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

static uint8_t g_CrankingFiringFlag = 0;
static double l_PrevTimeDifference_us = 0.0;
/*Handler for Calculation States*/
static void Calculation_v_Handler(void);
/*Handler for Firing States*/
static  void Firing_v_Handler(void);
/*Check for the first sensor is available, and if it is, it returns the status and 
 sets the time for first sensor*/
static uint8_t IgnitionControl_FirstSensorCheck(void);

/*Check for the second sensor is available, and if it is, it returns the status and 
 sets the time for first sensor*/
//static uint8_t IgnitionControl_SecondSensorCheck(void);
/*To check if the sensors are in sync*/
static uint8_t IgntionControl_SyncCheck(void);

/* returns calculated rate of change of in value*/
static uint32_t CalculateRate_u_OfChange(uint32_t *in_prevValue, uint32_t in_currValue )
{
    double l_DeltaTimeDifference_us = 0.0;
    l_DeltaTimeDifference_us = (in_currValue - *(in_prevValue) ) / 1.0;
    *in_prevValue = in_currValue;

    return in_currValue +=(uint32_t)l_DeltaTimeDifference_us;

}

uint32_t Calculate_u_Microseconds(uint32_t MicrosecondsTicks)
{
	return MicrosecondsTicks * 10; //Frequency is set @ 84MHz and prescaler is 10. Counter is 10->10uS per tick.
}

void IgnitionControl_v_Main(void)
{


    HAL_NVIC_DisableIRQ(EXTI4_IRQn);
	Firing_v_Handler();
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
     // HAL_GPIO_TogglePin(TestLED1_GPIO_Port,TestLED1_Pin);
    HAL_NVIC_DisableIRQ(EXTI4_IRQn);
    Calculation_v_Handler();
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);

    // HAL_GPIO_TogglePin(TestLED1_GPIO_Port,TestLED1_Pin);
}
#ifdef SENSOR_POLLING_MODE
static uint8_t IgnitionControl_FirstSensorCheck(void)
{
	uint8_t l_status = E_NOK;
	static uint8_t l_isSignalToggled = 0;

	if(0 == l_isSignalToggled)
	{
		if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Signal_1_GPIO_Port, Signal_1_Pin) )
		{
			//signal debouncing time 256uS times the debounce multiplier value
			if(SIGNAL_DEBOUNCE_MULTIPLIER < g_uSDebouncingSignalCounter)
			{
				g_uSDebouncingSignalCounter = 0;
				if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Signal_1_GPIO_Port, Signal_1_Pin) )
				{
					l_isSignalToggled = 1;
					//removed since sensor readout is used as RPM reference, not as firing angle signal
					//g_usSinceDetection = 0; //reset to zero to start calculating time to first cylinder firing
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
					else if(g_SignalState == 1)
					{
						g_FirstSensorTimeCurrent_us = g_FirstSensorTime_us;
						g_SignalState = 2;
					}

				}
				else{}
			}
			else{}
		}
		else{}
	}
	if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(Signal_1_GPIO_Port, Signal_1_Pin))
	{
		//To clear a BIT to have status when it is OFF
		l_isSignalToggled = 0;
		l_status = E_OK;
		g_SignalFlag &=  ~(1 << SENSOR_1_AVAILABLE);
	}
	else{}

	return l_status;
}
#endif /* SENSOR_POLLING_MODE */

extern void IgnitionControl_v_UpdateSignalTime(void)
{
	g_FirstSensorTime_us = Calculate_u_Microseconds(g_uSCounter);
	g_SignalFlag |=  1 << SENSOR_1_AVAILABLE;
	g_SyncFlag |= 1 << SENSOR_1_AVAILABLE;
	g_SensorActivationCounter++; //counter to measure how many times Signal occurred
    g_usSinceDetectionCyl1 = 0; // start time since detection of Signal
    GlobalDataValues.FiringState = en_FiringStateInactive; // reset the firing state for reseting the cranking firing.
    GlobalDataValues.isCylinder1CoilCharging = false;
    /* Check if the ignition coil is still active due to firing timer reset
     between activations at cranking RPM due to incosistent RPMS during cranking, 
     and if it so pin will go to reset to avoid damage to ignition coil. */
     if(true == HW_FiringPin_v_Cylinder_1_Status_Read())
     {
        HW_FiringPin_v_Cylinder_1_Reset();
     }

}
extern uint8_t IgnitionControl_u_FirstSensorCheck_IT(void)
{
    static uint32_t l_g_SensorActivationCounter = 0U;

    /* Initial fetch of time at sensor first pulse */
	if ( (0U == g_SignalState)  && (1U == g_SensorActivationCounter) )
	{
		g_FirstSensorTimePrevious_us = g_FirstSensorTime_us;
		g_SignalState = 1U;
	}
    /* fetch of time at sensor second and future pulses */
	else if ( (g_SignalState == 1U) && (1U < g_SensorActivationCounter) && (l_g_SensorActivationCounter < g_SensorActivationCounter))
	{
		g_FirstSensorTimeCurrent_us = g_FirstSensorTime_us;
		g_SignalState = 2U;
        l_g_SensorActivationCounter = g_SensorActivationCounter;

	}


	return 0U;

}


uint8_t IgntionControl_SyncCheck(void)
{
     uint8_t l_status = E_OK; 
     
     if( g_SyncFlag == (1 << SENSOR_1_AVAILABLE) )
     {
         g_SyncFlag = 0; //Clear the flag 
         l_status = E_OK;
         /*Sensor Activated 2 times */
         if( (2U <= g_SensorActivationCounter) && (g_FirstSensorTimePrevious_us != g_FirstSensorTimeCurrent_us) )
         {
              GlobalDataValues.SynchronizationStatus = IN_SYNC;
         }
         else
         {
             //do nothing
         }
     }
     else if( !(g_SyncFlag == (1 << SENSOR_1_AVAILABLE)) && (GlobalDataValues.SynchronizationStatus != OUT_OF_SYNC))
     {
         GlobalDataValues.SynchronizationStatus = OUT_OF_SYNC;
         g_LostSyncCounter++;
         l_status = E_NOK;
     }
     else 
     {
        // do nothing
     }
     return l_status; 
}
/* Data array for debug purposes */
volatile uint8_t g_LoggingGlobalDataArray[12] = {0};
static void Calculation_v_Handler(void)
{
    uint8_t l_Result = 0; 
    const uint16_t OneRevolutionAngleInDeg = 360; 
    const uint16_t SecondCylinderAngleinDeg = 90;
    volatile static uint32_t OneRevolutionTimeCylinder1 = 0;
    volatile static uint32_t OneRevolutionTimeCylinder2 = 0;
    volatile uint8_t AdvanceAngleCalculatedTime = 0;
    static uint8_t l_previousStateHandler = 0;
    /* Debug data output to uart */
    /*   
    memcpy(&g_LoggingGlobalDataArray[0],&GlobalDataValues.RPM,2U);
    memcpy(&g_LoggingGlobalDataArray[2],&GlobalDataValues.CalculationState,1U);
    memcpy(&g_LoggingGlobalDataArray[3],&GlobalDataValues.FiringState,1U);
    memcpy(&g_LoggingGlobalDataArray[4],&GlobalDataValues.TimeElapsedSinceDetection,4U);
    memcpy(&g_LoggingGlobalDataArray[8],&GlobalDataValues.FiringTimeCyl_1,4U);
    
    HAL_UART_Transmit(&huart2,g_LoggingGlobalDataArray,12U,10);
    HAL_UART_Transmit(&huart2,"\r\n",2U,10);  
    memset(g_LoggingGlobalDataArray,0U,12U); */

    GlobalDataValues.Microseconds = Calculate_u_Microseconds(g_uSCounter);

    switch(GlobalDataValues.CalculationState)
    {
        case en_InitFinished:
        GlobalDataValues.CalculationState = en_SynchronizationOngoing;
        break;
        case    en_SynchronizationOngoing:
#ifdef SENSOR_INTERRUPT_MODE

        	IgnitionControl_u_FirstSensorCheck_IT();
#else
        	l_Result = IgnitionControl_FirstSensorCheck();
#endif /*STM_INTERRUPT*/
        	l_Result = IgntionControl_SyncCheck();
        if( IN_SYNC == GlobalDataValues.SynchronizationStatus)
        {
             GlobalDataValues.CalculationState = en_Synchronized;

        }
        else
        {            //do nothing
        }
        break;

        case en_Synchronized:
    #ifdef SENSOR_INTERRUPT_MODE
                IgnitionControl_u_FirstSensorCheck_IT(); //OK
    #else
                l_Result = IgnitionControl_FirstSensorCheck();
    #endif /*STM_INTERRUPT*/

        // Again check for uS values to get latest value for the check below
         GlobalDataValues.Microseconds = Calculate_u_Microseconds(g_uSCounter);
      	//If more than 2 Seconds have passed, disable the signal and set status to out of sync
         if( (MAX_TIME_FOR_SIGNAL_AVAILABILITY <= (GlobalDataValues.Microseconds - g_FirstSensorTimeCurrent_us)) )
     	{
     		g_SignalFlag &= ~(1 << SENSOR_1_AVAILABLE) ;
     		g_SyncFlag &= ~(1 << SENSOR_1_AVAILABLE) ;
     		GlobalDataValues.SynchronizationStatus = OUT_OF_SYNC;
     		GlobalDataValues.Microseconds = 0; //reset Microseconds counter to start from beginning to count the difference
     		GlobalDataValues.RPM = 0;
     		g_FirstSensorTimeCurrent_us = 0;
     		g_FirstSensorTimePrevious_us = 0;
     		g_uSCounter = 0;
            g_LostSyncCounter++;
     	}

         if(g_FirstSensorTimeCurrent_us != g_FirstSensorTimePrevious_us)
        {
   
            GlobalDataValues.RPM = Calculate_u_RPM();
            /* TODO: Add calculated rate of change of RPM with corresponding filtering until a good balance is achieved...*/
            if( (CRANKING_RPM >= GlobalDataValues.RPM) && (GlobalDataValues.RPM > 30U) ) 
            {
                GlobalDataValues.CalculationState = en_EngineCranking;
             
            }
            /* RPM Limiter will be implemented as a hard limiter, so if the RPMs are over 
            from setpoint, firing event will be skipped. */
            else if (MAX_RPM <  GlobalDataValues.RPM )
            {
                GlobalDataValues.CalculationState = en_Synchronized;
                GlobalDataValues.FiringState = en_RPMHardLimitState;
            }
           
        }
         
        else if( OUT_OF_SYNC == GlobalDataValues.SynchronizationStatus)
        {
            GlobalDataValues.CalculationState = en_SynchronizationOngoing;
        }

        else if (CRANKING_RPM <  GlobalDataValues.RPM )
        {
            /* Handling for case  of one cycle after higher rpm then cranking */
            if( 1U == g_CrankingFiringFlag )
            {
                GlobalDataValues.CalculationState = en_EngineCranking; 
                g_CrankingFiringFlag = 0U;               
            }
            else if (  0U == g_CrankingFiringFlag )
            {
                GlobalDataValues.CalculationState = en_CalculationOngoing;

                
            }

          
        }
        break;

        case en_CalculationOngoing:
            // 1. Get the Advance angle
#ifdef USING_ADVANCE_TIMING
        	GlobalDataValues.AdvanceAngle = get_u_AdvanceAngle(GlobalDataValues.RPM);
            AdvanceAngleCalculatedTime =  CalculateTime_u_FromAngle(GlobalDataValues.RPM, GlobalDataValues.AdvanceAngle);
#endif /*USING_ADVANCE_TIMING*/
#ifdef  USING_FIXED_TIMING
        	GlobalDataValues.AdvanceAngle = FIXED_TIMING_ANGLE;
            AdvanceAngleCalculatedTime =  CalculateTime_u_FromAngle(GlobalDataValues.RPM, GlobalDataValues.AdvanceAngle);
#endif /*USING_FIXED_TIMING*/

           OneRevolutionTimeCylinder1 =  CalculateTime_u_FromAngle(GlobalDataValues.RPM, OneRevolutionAngleInDeg - IGNITION_STATIC_ADVANCE_ANGLE);
           OneRevolutionTimeCylinder2 = CalculateTime_u_FromAngle(GlobalDataValues.RPM, (OneRevolutionAngleInDeg + SecondCylinderAngleinDeg) );
           // 2. Calculate Firing time Cyl-1
           GlobalDataValues.FiringTimeCyl_1 = Calculate_u_FiringTimeCylinder(AdvanceAngleCalculatedTime, OneRevolutionTimeCylinder1);
           /* 2.1  Rate of change of Firing time - to be seen if it is beneficial */
           GlobalDataValues.FiringTimeCyl_1 = CalculateRate_u_OfChange(&l_PrevTimeDifference_us, GlobalDataValues.FiringTimeCyl_1);
            // 3. Calculate Firing time Cyl-2
            GlobalDataValues.FiringTimeCyl_2 = Calculate_u_FiringTimeCylinder(AdvanceAngleCalculatedTime, OneRevolutionTimeCylinder2 );
            // 4. set state to en_CalculationFinished

            if( (0 < GlobalDataValues.FiringTimeCyl_1) && (0 < GlobalDataValues.FiringTimeCyl_2))
            {
            GlobalDataValues.CalculationState = en_CalculationFinished;
            }

            break;
        case en_CalculationFinished:
        	 GlobalDataValues.CalculationState = en_Synchronized;
        	 GlobalDataValues.FiringState = en_FiringCylinder1;
            break;
        case en_IdleStateCalculation:
            //do nothing 
            break;
        case en_EngineCranking:

            GlobalDataValues.CalculationState = en_Synchronized;
            /* Check if firing was executed already and don't set state to firing until the next cycle. */
            /* TODO: Check if this affect the triggering of multiple Cranking events after first trigger */
            if( ! (GlobalDataValues.FiringState == en_IdleStateFiringState) )
            {
                GlobalDataValues.FiringState = en_FiringCylinder1Cranking;
            }
            
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
   
	 GlobalDataValues.TimeElapsedSinceDetection = g_usSinceDetectionCyl1 * 10;

        switch(GlobalDataValues.FiringState)
        {
            case en_FiringCylinder1:
                Firing_v_Cylinder1();
            break;
            case en_FiringCylinder1Completed:
            GlobalDataValues.FiringState = en_IdleStateFiringState;
            
//TODO: Implement firing and handling for Cylinder2.
            break;
            case en_FiringCylinder2:
                 Firing_v_Cylinder2();
            break;
            case en_FiringCylinder2Completed:
                GlobalDataValues.FiringState = en_IdleStateFiringState;
                
               
            break;

            case en_FiringCylinder1Cranking:
            g_CrankingFiringFlag = 1U;
            Firing_v_Cylinder1Cranking();
            break;
            case en_RPMHardLimitState:
            GlobalDataValues.FiringState = en_IdleStateFiringState;
            break;
            case en_IdleStateFiringState:
               // do nothing
            break;
            default:
             // should not be reached.
            break;
        }
   
}



extern uint16_t Calculate_u_RPM(void)
{
    uint16_t l_CalculatedRPM = 0;
    const double alpha = 8.0;
    volatile double l_TimeDifference_us = 0.0;
    volatile double l_TimeDifference_ms = 0.0;
    volatile  double l_AngularVelocity = 0.0; 
    volatile double l_DeltaTimeDifference_us = 0.0;
 l_TimeDifference_us = (g_FirstSensorTimeCurrent_us - g_FirstSensorTimePrevious_us);
 //l_DeltaTimeDifference_us = alpha * (l_TimeDifference_us - l_PrevTimeDifference_us);
 //l_PrevTimeDifference_us = l_TimeDifference_us;
 /* Calculated rate of change */
// l_TimeDifference_us += l_DeltaTimeDifference_us;
 l_TimeDifference_ms = l_TimeDifference_us / 1000.0f; 
 l_AngularVelocity = (2.0 * M_PI * 1000.0) /(l_TimeDifference_ms ); //[rad/S]
 l_CalculatedRPM = (uint16_t) (l_AngularVelocity * 30.0f / M_PI); 
// Linear fltering - not good try with moving average if the rate of change is not functioning as it should be....
//l_CalculatedRPM =  (uint16_t) (alpha * l_CalculatedRPM  + (1.0 - alpha) * GlobalDataValues.RPM);


 /*Case when the RPM signal is already known, so we need just to update currentTime*/
 if( 2 == g_SignalState )
 {
    g_FirstSensorTimePrevious_us = g_FirstSensorTimeCurrent_us;
    g_SignalState = 1;
 }
 else{}


#ifdef USING_CRANK_SIGNAL
 return      l_CalculatedRPM;
#endif/*USING_CRANK_SIGNAL*/
#ifdef USING_CAM_SIGNAL
 return      l_CalculatedRPM * 2 ;
#endif/*USING_CAM_SIGNAL*/
}


