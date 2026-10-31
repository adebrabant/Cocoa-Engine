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
		registerEventHandlers();
	}

	Application::~Application()
	{
		unregisterEventHandlers();
	}

    void Application::Run()
    {
        platforms::GLFWWindow window(m_eventBus, m_windowProps);
        graphics::OpenGLContext openGLContext;

		m_graphicsDevice = createUnique<graphics::OpenGLGraphicsDevice>();
        m_graphicsDevice->setViewport(0, 0, m_windowProps.getWidth(), m_windowProps.getHeight());
        m_graphicsDevice->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        assets::AssetManager assetManager;
        assets::FilesystemAssetSource assetSource(m_assetPathProvider.getAssetsPath());
        assets::JsonAssetDatabase jsonAssetDatabase(m_assetPathProvider.getMetaDataPath());

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

        configureScenes(sceneManager);

        m_frameClock.reset();

        while (window.isOpen())
        {
            m_frameClock.tick();
        	window.processEvents();
            while (m_frameClock.canUpdate())
            {
            	sceneManager.fixedUpdate(m_frameClock.getFixedDelta());
                m_frameClock.consumeUpdate();
            }

        	sceneManager.update(m_frameClock.getDelta());

            m_graphicsDevice->beginFrame();
            m_graphicsDevice->clear();
        	sceneManager.render(renderer2d, m_frameClock.getAlpha());
            m_graphicsDevice->endFrame();

            window.onUpdate();

        	window.waitForEvents(m_frameClock.getRemainingFrameTime());
        }
    }

    void Application::configureScenes(scenes::SceneManager& sceneManager)
    {

    }

	void Application::registerEventHandlers()
	{
		m_FramebufferResizeEventToken = m_eventBus.subscribe<platforms::FramebufferResizeEvent>(
			[this](const platforms::FramebufferResizeEvent& evt)
			{
				if (evt.width == 0 || evt.height == 0)
					return;

				m_graphicsDevice->setViewport(0,0, evt.width, evt.height);
			});
	}

    void Application::unregisterEventHandlers()
    {
		m_eventBus.unsubscribe<platforms::FramebufferResizeEvent>(m_FramebufferResizeEventToken);
    }
}
