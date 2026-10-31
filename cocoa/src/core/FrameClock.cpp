#include "core/FrameClock.hpp"
#include <algorithm>
#include <chrono>
#include <thread>

namespace cocoa::core
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

    void FrameClock::reset()
    {
        m_last = m_start = std::chrono::high_resolution_clock::now();
        m_accumulator = 0.0f;
        m_deltaTime = 0.0f;
    }

    void FrameClock::tick()
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = now - m_last;
        m_last = now;
        m_deltaTime = std::min(delta.count(), m_maxDelta);
        m_accumulator += m_deltaTime;
    }

    bool FrameClock::canUpdate() const
    {
        return m_fixedDelta > 0.0f && m_accumulator >= m_fixedDelta;
    }

    void FrameClock::consumeUpdate()
    {
        if (m_fixedDelta > 0.0f)
            m_accumulator -= m_fixedDelta;
    }

    float FrameClock::getDelta() const
    {
        return m_deltaTime;
    }

    float FrameClock::getFixedDelta() const
    {
        return (m_fixedDelta > 0.0f) ? m_fixedDelta : m_deltaTime;
    }

    float FrameClock::getAlpha() const
    {
        return (m_fixedDelta > 0.0f) ? std::clamp(m_accumulator / m_fixedDelta, 0.0f, 1.0f) : 1.0f;
    }

    void FrameClock::sleepNextFrame() const
	{
	    if (m_targetFrameTime <= 0.0f)
	        return;

	    const auto targetFrameEnd =
            m_last +
            std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
                std::chrono::duration<float>(m_targetFrameTime));

	    std::this_thread::sleep_until(targetFrameEnd);
	}

    float FrameClock::getElapsed() const
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = now - m_start;

        return elapsedTime.count();
    }

    float FrameClock::getRemainingFrameTime() const
    {
	    if (m_targetFrameTime <= 0.0f)
	        return 0.0f;

		const auto now = std::chrono::high_resolution_clock::now();

		const std::chrono::duration<float> elapsed = now - m_last;

		return std::max(0.0f, m_targetFrameTime - elapsed.count());
    }
}
