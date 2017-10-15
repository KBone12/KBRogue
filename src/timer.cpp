#include "timer.hpp"

#include <chrono>

#include "curses_include.h"

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using kb::rogue::FpsTimer;

FpsTimer::FpsTimer(int fps) : fps(fps)
{}

void FpsTimer::start()
{
	sleepTime = 1000 / fps;
	remainder = 1000 % fps;
	delta = 0;
	sleepDelta = 0;
	counter = 0;

	t2 = t3 = t4 = high_resolution_clock::now();
}

void FpsTimer::update()
{
	t4 = t1;
	t1 = high_resolution_clock::now();
	delta = duration_cast<milliseconds>(t1 - t4).count();

	// Calculate the number of frames per second
	time_sum += milliseconds(delta);
	if (++counter == fps)
	{
		measuredFps = (double)fps / time_sum.count() * 1000;
		counter = 0;
		time_sum = milliseconds(0);
	}
}

void FpsTimer::sleep()
{
	t2 = high_resolution_clock::now();
	sleepTime -= duration_cast<milliseconds>(t2 - t3).count() + sleepDelta;
	if (sleepTime > 0)	napms(sleepTime);

	t3 = high_resolution_clock::now();
	sleepDelta = duration_cast<milliseconds>(t3 - t2).count() - sleepTime;
	sleepTime = (1000 + remainder) / fps;
	remainder = (1000 + remainder) % fps;
}
