#pragma once

#include <chrono>

namespace cocoa::core
{
	class FrameClock
	{
	public:
		FrameClock(float maxDelta, float fixedDelta, float targetFrameRate = 1.0f / 60.0f);
		void reset();
		void tick();
		void consumeUpdate();
		void sleepNextFrame() const;
		[[nodiscard]] bool canUpdate() const;
		[[nodiscard]] float getDelta() const;
		[[nodiscard]] float getFixedDelta() const;
		[[nodiscard]] float getAlpha() const;
		[[nodiscard]] float getElapsed() const;
		[[nodiscard]] float getRemainingFrameTime() const;

	private:
		std::chrono::high_resolution_clock::time_point m_start;
		std::chrono::high_resolution_clock::time_point m_last;
		float m_maxDelta;
		float m_fixedDelta;
		float m_targetFrameTime;
		float m_accumulator;
		float m_deltaTime;
	};
}
