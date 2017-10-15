#ifndef _MOB_HEADER_PP_KBROGUE_
#define _MOB_HEADER_PP_KBROGUE_

namespace kb
{
	namespace rogue
	{
		class KBRogue;

		class Mob
		{
			public:
				/**
				 * x0: entity's initial position x
				 * y0: entity's initial position y
				 */
				Mob(KBRogue& game, char mark, int x0, int y0);
				virtual ~Mob() = default;

				virtual void initialize();
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
				KBRogue& game;
				char mark;
				int x, y;
				int mapX0, mapY0;		// origin
		};
	}
}

#endif /* _MOB_HEADER_PP_KBROGUE_ */
