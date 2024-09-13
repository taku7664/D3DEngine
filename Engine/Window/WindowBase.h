#pragma once

class WindowManager;

namespace Engine
{
	class WindowBase
	{
	public:
		virtual ~WindowBase();

		void SetWindowPosition(Vector2 _position);
		void SetWindowSize(Vector2 _size);

		const WCHAR*  GetWindowTitle()	  const { return m_title; }
		Vector2		  GetWindowSize()	  const { return m_windowSize; }
		Vector2		  GetWindowPosition() const { return m_windowPosition; }
	protected:
		WindowBase();
		const WCHAR*  m_title;
		Vector2       m_windowPosition;
		Vector2       m_windowSize;
		HWND		  m_handle;
	private:
	public:
		void SetPositionCenter();
		void SetFocus();
		operator HWND() { return m_handle; }
		friend class WindowManager;
	};
}