#include <gtest/gtest.h>
#include "test_IgnitionCotrol_Main.h"
#include "test_IgnitionCotrol_Main.c"
#include "test_IgnitionCtrl_CalculateTimesAndAngles.h"
#include "test_IgnitionCtrl_CalculateTimesAndAngles.c"


	/*Creation of test*/
	uint32_t g_FirstSensorTimeCurrent_us = 1000000; //1 Second Time
	uint32_t g_FirstSensorTimePrevious_us = 0;
	TEST(IgnitionControl_MainSuite, CalculateMicroseconds)
	{
		uint32_t TicksToBeRecalculated = 5;
		uint32_t expectedMicroSeconds = TicksToBeRecalculated << 8;

		EXPECT_EQ(expectedMicroSeconds, CalculateMicroseconds(TicksToBeRecalculated));

	}

	TEST(IgnitionControl_MainSuite, CalculateRPM)
	{

		uint16_t expectedRPM = 60;						//1 Round per second is 60 Rounds per minute
		//EXPECT_EQ(expectedRPM, CalculateRPM());
		EXPECT_EQ(1,2);
	}
	TEST(IgnitionControl_CalculateTimesAndAnglesSuite, GetIgnitionAngle)
	{

		uint16_t inputRPM1 = 5800;
		uint16_t expectedAdvanceAngle1 = 32;
		uint16_t inputRPM2 = 9500;
		uint16_t expectedAdvanceAngle2 = 29;
		int16_t  inputRPM3 = -100;
		uint16_t expectedAdvanceAngle3 = 0;
		EXPECT_EQ(expectedAdvanceAngle1, getAdvanceAngle(inputRPM1));
		EXPECT_EQ(expectedAdvanceAngle2, getAdvanceAngle(inputRPM2));
		EXPECT_EQ(expectedAdvanceAngle3, getAdvanceAngle(inputRPM3));
	}
	TEST(IgnitionControl_CalculateTimesAndAnglesSuite, CalculateTimeFromAngle)
	{

		uint16_t inputRPM2 = 4500;
		uint16_t inputAdvanceAngle = 31;
		uint16_t expectedTime = 1147;		//values can drift ~1-2 uS depends on compiler precision
		EXPECT_EQ(expectedTime, CalculateTime_u_FromAngle(inputRPM2, inputAdvanceAngle));
	}
	TEST(IgnitionControl_CalculateTimesAndAnglesSuite, CalculateFiringTimeCylinder1)
	{

		uint16_t OneFullRotationTime = 4500;
		uint16_t AdvanceAngleTime = 31;
		uint16_t expectedTime = OneFullRotationTime - AdvanceAngleTime;		//values can drift  uS depends on compiler precision
		EXPECT_EQ(expectedTime, Calculate_u_FiringTimeCylinder1(AdvanceAngleTime, OneFullRotationTime));
	}



	int main(int argc, char** argv)
	{
		testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
