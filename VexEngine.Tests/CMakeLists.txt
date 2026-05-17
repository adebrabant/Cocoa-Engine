add_executable(${VEXENGINE_TESTS_TARGET_NAME}
    src/Chronos/FrameClockTests.cpp
    src/Scenes/SceneManagerTests.cpp
    src/Platforms/WindowPropertiesTests.cpp
)

target_include_directories(${VEXENGINE_TESTS_TARGET_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${VEXENGINE_TESTS_TARGET_NAME}
    PRIVATE
        ${VEXENGINE_TARGET_NAME}
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME VexEngine.Tests COMMAND ${VEXENGINE_TESTS_TARGET_NAME})