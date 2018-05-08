###############################
# Copyright AnthonySteel 2018 #
###############################

cmake_minimum_required(VERSION 3.5)

project(spectrometer)

include(CTest)

#########################
# C++-Oriented Commands #
#########################
# Set the compiler to use C++14
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-padded")

#########
# GTest #
#########
include(${CMAKE_SOURCE_DIR}/DownloadGTest.cmake)

###########
# AvaSpec #
###########
# Generate an interface for the AvaSpec libraries
if(UNIX)
    add_library(AvaSpec INTERFACE)
    target_include_directories(AvaSpec INTERFACE
        ${CMAKE_SOURCE_DIR}/include/
    )
    target_link_libraries(AvaSpec INTERFACE
        avs
        usb-1.0
    )
endif()

########################
# Validator Library #
########################
add_library(validator ${CMAKE_SOURCE_DIR}/src/validator.cc)
target_include_directories(validator PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

####################################
# Meas Config Type Builder Library #
####################################
add_library(meas_config_type_builder ${CMAKE_SOURCE_DIR}/src/meas_config_type_builder.cc)
target_include_directories(meas_config_type_builder PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

########################
# Spectrometer Library #
########################

add_library(spectrometer ${CMAKE_SOURCE_DIR}/src/spectrometer.cc)
target_include_directories(spectrometer PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)
target_link_libraries(spectrometer
    AvaSpec
    validator
    meas_config_type_builder
)

###################
# Test Validation #
###################
add_executable(SpecTest test/spectrometer.test.cc)
target_include_directories(SpecTest PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)
target_link_libraries(SpecTest
    spectrometer
    GTest
)
add_test(NAME SpecTest COMMAND SpecTest)

# vim: set ts=4 sw=4 et :
