#include <clocale>
#include <iostream>

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "kb_rogue.hpp"

int main(int, char**)
try
{
	// Initialize spdlog (asynchronization mode, write to logs/log)
	spdlog::set_async_mode(8192);
	auto logger = spdlog::rotating_logger_mt("logger", "logs/log", 1024 * 1024 * 2, 5);
	logger->info("Set spdlog to asynchronization mode.");
#ifdef DEBUG
	logger->set_level(spdlog::level::debug);
	logger->info("DEBUG MODE!");
#endif

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
