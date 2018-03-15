cmake_minimum_required(VERSION 2.8.9)
project(spectrometer)

include_directories(./include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-padded")

add_executable(validator spectrometer_config_validator.cc)
