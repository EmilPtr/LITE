/******************************************************************************************
 * main.cpp
 * Created by Emil on XXXX-XX-XX
 * This file is the main event loop of the editor
 * This file will be kept minimal, and most of the heavy-lifting will be done by headers
 ******************************************************************************************/

#include <string>
#include <vector>
#include <ncurses.h>
#include "lib/helper_functions.h"
#include "lib/buffer.h"

using std::string;

// Main event loop
int main() {
    init_ncurses();
    std::vector<std::string> buffer = initialize_buffer();
    int rows,cols;
    while (true) {
        clear();
        getmaxyx(stdscr, rows, cols);
        print_header(cols);
        print_buffer(buffer);
        mvprintw(rows-1, 0, "A silly creation by LimeTheDerg");
        modify_buffer(getch(), buffer);
        refresh();
    }
}
