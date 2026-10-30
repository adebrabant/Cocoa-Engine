find_package(GTest CONFIG REQUIRED)

set(COCOA_TEST_HEADERS
    include/stubs/Graphics/StubGraphicsDevice.hpp
    include/stubs/Graphics/StubShader.hpp
    include/stubs/Graphics/StubTexture2D.hpp
    include/stubs/Graphics/StubVertexArray.hpp
    include/stubs/Graphics/StubVertexBuffer.hpp
    include/stubs/Graphics/StubIndexBuffer.hpp
    include/stubs/Graphics/StubFramebuffer.hpp
    include/helpers/TestFileReader.hpp
)

set(COCOA_TEST_SOURCES
    src/core/FrameClockTests.cpp
    src/scenes/SceneManagerTests.cpp
    src/platforms/WindowPropertiesTests.cpp

    src/assets/JsonDatabaseTests.cpp
    src/assets/AssetLoaderTests.cpp
    src/assets/AssetManagerTests.cpp
    src/assets/ResourceLoaderTests.cpp
    src/assets/FilesystemAssetSourceTests.cpp

    src/math/Vector2fTests.cpp
    src/math/Vector3fTests.cpp
    src/math/Vector4fTests.cpp
    src/math/Matrix2fTests.cpp
    src/math/Matrix3fTests.cpp
    src/math/Matrix4fTests.cpp

    src/graphics/TextureSpecTests.cpp
    src/graphics/ShaderManagerTests.cpp
    src/graphics/TextureManagerTests.cpp
    src/graphics/MaterialManagerTests.cpp
    src/graphics/SpriteManagerTests.cpp
    src/graphics/OrthographicProjectionTests.cpp
    src/graphics/RenderStatisticsTests.cpp
    src/graphics/QuadBatchTests.cpp
    src/graphics/Renderer2DTests.cpp

    src/stubs/graphics/StubGraphicsDevice.cpp
    src/stubs/graphics/StubShader.cpp
    src/stubs/graphics/StubTexture2D.cpp
    src/stubs/graphics/StubVertexArray.cpp
    src/stubs/graphics/StubVertexBuffer.cpp
    src/stubs/graphics/StubIndexBuffer.cpp

    src/events/EventBusTests.cpp

    src/core/ColorTests.cpp
)

set(COCOA_TEST_DATA
    src/test_data/meta_data/textures.json
    src/test_data/meta_data/badtextures.json
    src/test_data/meta_data/shaders.json
    src/test_data/meta_data/badshaders.json
    src/test_data/meta_data/materials.json
    src/test_data/meta_data/badmaterials.json
    src/test_data/meta_data/sprites.json
    src/test_data/meta_data/badsprites.json
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
    COMMAND ${CMAKE_COMMAND} -E rm -rf
        "$<TARGET_FILE_DIR:${COCOA_TESTS_TARGET_NAME}>/test_data"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/test_data"
        "$<TARGET_FILE_DIR:${COCOA_TESTS_TARGET_NAME}>/test_data"

    COMMENT "Copying Cocoa test data"
    VERBATIM
)

add_test(
    NAME CocoaTests
    COMMAND ${COCOA_TESTS_TARGET_NAME}
)

set_tests_properties(CocoaTests PROPERTIES
    WORKING_DIRECTORY "$<TARGET_FILE_DIR:${COCOA_TESTS_TARGET_NAME}>"
)
