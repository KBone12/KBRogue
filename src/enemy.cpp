#include "enemy.hpp"

#include <random>

#include "curses_include.h"

#include "collision.hpp"
#include "map.hpp"
#include "mob.hpp"
#include "player.hpp"

using kb::rogue::CollisionDetector;
using kb::rogue::CollisionType;
using kb::rogue::Enemy;

Enemy::Enemy(const std::shared_ptr<Map>& map, char mark, int x0, int y0)
	: Mob(map, mark, x0, y0, 10)
{
	std::random_device device;
	rand.seed(device());
}

void Enemy::initialize()
{
}

void Enemy::update(int delta)
{
	if (!active)	return;

	std::uniform_int_distribution<> rangedRandom(-1, 1);
	int targetX = x + rangedRandom(rand);
	int targetY = y + rangedRandom(rand);

	auto collision = CollisionDetector::collision(targetX, targetY, map);
	if (collision == CollisionType::NONE
			|| collision == CollisionType::ENTITY_PASSABLE)
	{
		x = targetX;
		y = targetY;
	}
	else if (collision == CollisionType::PLAYER)
	{
		map->getPlayer()->setHp(map->getPlayer()->getHp() - 1);
	}
}

void Enemy::render()
{
	mvaddch(y + mapY0, x + mapX0, mark);
}
