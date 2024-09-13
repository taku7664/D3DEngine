#include "pch.h"
#include "Window.h"
#include "Manager/WindowManager.h"
#include "Application.h"

Window::~Window()
{
}

WindowData::WindowData()
	: m_class({})
{
	m_class.style = CS_HREDRAW | CS_VREDRAW;
	m_class.lpfnWndProc = WindowManager::WinProc;
	m_class.cbClsExtra = NULL;
	m_class.cbWndExtra = NULL;
	m_class.hInstance = *Engine::Application::Instance;
	m_class.hIcon = LoadIcon(*Engine::Application::Instance, IDI_APPLICATION);
	m_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	m_class.lpszMenuName = NULL;
	m_class.lpszClassName = L"Project";
}