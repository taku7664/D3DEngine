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
            // 가변 인자를 처리하는 wstringstream 사용
            std::wstringstream wss;
            (wss << ... << args);  // fold expression을 사용해 가변 인자 스트림에 출력

            std::wstring logMessage = wss.str();
            DWORD charsWritten = 0;

            // 변환된 문자열 출력
            WriteConsoleW(outputHandle, logMessage.c_str(), static_cast<DWORD>(logMessage.size()), &charsWritten, nullptr);
        }
    }
}