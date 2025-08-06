/******************************************************************************************
 * main.cpp
 * Created by Emil on 2025-07-11
 * This file is the main event loop of the editor
 * This file will be kept minimal, and most of the heavy-lifting will be done by other files
 * It describes the general control flow of the application
 ******************************************************************************************/

#include <string>
#include <vector>
#include <ncurses.h>
#include "lib/helper_functions.h"
#include "lib/buffer.h"

using std::string;

// Main event loop
int main() {
    initNcurses();
    std::vector<std::string> buffer = initializeBuffer();
    int rows,cols;
    while (true) {
        clear();
        getmaxyx(stdscr, rows, cols);
        printHeader(cols);
        printBuffer(buffer);
        mvprintw(rows-1, 0, "A silly creation by LimeTheDerg");
        modifyBuffer(getch(), buffer);
        refresh();
    }
}
