/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Allison Lee
 * leealli
 *
 * Project 4: Battleship
 *
 * Class for getting the position of each ship
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row_in, int col_in) {
    row = check_range(row_in);
    col = check_range(col_in);
}

Position::Position(char row_in, char col_in) {
    row = check_range(row_in - '1');
    col = check_range(toupper(col_in) - 'A');
}

int Position::get_row() {
    return row;
}

void Position::set_row(int row_in) {
    row = check_range(row_in);
    return;
}

int Position::get_col() {
    return col;
}

void Position::set_col(int col_in) {
    col = check_range(col_in);
    return;
}

void Position::read(istream &is) {
    char col2 = ' ';
    char trash = ' ';
    is >> row >> col2;
    if (is.fail()) {
        is.clear();
        is >> trash >> row >> trash >> col2 >> trash;
    }
    
    row = row - 1;
    col = toupper(col2) - 'A';
    
    row = check_range(row);
    col = check_range(col);
    
    return;
}

void Position::write(ostream &os) {
    char colChar = col + 'A';
    os << "(" << row + 1 << "," << colChar << ")";
    
    return;
}

int Position::check_range(int val) {
    //check if val is in range
    if (val < MAX_GRID_SIZE && val >= 0) {
        return val;
    } else {
        int distance0 = 0 - val;
        int distanceMax = MAX_GRID_SIZE - 1 - val;
        if (abs(distance0) > abs(distanceMax)) {
            return MAX_GRID_SIZE - 1;
        } else {
            return 0;
        }
    }
    
}


// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

