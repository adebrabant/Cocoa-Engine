#include "Application.hpp"
#include "Assets/AssetManager.hpp"

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
		m_sceneManager(),
		m_frameClock(0.25f, 1.0f / 60.0f)
	{

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