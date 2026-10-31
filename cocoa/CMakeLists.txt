find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Threads REQUIRED)

set(COCOA_PUBLIC_HEADERS
    include/core/Application.hpp
    include/core/Color.hpp

    include/utilities/Memory.hpp
    include/utilities/Threading.hpp

    include/platforms/Window.hpp
    include/platforms/WindowProperties.hpp
    include/platforms/FramebufferResizeEvent.hpp

    include/graphics/Renderer2D.hpp
    include/graphics/GraphicsDevice.hpp
    include/graphics/TextureSpec.hpp
    include/graphics/BufferLayout.hpp
    include/graphics/BufferElement.hpp
    include/graphics/IndexBuffer.hpp
    include/graphics/Shader.hpp
    include/graphics/Texture2D.hpp
    include/graphics/VertexArray.hpp
    include/graphics/VertexBuffer.hpp
    include/graphics/TextureManager.hpp
    include/graphics/ShaderManager.hpp
    include/graphics/MaterialManager.hpp
    include/graphics/Material.hpp
    include/graphics/Sprite.hpp
    include/graphics/SpriteManager.hpp
    include/graphics/GraphicsHandles.hpp
    include/graphics/OrthographicProjection.hpp
    include/graphics/Viewport.hpp
    include/graphics/QuadBatch.hpp
    include/graphics/RenderStatistics.hpp
    include/graphics/BlendMode.hpp
    include/graphics/SortLayer.hpp
    include/graphics/Framebuffer.hpp

    include/assets/AssetManager.hpp
    include/assets/AssetLoader.hpp
    include/assets/AssetPathProvider.hpp
    include/assets/Image.hpp
    include/assets/ShaderSource.hpp
    include/assets/AssetDatabase.hpp
    include/assets/JsonAssetDatabase.hpp
    include/assets/ResourceLoader.hpp
    include/assets/AssetSource.hpp
    include/assets/FilesystemAssetSource.hpp

    include/math/Vector2f.hpp
    include/math/Vector3f.hpp
    include/math/Vector4f.hpp
    include/math/Matrix2f.hpp
    include/math/Matrix3f.hpp
    include/math/Matrix4f.hpp

    include/scenes/SceneManager.hpp
    include/scenes/Scene.hpp
    include/scenes/ecs/World.hpp
    include/scenes/ecs/Entity.hpp
    include/scenes/ecs/ComponentType.hpp
    include/scenes/ecs/ComponentStorage.hpp
    include/scenes/ecs/View.hpp
    include/scenes/systems/System.hpp
    include/scenes/components/TransformComponent.hpp
    include/scenes/components/CameraComponent.hpp
    include/scenes/components/VelocityComponent.hpp
    include/scenes/components/CollisionComponent.hpp
    include/scenes/components/SpriteComponent.hpp
    include/scenes/components/QuadComponent.hpp

    include/scenes/systems/CameraSystem.hpp
    include/scenes/systems/MovementSystem.hpp
    include/scenes/systems/CollisionSystem.hpp
    include/scenes/systems/Render2DSystem.hpp

    include/core/FrameClock.hpp

    include/inputs/InputHandler.hpp

    include/events/EventBus.hpp
    include/scenes/components/ProjectionComponent.hpp
)

set(COCOA_PRIVATE_SOURCES
    src/core/Application.cpp

    src/utilities/Threading.cpp

    src/platforms/glfw/GLFWWindow.hpp
    src/platforms/glfw/GLFWWindow.cpp

    src/graphics/Renderer2D.cpp
    src/graphics/TextureSpec.cpp
    src/graphics/BufferLayout.cpp
    src/graphics/opengl/OpenGLContext.hpp
    src/graphics/opengl/OpenGLContext.cpp
    src/graphics/opengl/OpenGLGraphicsDevice.hpp
    src/graphics/opengl/OpenGLGraphicsDevice.cpp
    src/graphics/opengl/OpenGLShader.hpp
    src/graphics/opengl/OpenGLShader.cpp
    src/graphics/opengl/OpenGLVertexBuffer.hpp
    src/graphics/opengl/OpenGLVertexBuffer.cpp
    src/graphics/opengl/OpenGLVertexArray.hpp
    src/graphics/opengl/OpenGLVertexArray.cpp
    src/graphics/opengl/OpenGLIndexBuffer.hpp
    src/graphics/opengl/OpenGLIndexBuffer.cpp
    src/graphics/opengl/OpenGLTexture2D.hpp
    src/graphics/opengl/OpenGLTexture2D.cpp
    src/graphics/opengl/OpenGLFramebuffer.cpp
    src/graphics/opengl/OpenGLFramebuffer.hpp
    src/graphics/TextureManager.cpp
    src/graphics/ShaderManager.cpp
    src/graphics/MaterialManager.cpp
    src/graphics/SpriteManager.cpp
    src/graphics/OrthographicProjection.cpp
    src/graphics/QuadBatch.cpp

    src/assets/AssetManager.cpp
    src/assets/AssetLoader.cpp
    src/assets/AssetPathProvider.cpp
    src/assets/JsonAssetDatabase.cpp
    src/assets/ResourceLoader.cpp
    src/assets/FilesystemAssetSource.cpp

    src/scenes/SceneManager.cpp
    src/scenes/Scene.cpp
    src/scenes/ecs/World.cpp
    src/scenes/ecs/Entity.cpp
    src/scenes/systems/CameraSystem.cpp
    src/scenes/systems/MovementSystem.cpp
    src/scenes/systems/CollisionSystem.cpp
    src/scenes/systems/Render2DSystem.cpp

    src/core/FrameClock.cpp

    src/inputs/InputHandler.cpp
)

set(COCOA_RESOURCES
    resources/metadata/materials.json
    resources/metadata/shaders.json
    resources/metadata/textures.json
    resources/metadata/sprites.json

    resources/shaders/sprite_default.vert
    resources/shaders/sprite_default.frag

    resources/textures/default-01.png
)

add_library(${COCOA_TARGET_NAME}
    ${COCOA_PUBLIC_HEADERS}
    ${COCOA_PRIVATE_SOURCES}
    ${COCOA_RESOURCES}
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

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/resources
    PREFIX "Resource Files"
    FILES ${COCOA_RESOURCES}
)

target_include_directories(${COCOA_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${COCOA_TARGET_NAME} PRIVATE
    glfw
    GLEW::GLEW
)

target_link_libraries(${COCOA_TARGET_NAME} PUBLIC
    Threads::Threads
)
