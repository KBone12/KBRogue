#ifndef _PLYER_HEADER_PP_KBROGUE_
#define _PLYER_HEADER_PP_KBROGUE_

#include <bitset>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

namespace kb
{
	namespace rogue
	{
		class KBRogue;

		class Player
		{
			public:
				Player(const KBRogue* kbRogue, int x0 = 0, int y0 = 0);
				~Player() noexcept;

				void keyInput(int key);
				void update(int delta);
				void render();

				int getX() const
				{
					return x;
				}

				int getY() const
				{
					return y;
				}

			private:
				const KBRogue* game;
				int x0, y0;		// origin
				int x, y;
				std::bitset<4> moveFlags;		// 0: left, 1: down, 2: up, 3: right
				std::shared_ptr<spdlog::logger> logger;
		};
	}
}

#endif /* _PLYER_HEADER_PP_KBROGUE_ */
