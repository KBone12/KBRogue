#include "mob.hpp"

#include "kb_rogue.hpp"
#include "map.hpp"

using kb::rogue::KBRogue;
using kb::rogue::Mob;

Mob::Mob(KBRogue& game, char mark, int x0, int y0)
	: game(game), mark(mark), x(x0), y(y0)
{
}

void Mob::initialize()
{
	mapX0 = game.getCurrentMap()->getX0();
	mapY0 = game.getCurrentMap()->getY0();
}
