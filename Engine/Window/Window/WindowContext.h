#pragma once
#include "Window.h"
#ifdef _D2D1_H_window
#include "Renderer/D2DRenderer.h"
#endif
#ifdef __d3d11_h__
#include "Renderer/D3DRenderer.h"
#endif

class Window;
class WindowManager;

namespace Engine
{
    class WindowContext final
        : public ::Window
    {
    public:
        WindowContext() = default;
        virtual ~WindowContext();

        void Initialize();

        Renderer::IRenderer* GetRenderer() const { return m_renderer; }
    private:
        WNDCLASS             m_class = {};
        Renderer::IRenderer* m_renderer = nullptr;

        friend class ::WindowManager;
    };
}
