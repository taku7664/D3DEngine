#pragma once
#include "Window/WindowBase.h"
#include "Window/WindowDataBase.h"

class WindowManager;

class Window : public Engine::WindowBase
{
public:
	virtual ~Window();
	//void SendMessegeBox(WCHAR _title, WCHAR _text, std::function<void(int, int)> func);
protected:
	Window() = default;
public:
	bool IsFocusing() { return GetFocus() == m_handle; }
};

class WindowData : public Engine::WindowDataBase
{
public:
	WindowData();
	WindowData& InitializeStyle(UINT _style) { m_class.style = _style; return *this; }
	WindowData& InitializeIcon(HICON _hIcon) { m_class.hIcon = _hIcon;  return *this; }
	WindowData& InitializeCursor(HCURSOR _hCursor) { m_class.hCursor = _hCursor; return *this; }
private:
	WNDCLASS	  m_class;
	friend class  WindowManager;
};