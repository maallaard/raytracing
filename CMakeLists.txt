cmake_minimum_required ( VERSION 3.1.0...4.0.0 )

project ( RTWeekend LANGUAGES CXX )

set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

add_executable(inOneWeekend src/main.cc)
