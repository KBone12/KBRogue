#ifndef _MAP_HEADER_PP_KBROGUE_
#define _MAP_HEADER_PP_KBROGUE_

#include <string>
#include <vector>

namespace kb
{
	namespace rogue
	{
		class Map
		{
			public:
				Map(int x0, int y0);

				void initialize(const std::string& filePath = "resouce/map/test");
				void render();

				const std::vector<std::vector<int>>& getCollisionData() const
				{
					return collisionData;
				}

				int getX0() const
				{
					return x0;
				}

				int getY0() const
				{
					return y0;
				}

			private:
				std::vector<std::string> data;
				/*
				 * -1: Wall
				 *  0: Floor
				 *  1: Closed Door
				 */
				std::vector<std::vector<int>> collisionData;
				int x0, y0;		// origin
				int height;
		};
	}
}

#endif /* _MAP_HEADER_PP_KBROGUE_ */
