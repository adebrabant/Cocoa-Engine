#pragma once

#include <chrono>

namespace VexEngine::Chronos
{
	class FrameClock
	{
	public:
		FrameClock(float maxDelta, float fixedDelta, float targetFrameRate = 1.0f / 60.0f);
		void Reset();            
		void Tick();
		bool CanUpdate() const;
		void ConsumeUpdate();
		float GetDelta() const;
		float GetFixedDelta() const;
		float GetAlpha() const;
		void SleepNextFrame() const;
		float GetElapsed() const; 

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