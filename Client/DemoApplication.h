#pragma once
#include "../Engine/Application.h"

#define TITLE L"D3D_Test"
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 800;

class DemoApplication
	: public Engine::Application
{
public:
	DemoApplication(HINSTANCE _hinstance)
		: Engine::Application(_hinstance) {}

	virtual void Initialize() override;

	void InitializeWindow();
private:

};