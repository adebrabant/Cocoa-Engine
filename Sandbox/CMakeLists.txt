set(SANDBOX_PUBLIC_HEADERS
    include/GameApplication.hpp
    include/Scenes/TestScene.hpp
    include/Systems/InputSystem.hpp
)

set(SANDBOX_PRIVATE_SOURCES
    src/Main.cpp
    src/GameApplication.cpp
    src/Scenes/TestScene.cpp
    src/Systems/InputSystem.cpp
)

set(SANDBOX_RESOURCES
    resources/metadata/materials.json
    resources/metadata/shaders.json
    resources/metadata/textures.json

    resources/textures/backgrounds/sun-set-01.png
    resources/textures/backgrounds/mountains-01.png
    resources/textures/backgrounds/forest-fog-01.png
    resources/textures/backgrounds/forest-fog-02.png
    resources/textures/werewolf-idle1.png
)

add_executable(${SANDBOX_TARGET_NAME}
    ${SANDBOX_PUBLIC_HEADERS}
    ${SANDBOX_PRIVATE_SOURCES}
    ${SANDBOX_RESOURCES}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX "Header Files"
    FILES ${SANDBOX_PUBLIC_HEADERS}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "Source Files"
    FILES ${SANDBOX_PRIVATE_SOURCES}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/resources
    PREFIX "Resource Files"
    FILES ${SANDBOX_RESOURCES}
)

target_include_directories(${SANDBOX_TARGET_NAME} PUBLIC include)

target_link_libraries(${SANDBOX_TARGET_NAME} PRIVATE
    ${COCOA_TARGET_NAME}
)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(COCOA_RESOURCE_DIR
    "${CMAKE_SOURCE_DIR}/Cocoa/resources"
)

set(SANDBOX_RESOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
)

set(SANDBOX_STAGED_RESOURCE_DIR
    "$<TARGET_FILE_DIR:${SANDBOX_TARGET_NAME}>/resources"
)

add_custom_command(TARGET ${SANDBOX_TARGET_NAME} POST_BUILD
    COMMAND ${Python3_EXECUTABLE}
        "${CMAKE_SOURCE_DIR}/tools/stage_resources.py"
        --input "${COCOA_RESOURCE_DIR}"
        --input "${SANDBOX_RESOURCE_DIR}"
        --output "${SANDBOX_STAGED_RESOURCE_DIR}"
    COMMENT "Staging runtime resources"
    VERBATIM
)