#pragma once

namespace Engine
{
	class WindowDataBase
	{
	public:
		WindowDataBase() = default;
		virtual ~WindowDataBase() = default;

		WindowDataBase& InitializeTitle(const WCHAR* _title) { m_title = _title; return *this; }
		WindowDataBase& InitializePosition(int _x, int _y) { m_windowPosition.x = (float)_x; m_windowPosition.y = (float)_y;  return *this; }
		WindowDataBase& InitializeSize(int _x, int _y) { m_windowSize.x = (float)_x; m_windowSize.y = (float)_y;  return *this; }
	protected:
		const WCHAR*  m_title = L"";
		Vector2       m_windowPosition = { 0,0 };
		Vector2       m_windowSize = { 0,0 };
	};
}