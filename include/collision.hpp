#ifndef _COLLISION_HEADER_PP_KBROGUE_
#define _COLLISION_HEADER_PP_KBROGUE_

#include <memory>

namespace kb
{
	namespace rogue
	{
		class Map;

		class CollisionDetector
		{
			public:
				static bool collision(const int x, const int y, const std::shared_ptr<Map>& map);
		};
	}
}

#endif /* _COLLISION_HEADER_PP_KBROGUE_ */
