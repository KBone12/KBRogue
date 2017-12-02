#ifndef _ENEMY_HEADER_PP_KBROGUE_
#define _ENEMY_HEADER_PP_KBROGUE_

#include <random>

#include "mob.hpp"

namespace kb
{
	namespace rogue
	{
		class Enemy : public Mob
		{
			public:
				/**
				 * x0: entity's initial position x in map coordinate system
				 * y0: entity's initial position y in map coordinate system
				 */
				Enemy(const std::shared_ptr<Map>& map, char mark, int x0, int y0);
				virtual ~Enemy() = default;

				virtual void initialize() override;
				virtual void update(int delta) override;
				virtual void render() override;

				bool isActive() const
				{
					return active;
				}

				void setActive(bool active)
				{
					this->active = active;
				}

			private:
				std::mt19937 rand;
				bool active;
		};
	}
}

#endif /* _ENEMY_HEADER_PP_KBROGUE_ */
