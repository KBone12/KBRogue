#include "mob.hpp"

#include "kb_rogue.hpp"
#include "map.hpp"

using kb::rogue::KBRogue;
using kb::rogue::Mob;

Mob::Mob(const std::shared_ptr<Map>& map, char mark, int x0, int y0)
	: map(map), mark(mark),
	mapX0(map->getX0()), mapY0(map->getY0()), x(x0), y(y0)
{}
