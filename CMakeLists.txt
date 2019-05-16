cmake_minimum_required(VERSION 3.5)

project(spectrometer)

include(CTest)

# Set the compiler to use C++14
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-padded")


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

add_library(validator ${CMAKE_SOURCE_DIR}/src/validator.cc)
target_include_directories(validator PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

add_library(meas_config_type_builder ${CMAKE_SOURCE_DIR}/src/meas_config_type_builder.cc)
target_include_directories(meas_config_type_builder PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

add_library(avs_exception ${CMAKE_SOURCE_DIR}/src/avs_exception.cc)
target_include_directories(avs_exception PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

add_library(parser ${CMAKE_SOURCE_DIR}/src/parser.cc)
target_include_directories(parser PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

add_library(spectrometer ${CMAKE_SOURCE_DIR}/src/spectrometer.cc)
target_include_directories(spectrometer PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)
target_link_libraries(spectrometer
    AvaSpec
    validator
    avs_exception
    parser
    meas_config_type_builder
)
add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cc)
target_link_libraries(main
   spectrometer
)
