#pragma once
#include "WorldManager.h"
#include "WindowManager.h"
#include "Window/Window/WindowContext.h"
#include "Window/Console/ConsoleContext.h"
#include "Window/DialogBox/DialogWindowContext.h"


class GameManager
{
	/*class WindowManager
	{
	public:
		Console* GetConsole() { return WindowManager::GetConsole(); }
		Window* GetMainWindow() { return WindowManager::GetMainWindow(); }
		Window* GetWindow(const std::wstring& _name) { return WindowManager::GetWindow(_name); }
	};*/
public:
	// FixedUpdate가 호출되는 간격
	static float fixedTick;

	static WorldManager*  world;
	static WindowManager* window;
private:
	
};

