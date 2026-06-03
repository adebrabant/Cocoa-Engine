#include "Core/Application.hpp"
#include "Assets/AssetManager.hpp"
#include "Platforms/WindowProperties.hpp"
#include "Platforms/GLFW/GLFWWindow.hpp"
#include "Graphics/OpenGL/OpenGLContext.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsDevice.hpp"
#include "Graphics/Renderer2D.hpp"

#include <utility>
#include <string>
#include <iostream>

namespace Cocoa::Core
{
	Application::Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title) :
        m_assetPathProvider(),
        m_assetManager(m_assetPathProvider),
		m_sceneManager(),
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
        Graphics::Renderer2D renderer2d(graphicsDevice);

        m_frameClock.Reset();
        graphicsDevice.InitTemp(m_assetManager);

        while (window.IsOpen())
        {
            m_frameClock.Tick();
            while (m_frameClock.CanUpdate())
            {
                FixedUpdate(m_frameClock.GetFixedDelta());
                m_frameClock.ConsumeUpdate();
            }

            Update(m_frameClock.GetDelta());

            graphicsDevice.BeginFrame();
            graphicsDevice.Clear();
            graphicsDevice.RenderTemp();
            Render(renderer2d, m_frameClock.GetAlpha());

            graphicsDevice.EndFrame();

            window.OnUpdate();
            m_frameClock.SleepNextFrame();
        }
    }

    void Application::FixedUpdate(float fixedDeltaTime)
    {
        m_sceneManager.FixedUpdate(fixedDeltaTime);
    }

	void Application::Update(float deltaTime)
	{
		m_sceneManager.Update(deltaTime);
	}

	void Application::Render(Graphics::Renderer2D& renderer, float alpha)
	{
        renderer.BeginScene();
		//m_sceneManager.Render(*m_renderer, alpha);
        renderer.EndScene();
	}
}