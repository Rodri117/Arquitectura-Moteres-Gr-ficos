#include "RTime.h"

RTime::RTime()
{
	m_iCurrentTime;
	m_iLastTime;
	m_iTimerFrequency;
}

RTime::~RTime(){
}

void RTime::init(){
	//Se ajusta a la pantalla
	QueryPerformanceCounter(&m_iLastTime);
	QueryPerformanceFrequency(&m_iTimerFrequency);
}

void RTime::uptade(){
	QueryPerformanceCounter(&m_iCurrentTime);
	m_fDeltaTime = (m_iCurrentTime.QuadPart - m_iLastTime.QuadPart) / (float)m_iTimerFrequency.QuadPart;
	m_iLastTime = m_iCurrentTime;
	m_fDeltaTime = min(m_fDeltaTime, 0.1f);
}

void RTime::render(){

}

void RTime::destroy(){

}
