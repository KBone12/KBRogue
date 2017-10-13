#include "timer.hpp"

#include <chrono>

#include "curses_include.h"

using kb::rogue::FpsTimer;

FpsTimer::FpsTimer(int fps) : fps(fps)
{}

void FpsTimer::start()
{
	sleepTime = 1000 / fps;
	remainder = 1000 % fps;
	delta = 0;
	counter = 0;

	t2 = t3 = std::chrono::high_resolution_clock::now();
}

void FpsTimer::update()
{
	t1 = std::chrono::high_resolution_clock::now();
	delta = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t2).count();

	time_sum += std::chrono::milliseconds(delta);
	if (++counter == fps)
	{
		measuredFps = (double)fps / time_sum.count() * 1000;
		counter = 0;
		time_sum = std::chrono::milliseconds(0);
	}
}

void FpsTimer::sleep()
{
	t2 = std::chrono::high_resolution_clock::now();
	sleepTime -= std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t3).count();
	napms(sleepTime);
	t3 = std::chrono::high_resolution_clock::now();
	remainder -= std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() - sleepTime;
	sleepTime = (1000 + remainder) / fps;
	remainder = (1000 + remainder) % fps;
}
