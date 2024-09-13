#pragma once

class Window;
class Console;
class DialogWindow;
class WindowData;
class ConsoleData;
class DialogWindowData;
namespace Engine
{
	class WindowBase;
	class WindowContext;
	class ConsoleContext;
	class DialogWindowContext;
}

class WindowManager
{
public:
	static bool RegisterAndShowWindow(WindowData& _windowData);
	static bool RegisterAndShowConsole(ConsoleData& _consoleData);
	static bool IsActiveConsole() { return m_activeConsole != nullptr; }

	static Window* GetWindow(const std::wstring& _title);
	static Window*		 GetMainWindow();
	static Engine::WindowBase*   GetFocusWindow();
	static Console* GetConsole();
	// Proc
	static LRESULT CALLBACK WinProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
private:
	static Engine::WindowBase*				   m_focusWindow;
	static Engine::WindowContext*				   m_mainWindow;
	static Engine::ConsoleContext*			       m_activeConsole;

	static std::map<HWND, Engine::WindowBase*> m_hwndWindowTable;
	static std::map<std::wstring, Engine::WindowContext*> m_windows;

	friend Engine::WindowBase;
};
