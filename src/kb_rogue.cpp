#include "kb_rogue.hpp"

#include <chrono>

#include "curses_include.h"
#include "spdlog/spdlog.h"

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
	kb::rogue::Player player;
	kb::rogue::FpsTimer fps(30);

	fps.start();
	while (!quit)
	{
		clear();

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

		player.render();

#ifdef DEBUG
		mvprintw(0, 0, "%f", fps.getFps());
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
