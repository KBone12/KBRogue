#include <clocale>
#include <iostream>

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "player.hpp"

int main(int, char**)
try
{
	spdlog::set_async_mode(8192);
	auto log = spdlog::rotating_logger_mt("log", "logs/log", 1024 * 1024 * 2, 5);
#ifdef DEBUG
	log->set_level(spdlog::level::debug);
#endif

	std::setlocale(LC_ALL, "");		// For non-ascii characters
	SPDLOG_DEBUG(log, "Set environment variables 'LC_ALL' to \"\".");

	log->info("Initalization phase.");
	SPDLOG_DEBUG(log, "Start ncurses initializing.");
	initscr();
	cbreak();					// Set to raw mode
	noecho();
	curs_set(false);			// Hide cursor
	nodelay(stdscr, true);
	intrflush(stdscr, false);
	keypad(stdscr, true);
	ESCDELAY = 25;
	SPDLOG_DEBUG(log, "Completed ncurses initializing.");

	log->info("Start game loop.");
	bool quit = false;
	int x = 0, y = 0;
	int c;
	kb::rogue::Player player;

	while (!quit)
	{
		clear();

		while ((c = getch()) != ERR)
		{
			switch (c)
			{
				case 'q':
				case 'Q':
					quit = true;
					break;
			}

			player.keyInput(c);
		}

		player.update(0);

		player.render();

		refresh();

		napms(16);
	}

	log->info("Finalization phase.");
	endwin();
	SPDLOG_DEBUG(log, "Ncurses Finalized.");

	spdlog::drop_all();

	return 0;
}
catch (const spdlog::spdlog_ex& e)
{
	std::cerr << "spdlog can't initialize: " << e.what() << std::endl;
	return 1;
}
