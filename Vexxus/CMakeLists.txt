add_executable(${VEXXUS_TARGET_NAME}
    src/Main.cpp

    include/GameApplication.hpp
    src/GameApplication.cpp

    include/Scenes/TestScene.hpp
    src/Scenes/TestScene.cpp

    include/Systems/InputSystem.hpp
    src/Systems/InputSystem.cpp
)

target_include_directories(${VEXXUS_TARGET_NAME} PUBLIC include)

target_link_libraries(${VEXXUS_TARGET_NAME} PRIVATE
    ${VEXENGINE_TARGET_NAME}
)

add_custom_command(TARGET ${VEXXUS_TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:${VEXXUS_TARGET_NAME}>/Assets
    COMMENT "Copying Assets folder to output directory"
)