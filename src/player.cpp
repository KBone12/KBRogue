#include "player.hpp"

#include "curses_include.h"
#include "spdlog/spdlog.h"

using kb::rogue::Player;

Player::Player() : x(0), y(0), logger(spdlog::get("logger"))
{}

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

void Player::update(int delta)
{
	if (moveFlags[0])	--x;
	if (moveFlags[1])	++y;
	if (moveFlags[2])	--y;
	if (moveFlags[3])	++x;

	if (moveFlags.any())
	{
		SPDLOG_DEBUG(logger, "Player moves to ({0}, {1})", x, y);
	}

	moveFlags.reset();
}

void Player::render()
{
	mvaddch(y, x, '@');
}
