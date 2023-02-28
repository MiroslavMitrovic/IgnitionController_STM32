/*
 *test_IgnitionCotrol_Main.c
 *
 * Created: 26/06/2022 13:36:36
 *  Author: mmitr
 */ 
#include "test_IgnitionCotrol_Main.h"
#include <corecrt_math_defines.h>

tst_GlobalData GlobalDataValues;
uint32_t g_uSCounter = 0;
extern uint32_t g_FirstSensorTimePrevious_us;
extern uint32_t g_FirstSensorTimeCurrent_us;
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
/*Check the states and perform operations accordingly*/
static void IgnitionControl_Handler(void);
/*Check for the first sensor is available, and if it is, it returns the status and 
 sets the time for first sensor*/
static uint8_t IgnitionControl_FirstSensorCheck(void);
/*Check for the second sensor is available, and if it is, it returns the status and 
 sets the time for first sensor*/
static uint8_t IgnitionControl_SecondSensorCheck(void);
/*To check if the sensors are in sync*/
static uint8_t IgntionControl_SyncCheck(void);

inline uint32_t CalculateMicroseconds(uint32_t MicrosecondsTicks)
{
	return MicrosecondsTicks << 8; //Frequency is set @ 8MHz and prescaler is 256.
}

void IgnitionControl_Main(void)
{
    uint8_t l_Result = E_OK;
    GlobalDataValues.Microseconds = CalculateMicroseconds(g_uSCounter);
    IgnitionControl_Handler();
	
    
}
static uint8_t IgnitionControl_FirstSensorCheck(void)
{
    uint8_t l_status = E_NOK; 
    
    if( (PIN_SET == PIN_CHECK(PINB, MASK_PB_3_PIN_SET, PINB3) && ( g_SignalFlag == 0 ) ) )
	{
		g_FirstSensorTime_us = CalculateMicroseconds(g_uSCounter);
        l_status = E_OK; 
        g_SignalFlag |=  1 << SENSOR_1_AVAILABLE;
        g_SyncFlag |= 1 << SENSOR_1_AVAILABLE;
        g_SensorActivationCounter++; //counter to measure how many times Signal occured
        if(g_SignalState == 0)
        {
            g_FirstSensorTimePrevious_us = g_FirstSensorTime_us;
            g_SignalState = 1;
        }
        else if (g_SignalState == 1)
        {
                g_FirstSensorTimeCurrent_us = g_FirstSensorTime_us;
                g_SignalState = 2;
           
        }
        
       
	}
    else
    {  }
    if(PIN_RESET == PIN_CHECK(PINB, MASK_PB_3_PIN_SET, PINB3) )
	{
	    //To clear a BIT to have status when it is OFF 
        l_status = E_OK; 
        g_SignalFlag &=  ~(1 << SENSOR_1_AVAILABLE);
	}
    else
    {  }
  return l_status;
}


static uint8_t IgnitionControl_SecondSensorCheck(void)
{
    uint8_t l_status = E_NOK; 
    
    if(PIN_SET == PIN_CHECK(PINB, MASK_PB_4_PIN_SET, PINB4) )
	{
		g_SecondSensorTime_us = CalculateMicroseconds(g_uSCounter);
        l_status = E_OK; 
        g_SyncFlag |=  1 << SENSOR_2_AVAILABLE;
	}
    else
    {
        
    }
  return l_status;
}

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

static void IgnitionControl_Handler(void)
{
      uint8_t l_Result = E_OK;
    
    switch(GlobalDataValues.IgnitionControlState)
    {
        case en_InitFinished:
        GlobalDataValues.Microseconds = CalculateMicroseconds(g_uSCounter);
        GlobalDataValues.IgnitionControlState = en_SynchronizationOngoing;
        break;
        case    en_SynchronizationOngoing:
        //GlobalDataValues.Microseconds = CalculateMicroseconds(g_uSCounter);
        l_Result = IgnitionControl_FirstSensorCheck();
        l_Result = IgntionControl_SyncCheck();
        if( IN_SYNC == GlobalDataValues.IsSynchronised)
        {
             GlobalDataValues.IgnitionControlState = en_Synchronized;
        }
        else
        {
            //do nothing
        }
             break;
        case en_Synchronized:
       //  l_Result = IgnitionControl_FirstSensorCheck();
         GlobalDataValues.RPM = CalculateRPM();
         GlobalDataValues.IgnitionControlState = en_CalculationOngoing;
            break;
        case en_CalculationOngoing:
            break;
        case en_CalculationFinished:
           break;
        case en_FiringCylinder1:
            break;
        case en_FiringCylinder2:
            break;
        case en_IdleState:
             GlobalDataValues.IgnitionControlState = en_SynchronizationOngoing;
            break;
        default: 
            break; 
                   
    }
    
}

extern uint16_t CalculateRPM(void)
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
 }

 return      l_CalculatedRPM;

}