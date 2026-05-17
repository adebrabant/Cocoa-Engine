#include "Chronos/FrameClock.hpp"
#include <chrono>
#include <algorithm>
#include <thread>

namespace VexEngine::Chronos
{
	FrameClock::FrameClock(float maxDelta, float fixedDelta, float targetFrameRate) :
		m_maxDelta(maxDelta),
		m_fixedDelta(fixedDelta),
		m_targetFrameTime(targetFrameRate),
		m_accumulator(0.0f),
		m_deltaTime(0.0f)
	{
		m_last = std::chrono::high_resolution_clock::now();
		m_start = m_last;
	}

    void FrameClock::Reset()
    {
        m_last = m_start = std::chrono::high_resolution_clock::now();
        m_accumulator = 0.0f;
        m_deltaTime = 0.0f;
    }

    void FrameClock::Tick()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = now - m_last;
        m_last = now;
        m_deltaTime = std::min(delta.count(), m_maxDelta);
        m_accumulator += m_deltaTime;
    }

    bool FrameClock::CanUpdate() const
    {
        return m_fixedDelta > 0.0f && m_accumulator >= m_fixedDelta;
    }

    void FrameClock::ConsumeUpdate()
    {
        if (m_fixedDelta > 0.0f)
            m_accumulator -= m_fixedDelta;
    }

    float FrameClock::GetDelta() const
    {
        return m_deltaTime;
    }

    float FrameClock::GetFixedDelta() const
    {
        return (m_fixedDelta > 0.0f) ? m_fixedDelta : m_deltaTime;
    }

    float FrameClock::GetAlpha() const
    {
        return (m_fixedDelta > 0.0f) ? std::clamp(m_accumulator / m_fixedDelta, 0.0f, 1.0f) : 1.0f;
    }

    void FrameClock::SleepNextFrame() const
    {
        if (m_targetFrameTime <= 0.0f)
            return; 

        if (m_deltaTime < m_targetFrameTime)
        {
            auto sleepTime = std::chrono::duration<float>(m_targetFrameTime - m_deltaTime);
            std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(sleepTime));
        }
    }

    float FrameClock::GetElapsed() const
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = now - m_start;

        return elapsedTime.count();
    }
}