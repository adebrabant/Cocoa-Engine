#include "Application.hpp"
#include "Assets/AssetManager.hpp"
#include "Platforms/WindowProperties.hpp"
#include "Platforms/GLFW/GLFWWindow.hpp"

#include <utility>
#include <string>
#include <iostream>

namespace VexEngine
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title) :
		m_graphicsFactory(),
        m_assetPathProvider(),
        m_assetManager(m_assetPathProvider),
		m_window(std::move(m_graphicsFactory.CreateWindow(windowWidth, windowHeight, title))),
		m_renderer(std::move(m_graphicsFactory.CreateRenderer(*m_window))),
        m_platformWindow(nullptr),
		m_sceneManager(),
		m_frameClock(0.25f, 1.0f / 60.0f)
	{
        Platforms::WindowProperties windowProps(
            static_cast<uint32_t>(windowWidth), 
            static_cast<uint32_t>(windowHeight), 
            title
        );

        m_platformWindow = std::make_unique<Platforms::GLFWWindow>();
        m_platformWindow->OnInit(windowProps);
	}

    void Application::Run()
    {
        m_window->Open();
        m_frameClock.Reset();

        while (m_window->IsOpen())
        {
            m_frameClock.Tick();
            while (m_frameClock.CanUpdate())
            {
                Update(m_frameClock.GetFixedDelta());
                m_frameClock.ConsumeUpdate();
            }

            float alpha = m_frameClock.GetAlpha();

            m_renderer->Clear();

            Render(alpha);
            m_renderer->Display();

            m_platformWindow->OnUpdate();
            m_frameClock.SleepNextFrame();
        }
    }

	void Application::Update(float deltaTime)
	{
		m_sceneManager.Update(deltaTime);
	}

	void Application::Render(float alpha)
	{
		m_sceneManager.Render(*m_renderer, alpha);
	}
}