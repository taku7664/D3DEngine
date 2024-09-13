#include "pch.h"
#include "WindowBase.h"

namespace Engine
{
	WindowBase::WindowBase() : m_handle(nullptr), m_title(L""), m_windowPosition({}), m_windowSize({})
	{
	}
	WindowBase::~WindowBase()
	{
		GameManager::window->m_hwndWindowTable.erase(m_handle);
		DestroyWindow(m_handle);
	}
	void WindowBase::SetWindowPosition(Vector2 _position)
	{
		MoveWindow(m_handle
			, static_cast<int>(_position.x)
			, static_cast<int>(_position.y)
			, static_cast<int>(m_windowSize.x)
			, static_cast<int>(m_windowSize.y)
			, TRUE);
	}
	void WindowBase::SetWindowSize(Vector2 _size)
	{
		SetWindowPos(m_handle
			, HWND_TOP
			, static_cast<int>(m_windowPosition.x)
			, static_cast<int>(m_windowPosition.y)
			, static_cast<int>(_size.x)
			, static_cast<int>(_size.y)
			, SWP_NOMOVE);
	}
	void WindowBase::SetPositionCenter()
	{
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		RECT windowRect;
		GetWindowRect(m_handle, &windowRect);

		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		SetWindowPos(m_handle, NULL,
			(screenWidth - windowWidth) / 2,
			(screenHeight - windowHeight) / 2,
			0, 0, SWP_NOZORDER | SWP_NOSIZE
		);
	}
	void WindowBase::SetFocus()
	{
		::SetFocus(m_handle);
	}
}
          