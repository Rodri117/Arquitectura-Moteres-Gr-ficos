#include <Windows.h>
#pragma once

class 
RTime{
public:
	RTime();
	~RTime();

	void 
	init();

	void 
	uptade();

	void 
	render();

	void 
	destroy();


	float m_deltaTime;

private:
	
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_lastTime;
	LARGE_INTEGER m_timerFrequency;

public: 
	float m_deltaTime;
};

