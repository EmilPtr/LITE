/*************************************************************************************************************
 * buffer.cpp
 * Created by Emil on 2025-07-15
 * This file contains all the main buffer functionality, such as keypresses, editing, selecting, and loading
 * buffer.h is its respective header file
 *************************************************************************************************************/

#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "buffer.h"

struct cursor {
    int startRow;
    int startCol;
    int endRow;
    int endCol;
};

void log(std::string s) {
    std::ofstream file("log");
    file << s;
    file.close();
}

cursor c = cursor(0, 0, 0, 0); // Start the cursor at the top left

// Determine if a selection is active
bool isSelectionActive() {
    return (c.startCol != c.endCol && c.startRow != c.endRow);
}

// Move the cursor up by one row
void moveUp(const std::vector<std::string> &buffer) {
    if (c.startRow != 0) {
        c.startRow -= 1;
        c.endRow -= 1;
    }
    if (c.startCol >= buffer[c.startRow].size()) {
        c.startCol = buffer[c.startRow].size();
        c.endCol = c.startCol;
    }
}

// Move the cursor down by one row
void moveDown(const std::vector<std::string> &buffer) {
    if (c.startRow != buffer.size()-1) {
        c.startRow += 1;
        c.endRow += 1;
    }
    if (c.startCol >= buffer[c.startRow].size()) {
        c.startCol = buffer[c.startRow].size();
        c.endCol = c.startCol;
    }
}

// Move the cursor right by one column
void moveRight(const std::vector<std::string> &buffer) {
    if (c.startCol != buffer[c.startRow].size()) {
        c.startCol += 1;
        c.endCol += 1;
    }
}

// Move the cursor left by one column
void moveLeft() {
    if (c.startCol != 0) {
        c.startCol -= 1;
        c.endCol -= 1;
    }
}

/**
 * Function that checks if the key detected using getch() was a special character,
 * for instance, an escape sequence. The if-statement chain detects which special char was
 * detected, and performs the action associated with it, such as Backspace to delete a character in the buffer.
 * @param ch The character to be checked
 * @param buffer The current text buffer
 * @return a boolean, returns true if it's a special key
 */
bool isSpecialKey(const int ch, std::vector<std::string> &buffer) {

    if (ch == KEY_BACKSPACE) {
        // Remove a character normally
        if (c.startCol != 0 && !isSelectionActive()) {
            buffer[c.startRow].erase(c.startCol-1, 1);
            moveLeft();
        }
        // If the cursor is at the beginning of a line, append the contents of the
        // deleted line to the line above
        else if (c.startCol == 0 && !isSelectionActive() && c.startRow != 0) {
            std::string temp = buffer[c.startRow];
            buffer.erase(buffer.begin() + c.startRow);
            c.startCol = buffer[c.startRow-1].size();
            c.endCol = c.startCol;
            buffer[c.startRow-1].append(temp);
            moveUp(buffer);
        }
        return true;
    }

    if (ch == KEY_ENTER || ch == '\n' || ch == '\r') {
        // If the enter key was pressed at the end of a line
        if (c.startCol == buffer[c.startRow].size() && !isSelectionActive()) {
            const std::string empty;
            buffer.insert(buffer.begin()+c.startRow+1, empty);
            moveDown(buffer);
        }
        else if (!isSelectionActive()) {

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
        moveUp(buffer);
        return true;
    }

    if (ch == KEY_DOWN) {
        moveDown(buffer);
        return true;
    }

    if (ch == KEY_LEFT) {
        moveLeft();
        return true;
    }

    if (ch == KEY_RIGHT) {
        moveRight(buffer);
        return true;
    }

    if (!(ch >= 32 && ch <= 126)) {
        return true;
    }

    return false;
}

// Initialize the buffer
std::vector<std::string> initializeBuffer() {
    return {"I HAVE STUFF!!!!", "okay maybe not"};
}
/**
 * Insert a character into the buffer at the position of the cursor.
 * @param ch The character to insert into the buffer
 * @param buffer The current text buffer
 */
void modifyBuffer(const int ch, std::vector<std::string> &buffer) {
    log(std::to_string(c.startRow)+" "+std::to_string(c.startCol)+"\n"+std::to_string(c.endRow)+" "+std::to_string(c.endCol));
    if (isSpecialKey(ch, buffer)) {
        return;
    }
    if (isSelectionActive()) { // If there is a larger selection
        return;
    }
    const char regChar = static_cast<char>(ch);
    buffer[c.startRow].insert(c.startCol, 1, regChar);
    moveRight(buffer);
}

/**
 * Prints out a buffer to the ncurses stdscr
 * @param buffer The current text buffer
 */
void printBuffer(const std::vector<std::string> &buffer) {
    for (int i = 0; i < buffer.size(); i++) {
        for (int j = 0; j < buffer[i].length()+1; j++) {
            if (j == buffer[i].length() && i >= c.startRow && i <= c.endRow && j >= c.startCol && j <= c.endCol) {
                attron(A_STANDOUT);
                printw("%c", ' ');
                attroff(A_STANDOUT);
                continue;
            }
            if (i >= c.startRow && i <= c.endRow && j >= c.startCol && j <= c.endCol) {
                attron(A_STANDOUT);
                printw("%c", buffer[i][j]);
                attroff(A_STANDOUT);
            } else printw("%c", buffer[i][j]);
        }
        printw("\n");
    }
}


