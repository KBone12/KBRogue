#ifndef _TIMER_HEADER_PP_KBROGUE_
#define _TIMER_HEADER_PP_KBROGUE_

#include <chrono>

namespace kb
{
	namespace rogue
	{
		class FpsTimer
		{
			public:
				FpsTimer(int fps);

				void start();
				void update();
				void sleep();

				int getDelta() const
				{
					return delta;
				}

				double getFps() const
				{
					return measuredFps;
				}

			private:
				const int fps;
				std::chrono::high_resolution_clock::time_point t1, t2, t3;
				int sleepTime, remainder, delta;
				int counter;
				std::chrono::milliseconds time_sum;
				double measuredFps;
		};
	}
}

#endif /* _TIMER_HEADER_PP_KBROGUE_ */
