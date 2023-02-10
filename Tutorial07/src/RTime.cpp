#include "RTime.h"

RTime::RTime()
{
}

RTime::~RTime()
{
}

void RTime::init()
{
	QueryPerformanceCounter(&m_lastTime);
	QueryPerformanceFrequency(&m_timerFrequency);
}

void RTime::uptade()
{
	QueryPerformanceCounter(&m_currentTime);
	float deltaTime = (m_currentTime.QuadPart - m_lastTime.QuadPart) / (float)m_timerFrequency.QuadPart;
	m_lastTime = m_currentTime;
	deltaTime = min(deltaTime, 0.1f);
}

void RTime::render()
{
}

void RTime::destroy()
{
}
