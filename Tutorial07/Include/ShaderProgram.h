#pragma once
#include "Prerrequisitos.h"
#include "InputLayout.h"

class Device;

class
ShaderProgram {
public:
	ShaderProgram() = default;
	~ShaderProgram() {};

	void
	init(Device device,
		std::string fileName,
		std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

	void
		update();

	void
		render();

	void
		destroy();

	HRESULT
		CompileShaderFronFile(char* szFileName,
			LPCSTR szEntryPoint,
			LPCSTR szShaderModel,
			ID3DBlob** ppBlobOut);


};