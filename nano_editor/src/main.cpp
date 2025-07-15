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
