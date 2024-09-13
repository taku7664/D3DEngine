#pragma once
#include "Window/WindowBase.h"
#include "Window/WindowDataBase.h"
#include "Manager/WindowManager.h"

class Console : public Engine::WindowBase
{
public:
    Console();
    virtual ~Console();
protected:
	HANDLE m_outputHandle;
	HANDLE m_inputHandle;
private:
public:
    template<typename... Args>
	static void Log(Args&&... args);
};

class ConsoleData : public Engine::WindowDataBase
{
public:
private:
	friend class WindowManager;
};

template<typename... Args>
static void Console::Log(Args&&... args)
{
    if (WindowManager::IsActiveConsole())
    {
        HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (outputHandle != INVALID_HANDLE_VALUE)
        {
            // ���� ���ڸ� ó���ϴ� wstringstream ���
            std::wstringstream wss;
            (wss << ... << args);  // fold expression�� ����� ���� ���� ��Ʈ���� ���

            std::wstring logMessage = wss.str();
            DWORD charsWritten = 0;

            // ��ȯ�� ���ڿ� ���
            WriteConsoleW(outputHandle, logMessage.c_str(), static_cast<DWORD>(logMessage.size()), &charsWritten, nullptr);
        }
    }
}