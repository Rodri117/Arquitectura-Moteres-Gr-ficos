#include "RTime.h"

RTime::RTime()
{
	m_currentTime;
	m_lastTime;
	m_timerFrequency;
}

RTime::~RTime(){
}

void RTime::init(){
	//Se ajusta a la pantalla
	QueryPerformanceCounter(&m_lastTime);
	QueryPerformanceFrequency(&m_timerFrequency);
}

void RTime::uptade(){
	QueryPerformanceCounter(&m_currentTime);
	m_deltaTime = (m_currentTime.QuadPart - m_lastTime.QuadPart) / (float)m_timerFrequency.QuadPart;
	m_lastTime = m_currentTime;
	m_deltaTime = min(m_deltaTime, 0.1f);
}

void RTime::render(){

}

void RTime::destroy(){

}
