::Configure and build Google Test for Dynamic Tests
rmdir /s /q build-tests
Echo Building Google Test for Dynamic Tests...
cmake -S Testing/DynamicTests -B build-tests -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake --build build-tests -j

:: RUN the tests with XML output
Echo Running Unit Tests...
.\build-tests\UnitTesting.exe --gtest_output=xml:build-tests\gtest.xml
Echo Google Test build and execution completed.
:: END of build_gtest.bat