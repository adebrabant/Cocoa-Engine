#pragma once

namespace cocoa::inputs
{
	class InputHandler
	{
	public:
		InputHandler() = default;
		~InputHandler() = default;
        void update();
        bool isUpPressed()    const { return m_up; }
        bool isDownPressed()  const { return m_down; }
        bool isLeftPressed()  const { return m_left; }
        bool isRightPressed() const { return m_right; }

    private:
        bool m_up = false;
        bool m_down = false;
        bool m_left = false;
        bool m_right = false;
	};
}
