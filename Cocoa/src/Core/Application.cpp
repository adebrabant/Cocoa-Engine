#include "Core/Application.hpp"
#include "Assets/AssetManager.hpp"
#include "Assets/JsonAssetDatabase.hpp"
#include "Assets/ResourceLoader.hpp"
#include "Assets/FilesystemAssetSource.hpp"
#include "Platforms/GLFW/GLFWWindow.hpp"
#include "Graphics/OpenGL/OpenGLContext.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsDevice.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/OrthographicCamera.hpp"
#include "Scenes/SceneManager.hpp"

#include <utility>
#include <string>
#include <iostream>

namespace Cocoa::Core
{
	Application::Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title) :
        m_assetPathProvider(),
		m_frameClock(0.25f, 1.0f / 60.0f),
        m_windowProps(windowWidth, windowHeight, title)
	{

	}

    void Application::Run()
    {
        Platforms::GLFWWindow window(m_windowProps);
        Graphics::OpenGLContext openGLContext;
        Graphics::OpenGLGraphicsDevice graphicsDevice;
        graphicsDevice.SetViewport(window.GetWidth(), window.GetHeight());
        graphicsDevice.SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        Assets::AssetManager assetManager;
        Assets::FilesystemAssetSource assetSource(m_assetPathProvider.GetAssetsPath());
        Assets::JsonAssetDatabase jsonAssetDatabase(m_assetPathProvider.GetMetaDataPath());

        Graphics::ShaderManager shaderManager(graphicsDevice);
        Graphics::TextureManager textureManager(graphicsDevice);
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
            graphicsDevice, 
            shaderManager,
            textureManager, 
            materialManager
        );

	    constexpr float aspectRatio = 800.0f / 600.0f;
	    Graphics::OrthographicCamera orthoCamera(
	    	-aspectRatio, aspectRatio,
	    	-1.0f, 1.0f,
	    	-1.0f, 1.0f);

        Scenes::SceneManager sceneManager(resourceLoader);

        ConfigureScenes(sceneManager);

        m_frameClock.Reset();

        while (window.IsOpen())
        {
            m_frameClock.Tick();
            while (m_frameClock.CanUpdate())
            {
                FixedUpdate(sceneManager, m_frameClock.GetFixedDelta());
                m_frameClock.ConsumeUpdate();
            }

            Update(sceneManager, m_frameClock.GetDelta());

            graphicsDevice.BeginFrame();
            graphicsDevice.Clear();
            Render(sceneManager, renderer2d, orthoCamera, m_frameClock.GetAlpha());
            graphicsDevice.EndFrame();

            window.OnUpdate();
            m_frameClock.SleepNextFrame();
        }
    }

    void Application::FixedUpdate(Scenes::SceneManager& sceneManager, float fixedDeltaTime)
    {
        sceneManager.FixedUpdate(fixedDeltaTime);
    }

	void Application::Update(Scenes::SceneManager& sceneManager, float deltaTime)
	{
        sceneManager.Update(deltaTime);
	}

	void Application::Render(Scenes::SceneManager& sceneManager, Graphics::Renderer2D& renderer, Graphics::OrthographicCamera& camera, const float alpha)
	{
        renderer.BeginScene(camera);
		sceneManager.Render(renderer, alpha);
        renderer.EndScene();
	}

    void Application::ConfigureScenes(Scenes::SceneManager& sceneManager)
    {

    }
}
