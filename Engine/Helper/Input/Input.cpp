#include "pch.h"
#include "Input.h"
#include "Window/Console/ConsoleContext.h"

Key* Input::m_key = nullptr;
Mouse* Input::m_mouse = nullptr;

void Input::Initialize()
{
	m_key = new Key();
	m_mouse = new Mouse();
	m_mouse->Initialize();
}

void Input::Update()
{
	m_key->Update();
	m_mouse->Update();
}

void Input::Reset()
{
	m_key->Reset();
	m_mouse->Reset();
}

bool Input::IsMouseDown(int _mouseType)
{
	return m_mouse->IsMouseDown(_mouseType);
}

bool Input::IsMouseHold(int _mouseType)
{
	return m_mouse->IsMouseHold(_mouseType);
}

bool Input::IsMouseUp(int _mouseType)
{
	return m_mouse->IsMouseUp(_mouseType);
}
