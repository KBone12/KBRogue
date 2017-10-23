#ifndef _ENTITY_HEADER_PP_KBROGUE_
#define _ENTITY_HEADER_PP_KBROGUE_

#include <memory>

namespace kb
{
	namespace rogue
	{
		class Map;

		class Entity
		{
			public:
				/**
				 * x0: entity's initial position x in map coordinate system
				 * y0: entity's initial position y in map coordinate system
				 */
				Entity(const std::shared_ptr<Map>& map, char mark, int x0, int y0, bool passable);
				virtual ~Entity() = default;

				virtual void initialize() = 0;
				virtual void update(int delta) = 0;
				virtual void render() = 0;
				virtual void action() = 0;

				char getMark() const
				{
					return mark;
				}

				int getX() const
				{
					return x;
				}

				int getY() const
				{
					return y;
				}

				bool isPassable() const
				{
					return passable;
				}

			protected:
				std::shared_ptr<Map> map;
				char mark;
				int x, y;
				int mapX0, mapY0;
				bool passable;
		};
	}
}

#endif /* _ENTITY_HEADER_PP_KBROGUE_ */
