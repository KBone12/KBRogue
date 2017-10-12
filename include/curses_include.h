#ifndef _CURSES_INCLUDE_HEADER_IN_
#define _CURSES_INCLUDE_HEADER_IN_
#define CURSES_HAVE_CURSES_H
#define CURSES_HAVE_NCURSES_H
/* #undef CURSES_HAVE_NCURSES_CURSES_H */
/* #undef CURSES_HAVE_NCURSES_NCURSES_H */
#endif

#ifdef CURSES_HAVE_NCURSES_H
#include "ncurses.h"
#elif defined CURSES_HAVE_NCURSES_NCURSES_H
#include "ncurses/ncurses.h"
#elif defined CURSES_HAVE_NCURSES_CURSES_H
#include "ncurses/curses.h"
#elif defined CURSES_HAVE_CURSES_H
#include "curses.h"
#endif
