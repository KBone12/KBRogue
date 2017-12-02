#include "door.hpp"

#include "curses_include.h"

#include "map.hpp"

using kb::rogue::Door;
using kb::rogue::Entity;

Door::Door(const std::shared_ptr<Map>& map, int x0, int y0, bool opened, bool horizontal)
	: Entity(map, '+', x0, y0, opened), horizontal(horizontal)
{}

void Door::initialize()
{
	if (passable)		mark = horizontal ? '-' : '|';
	else			mark = '+';
}

void Door::update(int)
{}

void Door::render()
{
	mvaddch(y + mapY0, x + mapX0, mark);
}

void Door::action()
{
	if (passable)
	{
		mark = '+';
		passable = false;
	}
	else
	{
		mark = horizontal ? '-' : '|';
		passable = true;
	}
}
