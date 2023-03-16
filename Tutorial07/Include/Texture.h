#include "Prerrequisitos.h"
#include "Commons.h"
#pragma once

class
Device;

class 
Texture{
public:
	Texture() = default;
	~Texture() {};
	/*Sobrecarga de metodos que inicializa una 
	textura desde archivo y otra desde la textura en si
	*/
	void
		init(Device device, std::string TextureName);

	void
		init(Device device,
			unsigned int width,
			unsigned int heigth,
			DXGI_FORMAT Format,
			unsigned int Bindflags);

	void
		update();

	void
		render();

	void
		destroy();

public:
	//Variable de la textura
	ID3D11Texture2D* m_texture = nullptr;
	//Variable de textura de la imagen
	ID3D11ShaderResourceView* m_textureFromImg = nullptr;
};


