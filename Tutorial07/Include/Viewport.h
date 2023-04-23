#include "Prerrequisitos.h"
#pragma once

class
	Window;

class
	DeviceContext;

class
Viewport {
public:
	Viewport() = default;
	~Viewport() {};
	//crea la estructua del viewport
	void
		init(Window window);

	void
		update();
	
	void
		render(DeviceContext& deviceContext);

	void
		destroy();

public:
	D3D11_VIEWPORT m_viewport;
};