#include "pch.h"
#include "WindowManager.h"
#include "Window/Window/WindowContext.h"
#include "Window/Console/ConsoleContext.h"
#include "Window/DialogBox/DialogWindowContext.h"
#include "Application.h"


std::map<HWND, Engine::WindowBase*> WindowManager::m_hwndWindowTable = {};
std::map<std::wstring, Engine::WindowContext*> WindowManager::m_windows = {};
Engine::ConsoleContext*				WindowManager::m_activeConsole = nullptr;
Engine::WindowBase*		   		    WindowManager::m_focusWindow  = nullptr;
Engine::WindowContext*				    WindowManager::m_mainWindow = nullptr;

bool WindowManager::RegisterAndShowWindow(WindowData& _windowData)
{
	Engine::WindowContext* window = new Engine::WindowContext();
	window->m_class = std::move(_windowData.m_class);
	window->m_title = std::move(_windowData.m_title);
	window->m_class.lpszClassName = window->m_title;
	window->m_windowPosition = std::move(_windowData.m_windowPosition);
	window->m_windowSize = std::move(_windowData.m_windowSize);

	if (!RegisterClass(&window->m_class)) {
		SAFE_DELETE(window)
		return false;
	}

	RECT rect = { 0, 0
		, static_cast<LONG>(window->m_windowSize.x)
		, static_cast<LONG>(window->m_windowSize.y) };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	const LONG width = rect.right - rect.left;
	const LONG height = rect.bottom - rect.top;

	HINSTANCE hInstance = *Engine::Application::Instance;

	window->m_handle = CreateWindow(
		window->m_title,
		window->m_title,
		WS_OVERLAPPEDWINDOW,
		rect.left, rect.top, width, height,
		NULL, NULL, hInstance, NULL);

	if (window->m_handle) 
	{
		if (!m_mainWindow) m_mainWindow = window;
		m_focusWindow = window;

		window->Initialize();

		ShowWindow(window->m_handle, SW_SHOWNORMAL);
		UpdateWindow(window->m_handle);
		
		m_hwndWindowTable.insert(std::make_pair(window->m_handle, window));
		m_windows.insert(std::make_pair(window->m_title, window));
		return true;
	}
	else
	{
		SAFE_DELETE(window)
		return false;
	}
}

bool WindowManager::RegisterAndShowConsole(ConsoleData& _consoleData)
{
	if (!m_activeConsole)
	{
		if (AllocConsole())
		{
			Engine::ConsoleContext* console = new Engine::ConsoleContext();
			SetConsoleTitleW(_consoleData.m_title);
			console->m_inputHandle = GetStdHandle(STD_INPUT_HANDLE);
			console->m_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			console->m_handle = GetConsoleWindow();
			m_activeConsole = console;
			return true;
		}
	}
	return false;
}

Window* WindowManager::GetMainWindow()
{
	if (m_mainWindow) return m_mainWindow;
	else return nullptr;
	
}

Engine::WindowBase* WindowManager::GetFocusWindow()
{
	if (m_focusWindow) return m_focusWindow;
	else return nullptr;
}

Window* WindowManager::GetWindow(const std::wstring& _title)
{
	auto windowIter = m_windows.find(_title);
	if (windowIter != m_windows.end())
	{
		return windowIter->second;
	}
	return nullptr;
}

Console* WindowManager::GetConsole()
{
	if (m_activeConsole) return m_activeConsole;
	else return nullptr;
}

LRESULT CALLBACK WindowManager::WinProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	Engine::WindowBase* handler = nullptr;
	auto windowIter = m_hwndWindowTable.find(_hwnd);
	if (windowIter != m_hwndWindowTable.end())
	{
		handler = windowIter->second;
	}
	switch (_msg)
	{
	case WM_CREATE:
		break;

	case WM_SIZE:
		if (handler)
		{
			RECT windowRect; GetWindowRect(_hwnd, &windowRect);
			handler->m_windowSize.x = static_cast<float>(windowRect.right - windowRect.left);
			handler->m_windowSize.y = static_cast<float>(windowRect.bottom - windowRect.top);
			Console::Log(L"Window Resizing (", handler->m_title, " - x : ", handler->m_windowSize.x,
				", y : ", handler->m_windowSize.y, ")\n");
		}
		break;

	case WM_MOVE:
		if (handler)
		{
			RECT windowRect; GetWindowRect(_hwnd, &windowRect);
			handler->m_windowPosition.x = static_cast<float>(windowRect.left);
			handler->m_windowPosition.y = static_cast<float>(windowRect.top);
			Console::Log(L"Window Moving (", handler->m_title, " - x : ", handler->m_windowPosition.x,
				", y : ", handler->m_windowPosition.y, ")\n");
		}
		break;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		if (_wParam == VK_MENU)
			return 0;
		break;

	case WM_SETFOCUS:
		if (handler)
		{
			m_focusWindow = handler;
			Console::Log("Window Forcus (", handler->m_title, ")\n");
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		Engine::Application::Quit();
		break;

	default:
		return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
	}
	return 0;
}

