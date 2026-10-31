#include "core/Application.hpp"
#include "assets/AssetManager.hpp"
#include "assets/FilesystemAssetSource.hpp"
#include "assets/JsonAssetDatabase.hpp"
#include "assets/ResourceLoader.hpp"
#include "graphics/MaterialManager.hpp"
#include "graphics/Renderer2D.hpp"
#include "graphics/ShaderManager.hpp"
#include "graphics/SpriteManager.hpp"
#include "graphics/TextureManager.hpp"
#include "graphics/opengl/OpenGLContext.hpp"
#include "graphics/opengl/OpenGLGraphicsDevice.hpp"
#include "platforms/FramebufferResizeEvent.hpp"
#include "platforms/glfw/GLFWWindow.hpp"
#include "scenes/SceneManager.hpp"

#include <string>

namespace cocoa::core
{
	Application::Application(const uint32_t windowWidth, const uint32_t windowHeight, const std::string& title) :
        m_assetPathProvider(),
		m_frameClock(0.25f, 1.0f / 60.0f),
        m_windowProps(windowWidth, windowHeight, title),
		m_eventBus(),
		m_graphicsDevice(nullptr),
		m_FramebufferResizeEventToken()
	{
		RegisterEventHandlers();
	}

	Application::~Application()
	{
		UnregisterEventHandlers();
	}

    void Application::Run()
    {
        platforms::GLFWWindow window(m_eventBus, m_windowProps);
        graphics::OpenGLContext openGLContext;

		m_graphicsDevice = CreateUnique<graphics::OpenGLGraphicsDevice>();
        m_graphicsDevice->SetViewport(0, 0, m_windowProps.GetWidth(), m_windowProps.GetHeight());
        m_graphicsDevice->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        assets::AssetManager assetManager;
        assets::FilesystemAssetSource assetSource(m_assetPathProvider.GetAssetsPath());
        assets::JsonAssetDatabase jsonAssetDatabase(m_assetPathProvider.GetMetaDataPath());

        graphics::ShaderManager shaderManager(*m_graphicsDevice);
        graphics::TextureManager textureManager(*m_graphicsDevice);
        graphics::MaterialManager materialManager;
		graphics::SpriteManager spriteManager;

        assets::ResourceLoader resourceLoader(
            jsonAssetDatabase,
            assetSource,
            assetManager,
            textureManager,
            shaderManager,
            materialManager,
            spriteManager
        );

        graphics::Renderer2D renderer2d(
            *m_graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager
        );

        scenes::SceneManager sceneManager(resourceLoader);

        ConfigureScenes(sceneManager);

        m_frameClock.Reset();

        while (window.IsOpen())
        {
            m_frameClock.Tick();
        	window.ProcessEvents();
            while (m_frameClock.CanUpdate())
            {
            	sceneManager.FixedUpdate(m_frameClock.GetFixedDelta());
                m_frameClock.ConsumeUpdate();
            }

        	sceneManager.Update(m_frameClock.GetDelta());

            m_graphicsDevice->BeginFrame();
            m_graphicsDevice->Clear();
        	sceneManager.Render(renderer2d, m_frameClock.GetAlpha());
            m_graphicsDevice->EndFrame();

            window.OnUpdate();

        	window.WaitForEvents(m_frameClock.GetRemainingFrameTime());
        }
    }

    void Application::ConfigureScenes(scenes::SceneManager& sceneManager)
    {

    }

	void Application::RegisterEventHandlers()
	{
		m_FramebufferResizeEventToken = m_eventBus.Subscribe<platforms::FramebufferResizeEvent>(
			[this](const platforms::FramebufferResizeEvent& evt)
			{
				if (evt.Width == 0 || evt.Height == 0)
					return;

				m_graphicsDevice->SetViewport(0,0, evt.Width, evt.Height);
			});
	}

    void Application::UnregisterEventHandlers()
    {
		m_eventBus.Unsubscribe<platforms::FramebufferResizeEvent>(m_FramebufferResizeEventToken);
    }
}
