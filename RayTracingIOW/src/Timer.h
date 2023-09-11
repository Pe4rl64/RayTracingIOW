#pragma once

#include <chrono>
#include <ratio>
#include <iostream>

class Timer
{
public:
	Timer()
	{
		m_start = std::chrono::steady_clock::now();
	}

	~Timer()
	{
		m_end = std::chrono::steady_clock::now();
		std::cout << "[DEBUG TIMER]: " <<  m_end - m_start << " elapsed.\n";
	}
private:
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<float, std::milli>> m_start, m_end;
};