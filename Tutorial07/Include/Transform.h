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
	
	Vector3 	m_v3Position;
	float		m_fScaleNum;
	Vector3		m_v3Scale;
	float		m_fRotateNum;
	Vector3		m_v3Rotate;
	float		m_fSpeed;
};
