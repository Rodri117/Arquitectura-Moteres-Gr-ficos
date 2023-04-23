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


private:
	
	LARGE_INTEGER m_iCurrentTime;
	
	LARGE_INTEGER m_iLastTime;
	
	LARGE_INTEGER m_iTimerFrequency;

public:
	
	float m_fDeltaTime;
};

