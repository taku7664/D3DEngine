#include "DemoApplication.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    DemoApplication App(hInstance);
    App.Initialize();
    App.Run();
    App.Release();
    return 0;
}