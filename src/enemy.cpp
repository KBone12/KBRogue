#include "enemy.hpp"

#include "curses_include.h"

#include "collision.hpp"
#include "map.hpp"
#include "mob.hpp"

using kb::rogue::Enemy;

Enemy::Enemy(const std::shared_ptr<Map>& map, char mark, int x0, int y0)
	: Mob(map, mark, x0, y0)
{}

void Enemy::initialize()
{
}

void Enemy::update(int delta)
{
	if (!active)	return;

	if (!CollisionDetector::collision(x + 1, y, map))
	{
		++x;
	}
}

void Enemy::render()
{
	mvaddch(y + mapY0, x + mapX0, mark);
}
