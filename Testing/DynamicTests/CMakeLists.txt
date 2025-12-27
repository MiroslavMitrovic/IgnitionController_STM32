cmake_minimum_required(VERSION 3.24)

project(IgnitionController_UnitTesting)

#get googletest
include(FetchContent)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

add_library(IgnitionCtrl_Main STATIC code/test_IgnitionCotrol_Main.c)

add_library(IgnitionCtrl_CalculateTimesAndAngles STATIC code/test_IgnitionCtrl_CalculateTimesAndAngles.c)

add_executable(UnitTesting code/test_gtest.cpp)

target_link_libraries(UnitTesting
PRIVATE
	IgnitionCtrl_Main
	IgnitionCtrl_CalculateTimesAndAngles
	GTest::gtest_main 
	GTest::gmock)
