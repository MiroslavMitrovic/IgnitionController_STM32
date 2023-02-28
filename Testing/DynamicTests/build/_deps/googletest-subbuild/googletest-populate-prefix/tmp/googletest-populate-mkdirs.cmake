# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-src"
  "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-build"
  "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/projects/atmel/attiny85/IgnitionController/unitTests/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
