#include "pch.h"
#include "WindowContext.h"
#include "Manager/WindowManager.h"

namespace Engine
{
	WindowContext::~WindowContext()
	{
	}
	void WindowContext::Initialize()
	{
#ifdef _D2D1_H_
		m_renderer = new Renderer::D2DRenderer();
#endif
#ifdef __d3d11_h__
		m_renderer = new Renderer::D3DRenderer();
#endif
		m_renderer->Initialize(this);
		SetPositionCenter();
	}
}