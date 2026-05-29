add_executable(${COCOA_TESTS_TARGET_NAME}
    src/Chronos/FrameClockTests.cpp
    src/Scenes/SceneManagerTests.cpp
    src/Platforms/WindowPropertiesTests.cpp
)

target_include_directories(${COCOA_TESTS_TARGET_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${COCOA_TESTS_TARGET_NAME}
    PRIVATE
        ${COCOA_TARGET_NAME}
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME Cocoa.Tests COMMAND ${COCOA_TESTS_TARGET_NAME})