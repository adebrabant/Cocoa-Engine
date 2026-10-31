#pragma once

#include <cstdint>
#include <string>

namespace cocoa::platforms
{
	class WindowProperties
	{
	public:
		WindowProperties(const uint32_t width, const uint32_t height, std::string title) :
			m_title(std::move(title)),
			m_width(width),
			m_height(height) { }

		[[nodiscard]] uint32_t getWidth() const { return m_width; }
		[[nodiscard]] uint32_t getHeight() const { return m_height; }
		[[nodiscard]] const std::string& getTitle() const { return m_title; }

	private:
		std::string m_title;
		uint32_t m_width;
		uint32_t m_height;
	};
}
