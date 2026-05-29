#pragma once

#include <cstdint>
#include <string>

namespace Cocoa::Platforms
{
	class WindowProperties
	{
	public:
		WindowProperties(uint32_t width, uint32_t height, std::string title) :
			m_title(std::move(title)),
			m_width(width),
			m_height(height) { }

		uint32_t GetWidth() const { return m_width; }
		uint32_t GetHeight() const { return m_height; }
		const std::string& GetTitle() const { return m_title; }

	private:
		std::string m_title;
		uint32_t m_width;
		uint32_t m_height;
	};
}