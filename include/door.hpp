#ifndef _DOOR_HEADER_PP_KBROGUE_
#define _DOOR_HEADER_PP_KBROGUE_

#include <memory>

#include "entity.hpp"

namespace kb
{
	namespace rogue
	{
		class Map;

		class Door : public Entity
		{
			public:
				Door(const std::shared_ptr<Map>& game, int x0, int y0, bool opened, bool horizontal);
				virtual ~Door() = default;

				virtual void initialize() override;
				virtual void update(int delta) override;
				virtual void render() override;
				virtual void action() override;

			private:
				bool horizontal;
		};
	}
}

#endif /* _DOOR_HEADER_PP_KBROGUE_ */
