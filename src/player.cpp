#include "player.hpp"

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "collision.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "herb.hpp"
#include "map.hpp"

using kb::rogue::CollisionDetector;
using kb::rogue::CollisionType;
using kb::rogue::Map;
using kb::rogue::Mob;
using kb::rogue::Player;

Player::Player(const std::shared_ptr<Map>& map, char mark, int x0, int y0)
	: Mob(map, mark, x0, y0, 10), logger(spdlog::get("logger"))
{
	items.push_back(std::make_shared<Herb>(10));
}

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
			{
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
			}
			break;
		case 'i':
			{
				int tmp = 0;
				mvprintw(0, 0, "何番目のアイテムを使用しますか？[0-%lu)", items.size());
				nocbreak();
				nodelay(stdscr, false);
				scanw("%d", &tmp);
				cbreak();
				nodelay(stdscr, true);
				if (tmp < static_cast<int>(items.size()))
				{
					items[tmp]->use({ sharedThis() });
					removeItem(items[tmp], 1);
				}
			}
			break;
	}
}

void Player::update(int)
{
	int targetX = x;
	int targetY = y;
	if (moveFlags[0])	--targetX;
	if (moveFlags[1])	++targetY;
	if (moveFlags[2])	--targetY;
	if (moveFlags[3])	++targetX;

	auto collision = CollisionDetector::collision(targetX, targetY, map);
	if (collision == CollisionType::NONE
			|| collision == CollisionType::ENTITY_PASSABLE)
	{
		x = targetX;
		y = targetY;
		SPDLOG_DEBUG(logger,
				"Player moved to ({0}, {1})", x, y);
	}
	else if (collision == CollisionType::ENEMY)
	{
		auto enemy = map->getEnemy(targetX, targetY);
		enemy->setHp(enemy->getHp() - 1);
	}

	moveFlags.reset();
}

void Player::render()
{
	mvaddch(y + mapY0, x + mapX0, '@');

#ifdef DEBUG
	mvprintw(0, 5, "Player={ hp: %d }", hp);
#endif
}

void Player::changeCurrentMap(const std::shared_ptr<Map>& map)
{
	SPDLOG_DEBUG(logger, "Player moved from the floor{0} to the floor{1}", this->map->getFloorNumber(), map->getFloorNumber());
	this->map = map;
}
