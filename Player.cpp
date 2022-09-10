/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Allison Lee
 * leealli
 *
 * Project 4: Battleship
 *
 * Program for classic battleship game against CPU
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
    return;
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}

char Player::get_guess_grid_at(int row, int col) {
    return guess_grid[row][col];
}

void Player::add_ship(Ship ship) {
    if (num_ships == MAX_NUM_SHIPS) {
        return;
    } else {
        ships[num_ships] = ship;
        num_ships++;
        remaining_ships++;
        
        for (int i = 0; i < MAX_GRID_SIZE; i++) {
            for (int j = 0; j < MAX_GRID_SIZE; j++) {
                Position tempPos(i,j);
                if (ship.has_position(tempPos)) {
                    grid[i][j] = SHIP_LETTER;
                }
            }
        }
    }
    return;
}

void Player::attack(Player &opponent, Position pos) {
    //already hit or miss?
    if ((opponent.grid[pos.get_row()][pos.get_col()] == HIT_LETTER) || ((opponent.grid[pos.get_row()][pos.get_col()] == MISS_LETTER))) {
        cout << name << " ";
        pos.write(std::cout);
        cout << " miss" << endl;
    } else if (opponent.grid[pos.get_row()][pos.get_col()] == SHIP_LETTER) {
        // Hit that ship
        for (int i = 0; i < MAX_NUM_SHIPS; i++) {
            if (opponent.ships[i].has_position(pos)) {
                opponent.ships[i].hit();
                opponent.grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
                guess_grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
                cout << name << " ";
                pos.write(std::cout);
                cout << " hit" << endl;
                //check if sunk
                if (opponent.ships[i].has_sunk()) {
                    opponent.remaining_ships--;
                    announce_ship_sunk(opponent.ships[i].get_size());
                }
            }
        }
    } else {
        // Miss that ship
        opponent.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        cout << name << " ";
        pos.write(std::cout);
        cout << " miss" << endl;

    }
 
    return;
}

void Player::announce_ship_sunk(int size) {
    if (size == 2) {
        cout << "Congratulations " << name << "! You sunk a Destroyer" << endl;
    } else if (size == 3) {
        cout << "Congratulations " << name << "! You sunk a Submarine" << endl;
    } else if (size == 4) {
        cout << "Congratulations " << name << "! You sunk a Battleship" << endl;
    } else {
        cout << "Congratulations " << name << "! You sunk a Carrier" << endl;
    }
    return;
}

bool Player::load_grid_file(string filename) {
    Position pStart, pEnd;
    ifstream ins;
    ins.open(filename);
    int shipCounter = 0;
    while ((ins >> pStart >> pEnd) && (shipCounter < MAX_NUM_SHIPS)) {
        Ship tempShip(pStart, pEnd);
        add_ship(tempShip);
        shipCounter++;
    }
    if (shipCounter > 0) {
        return true;
    }
    return false;
}

bool Player::destroyed() {
    if (remaining_ships == 0) {
        return true;
    } else {
        return false;
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
