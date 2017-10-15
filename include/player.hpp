#ifndef _PLYER_HEADER_PP_KBROGUE_
#define _PLYER_HEADER_PP_KBROGUE_

#include <bitset>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "mob.hpp"

namespace kb
{
	namespace rogue
	{
		class KBRogue;

		class Player : public Mob
		{
			public:
				/**
				 * Throws a spdlog::spdlog_ex when spdlog can't initialize
				 *
				 * x0: player's initial position x
				 * y0: player's initial position y
				 */
				Player(KBRogue& game, char mark, int x0, int y0);
				virtual ~Player() = default;

				virtual void initialize() override;
				void keyInput(int key);
				virtual void update(int delta) override;
				virtual void render() override;

			private:
				std::shared_ptr<spdlog::logger> logger;
				std::bitset<4> moveFlags;		// 0: left, 1: down, 2: up, 3: right
		};
	}
}

#endif /* _PLYER_HEADER_PP_KBROGUE_ */
