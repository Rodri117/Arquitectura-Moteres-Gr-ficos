#include "Prerrequisitos.h"
#include "Commons.h"
#pragma once

class
Transform {
public:
	Transform() = default;
	~Transform() {};
	//inicializa el Transform
	void
	init();

	void
	ubdate();

	void
	render();

	void
	destroy();

public:
	Vector3 m_v3Position;
	float m_fScaleNum;
	float m_fRotateNum;
	float m_fSpeed;
};
