#include "Prerrequisitos.h"
#pragma once

// Estructura

struct SimpleVertex{

	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

struct Camera{

	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};

struct Vector3 {

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};