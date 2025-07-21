#include <ncurses.h>
#include <string>

#include "helper_functions.h"

void init_ncurses() {
    // Initialize ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    nonl();
    curs_set(0);
}

void print_header(int cols) {
    attron(A_STANDOUT); // Enable the highlighting attribute
    std::string header = " LITE v0.1";
    for (int i = 0; i < cols-12; i++) {
        header.append(" ");
    }
    printw(header.c_str());
    attroff(A_STANDOUT); // Disable the highlighting attribute
}