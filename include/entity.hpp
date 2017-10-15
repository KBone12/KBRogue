#ifndef _ENTITY_HEADER_PP_KBROGUE_
#define _ENTITY_HEADER_PP_KBROGUE_

namespace kb
{
	namespace rogue
	{
		class KBRogue;

		class Entity
		{
			public:
				/**
				 * x0: entity's initial position x
				 * y0: entity's initial position y
				 */
				Entity(KBRogue& game, char mark, int x0, int y0, bool passable);
				virtual ~Entity() = default;

				virtual void initialize();
				virtual void update() = 0;
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
				KBRogue& game;
				char mark;
				int x, y;
				int mapX0, mapY0;	// origin
				bool passable;
		};
	}
}

#endif /* _ENTITY_HEADER_PP_KBROGUE_ */
