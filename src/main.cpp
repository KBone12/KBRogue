#include <clocale>
#include <iostream>

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "kb_rogue.hpp"

int main(int, char**)
try
{
	spdlog::set_async_mode(8192);
	kb::rogue::KBRogue game;
	game.initialize();
	game.start();

	return 0;
}
catch (const spdlog::spdlog_ex& e)
{
	std::cerr << "spdlog can't initialize: " << e.what() << std::endl;
	return 1;
}
