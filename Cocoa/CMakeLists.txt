find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

set(COCOA_PUBLIC_HEADERS
    include/Core/Application.hpp
    include/Core/Memory.hpp
    include/Core/Color.hpp

    include/Platforms/Window.hpp
    include/Platforms/WindowProperties.hpp

    include/Graphics/Renderer2D.hpp
    include/Graphics/GraphicsDevice.hpp
    include/Graphics/TextureSpec.hpp
    include/Graphics/BufferLayout.hpp
    include/Graphics/BufferElement.hpp
    include/Graphics/IndexBuffer.hpp
    include/Graphics/Shader.hpp
    include/Graphics/Texture2D.hpp
    include/Graphics/VertexArray.hpp
    include/Graphics/VertexBuffer.hpp
    include/Graphics/TextureManager.hpp
    include/Graphics/ShaderManager.hpp
    include/Graphics/MaterialManager.hpp
    include/Graphics/Material.hpp
    include/Graphics/GraphicsHandles.hpp

    include/Assets/AssetManager.hpp
    include/Assets/AssetLoader.hpp
    include/Assets/AssetPathProvider.hpp
    include/Assets/Image.hpp
    include/Assets/ShaderSource.hpp
    include/Assets/AssetDatabase.hpp
    include/Assets/JsonAssetDatabase.hpp
    include/Assets/ResourceLoader.hpp

    include/Scenes/SceneManager.hpp
    include/Scenes/Scene.hpp
    include/Scenes/ECS/World.hpp
    include/Scenes/ECS/Entity.hpp
    include/Scenes/ECS/ComponentType.hpp
    include/Scenes/ECS/ComponentStorage.hpp
    include/Scenes/ECS/View.hpp
    include/Scenes/Systems/System.hpp
    include/Scenes/Components/TransformComponent.hpp
    include/Scenes/Components/CameraComponent.hpp
    include/Scenes/Components/VelocityComponent.hpp
    include/Scenes/Components/CollisionComponent.hpp
    include/Scenes/Components/Renderable2DComponent.hpp

    include/Scenes/Systems/CameraSystem.hpp
    include/Scenes/Systems/MovementSystem.hpp
    include/Scenes/Systems/CollisionSystem.hpp
    include/Scenes/Systems/RenderSystem.hpp

    include/Chronos/FrameClock.hpp

    include/Inputs/InputHandler.hpp
)

set(COCOA_PRIVATE_SOURCES
    src/Core/Application.cpp

    src/Platforms/GLFW/GLFWWindow.hpp
    src/Platforms/GLFW/GLFWWindow.cpp

    src/Graphics/Renderer2D.cpp
    src/Graphics/TextureSpec.cpp
    src/Graphics/BufferLayout.cpp
    src/Graphics/OpenGL/OpenGLContext.hpp
    src/Graphics/OpenGL/OpenGLContext.cpp
    src/Graphics/OpenGL/OpenGLGraphicsDevice.hpp
    src/Graphics/OpenGL/OpenGLGraphicsDevice.cpp
    src/Graphics/OpenGL/OpenGLShader.hpp
    src/Graphics/OpenGL/OpenGLShader.cpp
    src/Graphics/OpenGL/OpenGLVertexBuffer.hpp
    src/Graphics/OpenGL/OpenGLVertexBuffer.cpp
    src/Graphics/OpenGL/OpenGLVertexArray.hpp
    src/Graphics/OpenGL/OpenGLVertexArray.cpp
    src/Graphics/OpenGL/OpenGLIndexBuffer.hpp
    src/Graphics/OpenGL/OpenGLIndexBuffer.cpp
    src/Graphics/OpenGL/OpenGLTexture2D.hpp
    src/Graphics/OpenGL/OpenGLTexture2D.cpp
    src/Graphics/TextureManager.cpp
    src/Graphics/ShaderManager.cpp
    src/Graphics/MaterialManager.cpp

    src/Assets/AssetManager.cpp
    src/Assets/AssetLoader.cpp
    src/Assets/AssetPathProvider.cpp
    src/Assets/JsonAssetDatabase.cpp
    src/Assets/ResourceLoader.cpp

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

add_library(${COCOA_TARGET_NAME}
    ${COCOA_PUBLIC_HEADERS}
    ${COCOA_PRIVATE_SOURCES}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX "Header Files"
    FILES ${COCOA_PUBLIC_HEADERS}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "Source Files"
    FILES ${COCOA_PRIVATE_SOURCES}
)

target_include_directories(${COCOA_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${COCOA_TARGET_NAME} PRIVATE
    glfw
    GLEW::GLEW
)