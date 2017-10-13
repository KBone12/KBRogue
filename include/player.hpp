#ifndef _PLYER_HEADER_PP_KBROGUE_
#define _PLYER_HEADER_PP_KBROGUE_

#include <bitset>
#include <memory>

#include "spdlog/spdlog.h"

namespace kb
{
	namespace rogue
	{
		class Player
		{
			public:
				Player();

				void keyInput(int key);
				void update(int delta);
				void render();

			private:
				int x, y;
				std::bitset<4> moveFlags;		// 0: left, 1: down, 2: up, 3: right
				std::shared_ptr<spdlog::logger> logger;
		};
	}
}

#endif /* _PLYER_HEADER_PP_KBROGUE_ */
