cmake_minimum_required(VERSION 3.29.3)

project(Vexxus
    VERSION 1.0.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD           20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(COCOA_TARGET_NAME Cocoa)
set(VEXXUS_TARGET_NAME Vexxus)

set(COCOA_TESTS_TARGET_NAME Cocoa.Tests)

enable_testing()

add_subdirectory(${COCOA_TARGET_NAME})
add_subdirectory(${VEXXUS_TARGET_NAME})

add_subdirectory(${COCOA_TESTS_TARGET_NAME})

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${VEXXUS_TARGET_NAME})
endif()