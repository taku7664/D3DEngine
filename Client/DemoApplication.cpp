#include "DemoApplication.h"
#include "World/TestWorld_01.h"

void DemoApplication::Initialize()
{
	InitializeWindow();
}

void DemoApplication::InitializeWindow()
{
	WindowData  mainWindow;
	WindowData  subWindow;
	ConsoleData console;

	mainWindow.
		InitializeTitle(TITLE).
		InitializeSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	subWindow.
		InitializeTitle(L"SubWindow").
		InitializeSize(800, 600);

	console.
	InitializeTitle(TITLE).
	InitializeSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	GameManager::window->RegisterAndShowWindow(mainWindow);

	GameManager::window->GetMainWindow()->SetWindowSize(Vector2(1000,1000));

	GameManager::world->CreateWorld<TestWorld_01>(L"Test_01", L"default");
}