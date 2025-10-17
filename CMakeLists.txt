cmake_minimum_required ( VERSION 3.1.0...4.0.0 )

project ( RTWeekend LANGUAGES CXX )

set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

set ( SOURCE_RT
  src/main.cc
  src/camera.h
  src/color.h
  src/hittable.h
  src/hittable_list.h
  src/interval.h
# src/material.h
  src/ray.h
  src/rt.h
  src/sphere.h
  src/vec3.h
)

include_directories(src)

message (STATUS "Compiler ID: "   ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: "   ${CMAKE_CXX_FLAGS_DEBUG})

add_compile_options(-Wnon-virtual-dtor)
add_compile_options(-Wreorder)
add_compile_options(-Wmaybe-uninitialized)
add_compile_options(-Wunused-variable)

add_executable(rt ${SOURCE_RT})
