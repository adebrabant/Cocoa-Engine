#include "Application.hpp"
#include "Assets/AssetManager.hpp"
#include "Platforms/WindowProperties.hpp"
#include "Platforms/GLFW/GLFWWindow.hpp"

#include <utility>
#include <string>
#include <iostream>

namespace VexEngine
{
	Application::Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title) :
        m_window(std::make_unique<Platforms::GLFWWindow>()),
        m_assetPathProvider(),
        m_assetManager(m_assetPathProvider),
		m_sceneManager(),
		m_frameClock(0.25f, 1.0f / 60.0f),
        m_windowProps(windowWidth, windowHeight, title)
	{

	}

    void Application::Run()
    {
        m_window->OnInit(m_windowProps);
        m_frameClock.Reset();

        while (m_window->IsOpen())
        {
            m_frameClock.Tick();
            while (m_frameClock.CanUpdate())
            {
                FixedUpdate(m_frameClock.GetFixedDelta());
                m_frameClock.ConsumeUpdate();
            }

            Update(m_frameClock.GetDelta());
            Render(m_frameClock.GetAlpha());

            m_window->OnUpdate();
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

    // ToDo: Will revisit this
	void Application::Render(float alpha)
	{
        //m_renderer->Clear();
		//m_sceneManager.Render(*m_renderer, alpha);
        //m_renderer->Display();
	}
}