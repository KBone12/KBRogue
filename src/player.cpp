#include "player.hpp"

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "collision.hpp"
#include "kb_rogue.hpp"
#include "map.hpp"

using kb::rogue::Mob;
using kb::rogue::Player;

Player::Player(KBRogue& game, char mark, int x0, int y0) : Mob(game, mark, x0, y0), logger(spdlog::get("logger"))
{}

void Player::initialize()
{
	Mob::initialize();
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
	}
}

void Player::update(int)
{
	if (moveFlags[0]
			&& !CollisionDetector::collision(x - mapX0 - 1, y - mapY0,
				game.getCurrentMap()))
	{
		--x;
	}
	if (moveFlags[1]
			&& !CollisionDetector::collision(x - mapX0, y - mapY0 + 1,
				game.getCurrentMap()))
	{
		++y;
	}
	if (moveFlags[2]
			&& !CollisionDetector::collision(x - mapX0, y - mapY0 - 1,
				game.getCurrentMap()))
	{
		--y;
	}
	if (moveFlags[3]
			&& !CollisionDetector::collision(x - mapX0 + 1, y - mapY0,
				game.getCurrentMap()))
	{
		++x;
	}

	if (moveFlags.any())
	{
		SPDLOG_DEBUG(logger,
				"Player moves to ({0}, {1})", x - mapX0, y - mapY0);
	}
	moveFlags.reset();
}

void Player::render()
{
	mvaddch(y, x, '@');
}
