find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

set(VEXENGINE_PUBLIC_HEADERS
    include/Core/Application.hpp

    include/Platforms/IWindow.hpp
    include/Platforms/WindowProperties.hpp

    include/Graphics/Renderer2D.hpp
    include/Graphics/IGraphicsDevice.hpp

    include/Assets/AssetManager.hpp
    include/Assets/ImageLoader.hpp
    include/Assets/IPathProvider.hpp
    include/Assets/Asset.hpp
    include/Assets/AssetPathProvider.hpp

    include/Scenes/SceneManager.hpp
    include/Scenes/Scene.hpp
    include/Scenes/ECS/World.hpp
    include/Scenes/ECS/Entity.hpp
    include/Scenes/ECS/ComponentType.hpp
    include/Scenes/ECS/ComponentStorage.hpp
    include/Scenes/ECS/View.hpp
    include/Scenes/Systems/ISystem.hpp
    include/Scenes/Components/TransformComponent.hpp
    include/Scenes/Components/CameraComponent.hpp
    include/Scenes/Components/VelocityComponent.hpp
    include/Scenes/Components/CollisionComponent.hpp
    include/Scenes/Components/RenderableComponent.hpp
    include/Scenes/Systems/CameraSystem.hpp
    include/Scenes/Systems/MovementSystem.hpp
    include/Scenes/Systems/CollisionSystem.hpp
    include/Scenes/Systems/RenderSystem.hpp

    include/Chronos/FrameClock.hpp

    include/Inputs/InputHandler.hpp
)

set(VEXENGINE_PRIVATE_SOURCES
    src/Core/Application.cpp

    src/Platforms/GLFW/GLFWWindow.hpp
    src/Platforms/GLFW/GLFWWindow.cpp

    src/Graphics/Renderer2D.cpp
    src/Graphics/OpenGL/OpenGLContext.hpp
    src/Graphics/OpenGL/OpenGLContext.cpp
    src/Graphics/OpenGL/OpenGLGraphicsDevice.hpp
    src/Graphics/OpenGL/OpenGLGraphicsDevice.cpp

    src/Assets/AssetManager.cpp
    src/Assets/ImageLoader.cpp
    src/Assets/Asset.cpp
    src/Assets/AssetPathProvider.cpp

    src/Scenes/SceneManager.cpp
    src/Scenes/Scene.cpp
    src/Scenes/ECS/World.cpp
    src/Scenes/ECS/Entity.cpp
    src/Scenes/Systems/CameraSystem.cpp
    src/Scenes/Systems/MovementSystem.cpp
    src/Scenes/Systems/CollisionSystem.cpp
    src/Scenes/Systems/RenderSystem.cpp

    src/Chronos/FrameClock.cpp

    src/Inputs/InputHandler.cpp
)

add_library(${VEXENGINE_TARGET_NAME}
    ${VEXENGINE_PUBLIC_HEADERS}
    ${VEXENGINE_PRIVATE_SOURCES}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX "Header Files"
    FILES ${VEXENGINE_PUBLIC_HEADERS}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "Source Files"
    FILES ${VEXENGINE_PRIVATE_SOURCES}
)

target_include_directories(${VEXENGINE_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${VEXENGINE_TARGET_NAME} PRIVATE
    glfw
    GLEW::GLEW
)