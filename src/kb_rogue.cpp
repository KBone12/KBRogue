#include "kb_rogue.hpp"

#include <chrono>

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "map.hpp"
#include "player.hpp"
#include "timer.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using kb::rogue::KBRogue;

KBRogue::KBRogue() : logger(spdlog::rotating_logger_mt("logger", "logs/log", 1024 * 1024 * 2, 5))
{
#ifdef DEBUG
	logger->set_level(spdlog::level::debug);
#endif
}

void KBRogue::initialize()
{
	logger->info("Initalization phase.");
	std::setlocale(LC_ALL, "");		// For non-ascii characters
	SPDLOG_DEBUG(logger, "Set environment variables 'LC_ALL' to \"\".");

	SPDLOG_DEBUG(logger, "Start ncurses initializing.");
	initscr();
	cbreak();					// Set to raw mode
	noecho();
	curs_set(false);			// Hide cursor
	nodelay(stdscr, true);
	intrflush(stdscr, false);
	keypad(stdscr, true);
	ESCDELAY = 25;
	SPDLOG_DEBUG(logger, "Completed ncurses initializing.");
}

void KBRogue::start()
{
	logger->info("Start game loop.");
	bool quit = false;
	int c;
	kb::rogue::FpsTimer fps(30);
	maps.push_back(std::make_shared<Map>(1, 1));
	currentMap = maps.at(0);
	kb::rogue::Player player(this, 2, 2);

	currentMap->initialize("resource/map/map0");

	fps.start();
	while (!quit)
	{
		/*
		 * Key inputs
		 */
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

		fps.update();
		player.update(fps.getDelta());

		clear();
		currentMap->render();
		player.render();

#ifdef DEBUG
		mvprintw(0, 0, "%.1f", fps.getFps());
#endif /* DEBUG */

		refresh();
		fps.sleep();
	}

	finalize();
}

void KBRogue::finalize()
{
	logger->info("Finalization phase.");
	endwin();
	SPDLOG_DEBUG(logger, "Ncurses Finalized.");

	spdlog::drop_all();
}
