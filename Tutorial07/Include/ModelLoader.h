#pragma once
#include "Prerrequisitos.h"
#include "Commons.h"

class 
ModelLoader {
public:
	ModelLoader() = default;
	~ModelLoader() {};

	void
		init();

	void
		update();

	void
		render();

	void
		destroy();

	LoadData
		load(std::string objFileName);
};