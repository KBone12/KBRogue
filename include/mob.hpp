#ifndef _MOB_HEADER_PP_KBROGUE_
#define _MOB_HEADER_PP_KBROGUE_

#include <memory>

namespace kb
{
	namespace rogue
	{
		class Map;

		class Mob
		{
			public:
				/**
				 * x0: entity's initial position x in map coordinate system
				 * y0: entity's initial position y in map coordinate system
				 */
				Mob(const std::shared_ptr<Map>& map, char mark, int x0, int y0);
				virtual ~Mob() = default;

				virtual void initialize() = 0;
				virtual void update(int delta) = 0;
				virtual void render() = 0;

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

			protected:
				std::shared_ptr<Map> map;
				char mark;
				int mapX0, mapY0;		// origin
				int x, y;
		};
	}
}

#endif /* _MOB_HEADER_PP_KBROGUE_ */
