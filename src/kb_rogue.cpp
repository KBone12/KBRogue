#include "kb_rogue.hpp"

#include "curses_include.h"
#include "spdlog/spdlog.h"

#include "map.hpp"
#include "timer.hpp"

using kb::rogue::KBRogue;
using kb::rogue::MapManager;

KBRogue::KBRogue()
	: logger(spdlog::get("logger")),
	mapManager(std::make_shared<MapManager>())
{}

void KBRogue::initialize()
{
	logger->info("Initalization phase.");

	std::setlocale(LC_ALL, "");		// For non-ascii characters
	SPDLOG_DEBUG(logger, "Set environment variables 'LC_ALL' to \"\".");

	SPDLOG_DEBUG(logger, "Start ncurses initializing.");
	initscr();
	cbreak();					// Set to raw mode
	noecho();
	curs_set(false);			// Hide the cursor
	nodelay(stdscr, true);
	intrflush(stdscr, false);
	keypad(stdscr, true);
	ESCDELAY = 25;
	SPDLOG_DEBUG(logger, "Completed ncurses initializing.");

	mapManager->initialize();
}

void KBRogue::start()
{
	logger->info("Start game loop.");

	bool quit = false;
	int c;
	kb::rogue::FpsTimer fps(30);

	auto startMap = std::make_shared<kb::rogue::Map>("resource/map/map0", 1, 1, 1);
	mapManager->addMap(startMap);
	mapManager->changeCurrentMap(startMap);

	// Game loop
	fps.start();
	while (!quit)
	{
		// Key inuputs
		while ((c = getch()) != ERR)
		{
			switch (c)
			{
				case 'q':
				case 'Q':
					quit = true;
					break;
			}

			mapManager->keyInput(c);
		}

		// Updating
		fps.update();
		mapManager->update(fps.getDelta());

		// Rendering
		clear();
		mapManager->render();

#ifdef DEBUG
		mvprintw(0, 0, "%.1f", fps.getFps());
#endif /* DEBUG */

		// Reflecting to stdscr & sleeping
		refresh();
		fps.sleep();
	}

	finalize();
}

void KBRogue::finalize()
{
	logger->info("Finalization phase.");

	mapManager.reset();

	endwin();
	SPDLOG_DEBUG(logger, "Ncurses Finalized.");

	spdlog::drop_all();
}
