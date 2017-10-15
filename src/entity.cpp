#include "entity.hpp"

#include "kb_rogue.hpp"
#include "map.hpp"

using kb::rogue::Entity;
using kb::rogue::KBRogue;

Entity::Entity(KBRogue& game, char mark, int x0, int y0, bool passable)
	: game(game), mark(mark), x(x0), y(y0), passable(passable)
{
}

void Entity::initialize()
{
	mapX0 = game.getCurrentMap()->getX0();
	mapY0 = game.getCurrentMap()->getY0();
}
