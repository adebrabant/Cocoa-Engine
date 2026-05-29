#pragma once

namespace Cocoa::Inputs
{
	class InputHandler
	{
	public:
		InputHandler() = default;
		~InputHandler() = default;
        void Update();
        bool IsUpPressed()    const { return Up; }
        bool IsDownPressed()  const { return Down; }
        bool IsLeftPressed()  const { return Left; }
        bool IsRightPressed() const { return Right; }

    private:
        bool Up = false;
        bool Down = false;
        bool Left = false;
        bool Right = false;
	};
}