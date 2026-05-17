find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

add_library(${VEXENGINE_TARGET_NAME}
    include/Application.hpp
    src/Application.cpp

    include/Platforms/IWindow.hpp
    include/Platforms/WindowProperties.hpp

    src/Platforms/GLFW/GLFWWindow.hpp
    src/Platforms/GLFW/GLFWWindow.cpp

    include/Assets/AssetManager.hpp
    src/Assets/AssetManager.cpp

    include/Assets/ImageLoader.hpp
    src/Assets/ImageLoader.cpp

    include/Assets/IPathProvider.hpp

    include/Assets/Asset.hpp
    src/Assets/Asset.cpp

    include/Assets/AssetPathProvider.hpp
    src/Assets/AssetPathProvider.cpp

    include/Scenes/SceneManager.hpp
    src/Scenes/SceneManager.cpp

    include/Scenes/Scene.hpp
    src/Scenes/Scene.cpp

    include/Chronos/FrameClock.hpp
    src/Chronos/FrameClock.cpp

    include/Core/ECS/World.hpp
    src/Core/ECS/World.cpp

    include/Core/ECS/Entity.hpp
    src/Core/ECS/Entity.cpp

    include/Core/ECS/ComponentType.hpp

    include/Core/ECS/ComponentStorage.hpp

    include/Core/ECS/View.hpp

    include/Core/Systems/ISystem.hpp

    include/Core/Components/TransformComponent.hpp
    include/Core/Components/CameraComponent.hpp
    include/Core/Components/VelocityComponent.hpp
    include/Core/Components/CollisionComponent.hpp
    include/Core/Components/RenderableComponent.hpp

    include/Core/Systems/CameraSystem.hpp
    src/Core/Systems/CameraSystem.cpp

    include/Core/Systems/MovementSystem.hpp
    src/Core/Systems/MovementSystem.cpp

   include/Core/Systems/CollisionSystem.hpp
    src/Core/Systems/CollisionSystem.cpp

    include/Core/Systems/RenderSystem.hpp
    src/Core/Systems/RenderSystem.cpp

    include/Inputs/InputHandler.hpp
    src/Inputs/InputHandler.cpp
)

target_include_directories(${VEXENGINE_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${VEXENGINE_TARGET_NAME} PRIVATE
    glfw
    GLEW::GLEW
)