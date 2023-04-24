#include "Prerrequisitos.h"
#pragma once

class
Device;

class 
DeviceContext;

class
Window;

class
Texture;

class
SwapChain {
public:
	SwapChain() = default;
	~SwapChain() {};
	//da contexto al backbuffer
	void
		init(Device& device,
			DeviceContext& deviceContext,
			Texture& backBuffer,
			Window window);

	void
		update();
	
	void
		render();

	void
		destroy();
	//Se ve informacion en pantalla
	void
		present();


private:
	D3D_DRIVER_TYPE m_drievrType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	IDXGISwapChain* m_swapChain = nullptr;
};
