find_package(GTest CONFIG REQUIRED)

set(COCOA_TEST_HEADERS
    include/Stubs/Graphics/StubGraphicsDevice.hpp
    include/Stubs/Graphics/StubShader.hpp
    include/Stubs/Graphics/StubTexture2D.hpp
)

set(COCOA_TEST_SOURCES
    src/Chronos/FrameClockTests.cpp
    src/Scenes/SceneManagerTests.cpp
    src/Platforms/WindowPropertiesTests.cpp
    src/Assets/JsonDatabaseTests.cpp
    src/Assets/AssetLoaderTests.cpp
    src/Assets/AssetManagerTests.cpp
    src/Graphics/TextureSpecTests.cpp
    src/Graphics/ShaderManagerTests.cpp
    src/Graphics/TextureManagerTests.cpp
    src/Graphics/MaterialManagerTests.cpp

    src/Stubs/Graphics/StubGraphicsDevice.cpp
    src/Stubs/Graphics/StubShader.cpp
    src/Stubs/Graphics/StubTexture2D.cpp
)

set(COCOA_TEST_DATA
    src/TestData/Metadata/textures.json
    src/TestData/Metadata/badtextures.json
    src/TestData/Metadata/shaders.json
    src/TestData/Metadata/badshaders.json
    src/TestData/Metadata/materials.json
    src/TestData/Metadata/badmaterials.json
)

add_executable(${COCOA_TESTS_TARGET_NAME}
    ${COCOA_TEST_HEADERS}
    ${COCOA_TEST_SOURCES}
    ${COCOA_TEST_DATA}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX "Header Files"
    FILES ${COCOA_TEST_HEADERS}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "Source Files"
    FILES
        ${COCOA_TEST_SOURCES}
        ${COCOA_TEST_DATA}
)

target_include_directories(${COCOA_TESTS_TARGET_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${COCOA_TESTS_TARGET_NAME}
    PRIVATE
        ${COCOA_TARGET_NAME}
        GTest::gtest
        GTest::gtest_main
)

add_custom_command(TARGET ${COCOA_TESTS_TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TestData
        $<TARGET_FILE_DIR:${COCOA_TESTS_TARGET_NAME}>/TestData
)

add_test(NAME Cocoa.Tests COMMAND ${COCOA_TESTS_TARGET_NAME})

set_tests_properties(Cocoa.Tests PROPERTIES
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${COCOA_TESTS_TARGET_NAME}>
)