#include "player.hpp"

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "collision.hpp"
#include "entity.hpp"
#include "map.hpp"

using kb::rogue::Map;
using kb::rogue::Mob;
using kb::rogue::Player;

Player::Player(const std::shared_ptr<Map>& map, char mark, int x0, int y0)
	: Mob(map, mark, x0, y0), logger(spdlog::get("logger"))
{}

void Player::initialize()
{
	SPDLOG_DEBUG(logger, "Player initialized.");
}

void Player::keyInput(int key)
{
	switch (key)
	{
		case 'h':
			moveFlags[0] = true;
			break;
		case 'j':
			moveFlags[1] = true;
			break;
		case 'k':
			moveFlags[2] = true;
			break;
		case 'l':
			moveFlags[3] = true;
			break;
		case 'y':
			moveFlags[0] = true;
			moveFlags[2] = true;
			break;
		case 'u':
			moveFlags[3] = true;
			moveFlags[2] = true;
			break;
		case 'b':
			moveFlags[0] = true;
			moveFlags[1] = true;
			break;
		case 'n':
			moveFlags[3] = true;
			moveFlags[1] = true;
			break;
		case 'o':		// open the door
			mvaddstr(0, 0, "開けるドアの方向を入力してください。");
			nodelay(stdscr, false);
			char direction = getch();
			int targetX = x, targetY = y;
			switch (direction)
			{
				case 'h':
					--targetX;
					break;
				case 'j':
					++targetY;
					break;
				case 'k':
					--targetY;
					break;
				case 'l':
					++targetX;
					break;
				case 'y':
					--targetX;
					--targetY;
					break;
				case 'u':
					++targetX;
					--targetY;
					break;
				case 'b':
					--targetX;
					++targetY;
					break;
				case 'n':
					++targetX;
					++targetY;
					break;
			}
			nodelay(stdscr, true);
			if (map->getCollisionData()
					.at(targetY + 1).at(targetX + 1) == Map::H_DOOR
				|| map->getCollisionData()
					.at(targetY + 1).at(targetX + 1) == Map::V_DOOR
				)
			{
				if (!map->getEntity(targetX, targetY)->isPassable())
				{
					map->getEntity(targetX, targetY)->action();
				}
			}
			break;
	}
}

void Player::update(int)
{
	if (moveFlags[0]
			&& !CollisionDetector::collision(x - 1, y, map))
	{
		--x;
	}
	if (moveFlags[1]
			&& !CollisionDetector::collision(x, y + 1, map))
	{
		++y;
	}
	if (moveFlags[2]
			&& !CollisionDetector::collision(x, y - 1, map))
	{
		--y;
	}
	if (moveFlags[3]
			&& !CollisionDetector::collision(x + 1, y, map))
	{
		++x;
	}

	if (moveFlags.any())
	{
		SPDLOG_DEBUG(logger,
				"Player moved to ({0}, {1})", x, y);
	}
	moveFlags.reset();
}

void Player::render()
{
	mvaddch(y + mapY0, x + mapX0, '@');
}

void Player::changeCurrentMap(const std::shared_ptr<Map>& map)
{
	SPDLOG_DEBUG(logger, "Player moved from the floor{0} to the floor{1}", this->map->getFloorNumber(), map->getFloorNumber());
	this->map = map;
}
