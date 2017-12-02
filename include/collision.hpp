#ifndef _COLLISION_HEADER_PP_KBROGUE_
#define _COLLISION_HEADER_PP_KBROGUE_

#include <memory>

namespace kb
{
	namespace rogue
	{
		class Map;

		enum struct CollisionType
		{
			UNKNOWN,
			NONE,
			WALL,
			ENTITY_PASSABLE,
			ENTITY_NOT_PASSABLE,
			PLAYER,
			ENEMY
		};

		class CollisionDetector
		{
			public:
				static CollisionType collision(const int x, const int y, const std::shared_ptr<Map>& map);
		};
	}
}

#endif /* _COLLISION_HEADER_PP_KBROGUE_ */
