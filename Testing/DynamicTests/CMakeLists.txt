cmake_minimum_required(VERSION 3.24)

project(IgnitionController_UnitTesting)

#get googletest
include(FetchContent)
FetchContent_Declare(googletest
			GIT_REPOSITORY https://github.com/google/googletest
			GIT_TAG release-1.12.1)
FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

add_library(IgnitionCtrl_Main STATIC code/test_IgnitionCotrol_Main.c)

add_library(IgnitionCtrl_CalculateTimesAndAngles STATIC code/test_IgnitionCtrl_CalculateTimesAndAngles.c)

add_executable(mainApp code/test_main.c)

target_link_libraries(mainApp IgnitionCtrl_Main )

add_executable(UnitTesting code/test_gtest.cpp)

target_link_libraries(UnitTesting IgnitionCtrl_Main IgnitionCtrl_CalculateTimesAndAngles gtest_main gmock_main)

