#pragma once
#include "InputDevice.h"


class Mouse : public InputDevice::InputDeviceBase
{
public:
	Mouse() = default;
	virtual ~Mouse() = default;

	virtual void Initialize();
	virtual void Update();
	virtual void Reset();
	void OnMouseState();

	Vector2 MousePosition() { return m_mousePos; }
	bool    IsMouseDown(int _mouseType);
	bool    IsMouseHold(int _mouseType);
	bool    IsMouseUp(int _mouseType);
private:
	struct MouseState {
		bool Left = false;
		bool Right = false;
		bool Mid = false;
	};
	MouseState m_curState;
	MouseState m_preState;
	Vector2	   m_mousePos;
public:
	enum Type // ¸¶¿ì½º
	{
		LEFT = VK_LBUTTON,
		MID = VK_MBUTTON,
		RIGHT = VK_RBUTTON,
	};
};

