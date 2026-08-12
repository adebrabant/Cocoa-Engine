#include "Core/Application.hpp"
#include "Assets/AssetManager.hpp"
#include "Assets/JsonAssetDatabase.hpp"
#include "Assets/ResourceLoader.hpp"
#include "Assets/FilesystemAssetSource.hpp"
#include "Platforms/GLFW/GLFWWindow.hpp"
#include "Platforms/WindowResizeEvent.hpp"
#include "Graphics/OpenGL/OpenGLContext.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsDevice.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Scenes/SceneManager.hpp"

#include <string>

namespace Cocoa::Core
{
	Application::Application(const uint32_t windowWidth, const uint32_t windowHeight, const std::string& title) :
        m_assetPathProvider(),
		m_frameClock(0.25f, 1.0f / 60.0f),
        m_windowProps(windowWidth, windowHeight, title),
        m_viewport(0, 0, windowWidth, windowHeight),
		m_eventBus(),
		m_graphicsDevice(nullptr),
		m_windowResizeEventToken()
	{
		RegisterEventHandlers();
	}

	Application::~Application()
	{
		UnregisterEventHandlers();
	}

    void Application::Run()
    {
        Platforms::GLFWWindow window(m_eventBus, m_windowProps);
        Graphics::OpenGLContext openGLContext;

		m_graphicsDevice = CreateUnique<Graphics::OpenGLGraphicsDevice>();
        m_graphicsDevice->SetViewport(m_viewport.X, m_viewport.Y, m_viewport.Width, m_viewport.Height);
        m_graphicsDevice->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        Assets::AssetManager assetManager;
        Assets::FilesystemAssetSource assetSource(m_assetPathProvider.GetAssetsPath());
        Assets::JsonAssetDatabase jsonAssetDatabase(m_assetPathProvider.GetMetaDataPath());

        Graphics::ShaderManager shaderManager(*m_graphicsDevice);
        Graphics::TextureManager textureManager(*m_graphicsDevice);
        Graphics::MaterialManager materialManager;

        Assets::ResourceLoader resourceLoader(
            jsonAssetDatabase,
            assetSource,
            assetManager,
            textureManager,
            shaderManager,
            materialManager
        );

        Graphics::Renderer2D renderer2d(
            *m_graphicsDevice,
            shaderManager,
            textureManager, 
            materialManager
        );

        Scenes::SceneManager sceneManager(resourceLoader, m_viewport);

        ConfigureScenes(sceneManager);

        m_frameClock.Reset();

        while (window.IsOpen())
        {
            m_frameClock.Tick();
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
            m_frameClock.SleepNextFrame();
        }
    }

    void Application::ConfigureScenes(Scenes::SceneManager& sceneManager)
    {

    }

	void Application::RegisterEventHandlers()
	{
		m_windowResizeEventToken = m_eventBus.Subscribe<Platforms::WindowResizeEvent>(
			[this](const Platforms::WindowResizeEvent& evt)
			{
				m_viewport.Resize(0, 0, evt.Width, evt.Height);
				m_graphicsDevice->SetViewport(0,0, evt.Width, evt.Height);
			});
	}

    void Application::UnregisterEventHandlers()
    {
		m_eventBus.Unsubscribe<Platforms::WindowResizeEvent>(m_windowResizeEventToken);
    }
}
