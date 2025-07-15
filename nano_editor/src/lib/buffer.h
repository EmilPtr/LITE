#ifndef BUFFER_H
#define BUFFER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct cursor {
    int start_row;
    int start_col;
    int end_row;
    int end_col;
};

inline void log(std::string s) {
    std::ofstream file("log");
    file << s;
    file.close();
}

inline cursor c = cursor(0, 0, 0, 0);

inline void move_u(const std::vector<std::string> &buffer) {
    if (c.start_row != 0) {
        c.start_row -= 1;
        c.end_row -= 1;
    }
    if (c.start_col >= buffer[c.start_row].size()) {
        c.start_col = buffer[c.start_row].size();
        c.end_col = c.start_col;
    }
}

inline void move_d(const std::vector<std::string> &buffer) {
    if (c.start_row != buffer.size()-1) {
        c.start_row += 1;
        c.end_row += 1;
    }
    if (c.start_col >= buffer[c.start_row].size()) {
        c.start_col = buffer[c.start_row].size();
        c.end_col = c.start_col;
    }
}

inline void move_r(const std::vector<std::string> &buffer) {
    if (c.start_col != buffer[c.start_row].size()) {
        c.start_col += 1;
        c.end_col += 1;
    }
}

inline void move_l() {
    if (c.start_col != 0) {
        c.start_col -= 1;
        c.end_col -= 1;
    }
}

inline bool is_special_key(const int ch, std::vector<std::string> &buffer) {
    if (ch == KEY_BACKSPACE) {
        if (c.start_col != 0 && (c.start_col == c.end_col || c.start_row == c.end_row)) {
            buffer[c.start_row].erase(c.start_col-1, 1);
            move_l();
        }
        else if (c.start_col == 0 && (c.start_col == c.end_col || c.start_row == c.end_row) && c.start_row != 0) {
            std::string temp = buffer[c.start_row];
            buffer.erase(buffer.begin() + c.start_row);
            c.start_col = buffer[c.start_row-1].size();
            c.end_col = c.start_col;
            buffer[c.start_row-1].append(temp);
            move_u(buffer);
        }
        return true;
    }
    if (ch == KEY_ENTER || ch == '\n' || ch == '\r') {
        if (c.start_col == buffer[c.start_row].size()) {
            const std::string empty = "";
            buffer.insert(buffer.begin()+c.start_row+1, empty);
            move_d(buffer);
        }
        else if (c.start_col == c.end_col || c.start_row == c.end_row) {

        }
        return true;
    }
    if (ch >= 1 && ch <= 26) { // Detects any Ctrl+ combos
        if (ch == 24) {
            endwin();
            exit(EXIT_SUCCESS);
        }
        return true;
    }
    if (ch == KEY_UP) {
        move_u(buffer);
        return true;
    }
    if (ch == KEY_DOWN) {
        move_d(buffer);
        return true;
    }
    if (ch == KEY_LEFT) {
        move_l();
        return true;
    }
    if (ch == KEY_RIGHT) {
        move_r(buffer);
        return true;
    }
    if (!(ch >= 32 && ch <= 126)) {
        return true;
    }
    return false;
}

inline std::vector<std::string> initialize_buffer() {
    return {"I HAVE STUFF!!!!", "okay maybe not"};
}

inline void modify_buffer(const int ch, std::vector<std::string> &buffer) {
    log(std::to_string(c.start_row)+" "+std::to_string(c.start_col)+"\n"+std::to_string(c.end_row)+" "+std::to_string(c.end_col));
    if (is_special_key(ch, buffer)) {
        return;
    }
    if (c.start_col != c.end_col || c.start_row != c.end_row) { // If there is a larger selection
        return;
    }
    const char reg_char = static_cast<char>(ch);
    buffer[c.start_row].insert(c.start_col, 1, reg_char);
    move_r(buffer);
}

inline void print_buffer(const std::vector<std::string> &buffer) {
    for (int i = 0; i < buffer.size(); i++) {
        for (int j = 0; j < buffer[i].length()+1; j++) {
            if (j == buffer[i].length() && i >= c.start_row && i <= c.end_row && j >= c.start_col && j <= c.end_col) {
                attron(A_STANDOUT);
                printw("%c", ' ');
                attroff(A_STANDOUT);
                continue;
            }
            if (i >= c.start_row && i <= c.end_row && j >= c.start_col && j <= c.end_col) {
                attron(A_STANDOUT);
                printw("%c", buffer[i][j]);
                attroff(A_STANDOUT);
            } else printw("%c", buffer[i][j]);
        }
        printw("\n");
    }
}



#endif //BUFFER_H
