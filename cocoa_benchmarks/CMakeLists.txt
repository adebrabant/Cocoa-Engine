find_package(benchmark CONFIG REQUIRED)

set(COCOA_BENCHMARKS_HEADERS)

set(COCOA_BENCHMARKS_SOURCES
    src/stubs/graphics/StubGraphicsDevice.hpp
    src/stubs/graphics/StubShader.hpp
    src/stubs/graphics/StubTexture2D.hpp
    src/stubs/graphics/StubVertexArray.hpp
    src/stubs/graphics/StubVertexBuffer.hpp
    src/stubs/graphics/StubIndexBuffer.hpp

    src/fixtures/Renderer2DFixture.hpp
    src/graphics/Renderer2DBenchmarks.cpp
)

add_executable(${COCOA_BENCHMARKS_TARGET_NAME}
    ${COCOA_BENCHMARKS_HEADERS}
    ${COCOA_BENCHMARKS_SOURCES}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX "Header Files"
    FILES ${COCOA_BENCHMARKS_HEADERS}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "Source Files"
    FILES ${COCOA_BENCHMARKS_SOURCES}
)

target_include_directories(${COCOA_BENCHMARKS_TARGET_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${COCOA_BENCHMARKS_TARGET_NAME}
    PRIVATE
        ${COCOA_TARGET_NAME}
        benchmark::benchmark_main
)
