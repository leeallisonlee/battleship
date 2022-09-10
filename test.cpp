/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

void startTests() {
    test_position();
    test_ship();
    test_player();
    test_game();
    return;
}

void test_position() {
    // Write your tests here
    cout << "Now testing Position\n";
    
    //default ctor
    Position pDefault;
    
    //Call all functions on default constructor
    cout << "Expected: 0 Actual: " << pDefault.get_row() << endl;
    pDefault.set_col(5);
    cout << "Expected: 5 Actual: " << pDefault.get_col() << endl;
    pDefault.set_row(2);
    cout << "Expected: 2 Actual: " << pDefault.get_row() << endl;
    
    //nondefault ctor (int parameter)
    Position p1(2,3);
    
    //Call functions on nondefault
    cout << "Expected: 3 Actual: " << p1.get_col() << endl;
    cout << "Expected: 2 Actual: " << p1.get_row() << endl;
    p1.set_col(6);
    cout << "Expected: 6 Actual: " << p1.get_col() << endl;
    
    //nondefault ctor (char parameter)
    Position p6('2', 'A');
    cout << "Expected: 1 Actual: " << p6.get_row() << endl;
    cout << "Expected: 0 Actual: " << p6.get_col() << endl;
    Position p7('2', 'a');
    cout << "Expected: 1 Actual: " << p7.get_row() << endl;
    cout << "Expected: 0 Actual: " << p7.get_col() << endl;
    
    //test read
    ifstream positions_in;
    positions_in.open("grid1.txt");
    Position p3;
    p3.read(positions_in); //doesnt work with positions_in >> p3
    cout << "Expected: 7 Actual: " << p3.get_row() << endl;
    
    //test check_range()
    Position p4('9', 'I');
    cout << "Expected: 7 7 Actual: ";
    cout << p4.get_row() << " " << p4.get_col() << endl;
    Position p5(-1, -14);
    cout << "Expected: 00 Actual: ";
    cout << p5.get_row() << p5.get_col() << endl;
    
    
    cout << endl << endl;
    return;
}

void test_ship() {
    cout << "Now testing Ship\n";
        // Write your tests here
        Ship sDefault;
        
        //default
        cout << "Expected: (1,A) Actual: " << sDefault.get_start() << endl;
        cout << "Expected: (1,A) Actual: " << sDefault.get_end() << endl;
        cout << "Expected: 0 Actual: " << sDefault.get_size() << endl;
        
        //non-default vertical
        Position startCoordinate(1, 2);
        Position endCoordinate(5, 2);
        Ship testVertical(startCoordinate, endCoordinate);
        // for has_position(vertical)
        Position p1(2,2);
        Position p2(2,3);
        
        //non-default flipped vertical
        Ship testFlipVertical(endCoordinate, startCoordinate);
        
        // non-default horizontal
        Position startCoordinate2(4, 2);
        Position endCoordinate2(4, 3);
        Ship testHorizontal(startCoordinate2, endCoordinate2);
    
        //non-default flipped horizontal
        Ship testFlipHorizontal(endCoordinate2, startCoordinate2);
    
        // for has_position(horizontal)
        Position p3(4,2);
        Position p4(3,2);
        
        // testing start, end, size functions
        cout << "Expected: (2,C) Actual: " << testVertical.get_start() << endl;
        cout << "Expected: (6,C) Actual: " << testVertical.get_end() << endl;
        cout << "Expected: 5 Actual: " << testVertical.get_size() << endl;
        // testing has_position vertical
        cout << "Expected: 1 Actual: " << testVertical.has_position(p1) << endl;
        cout << "Expected: 0 Actual: " << testVertical.has_position(p2) << endl;
        // testing has_position horizontal
        cout << "Expected: 1 Actual: " << testHorizontal.has_position(p3) << endl;
        cout << "Expected: 0 Actual: " << testHorizontal.has_position(p4) << endl;
        //testing has_position flipped vertical
        cout << "Expected: 1 Actual: " << testVertical.has_position(p1) << endl;
        cout << "Expected: 0 Actual: " << testVertical.has_position(p2) << endl;
        //testing has_position flipped horizontal
        cout << "Expected: 1 Actual: " << testHorizontal.has_position(p3) << endl;
        cout << "Expected: 0 Actual: " << testHorizontal.has_position(p4) << endl;
        // testing hit**
        cout << "Expected: Actual: ";
        testVertical.hit();
        testVertical.hit();
        cout << "Expected: 0 Actual: " << testVertical.has_sunk() << endl;
        cout << endl;

    return;
}

void test_player() {
    cout << "Now testing player()" << endl;
    //test default constructor
    Player player1;
    
    //test nondefault constructor
    Player player2("Joan");
    
    //another player
    Player player3("Allison");
    
    //no name constructor
    Player player4("");
    
    //test initgrid
    player1.print_grid();
    player1.print_guess_grid();
    player2.print_grid();
    player2.print_guess_grid();
    
    //test get_name()
    cout << "Expected: Actual: " << player1.get_name() << endl;
    cout << "Expected: Joan Actual: " << player2.get_name() << endl;
    
    //test get_num_ships()
    cout << "Expected: 0 Actual: " << player1.get_num_ships() << endl;
    cout << "Expected: 0 Actual: " << player2.get_num_ships() << endl;
    
    //test remaining_ships()
    cout << "Expected: 0 Actual: " << player1.get_remaining_ships() << endl;
    cout << "Expected: 0 Actual: " << player2.get_remaining_ships() << endl;
    
    //test load_grid_file()
    cout << "Expected: 1 Actual: " << player1.load_grid_file("grid1.txt")
        << endl;
    cout << "Expected: 1 Actual: " << player2.load_grid_file("grid2.txt")
        << endl;
    cout << "Expected: 0 Actual: " << player3.load_grid_file("grid3.txt")
        << endl;
    cout << "Expected: 0 Actual: " << player4.load_grid_file("grid3.txt")
        << endl;
    
    
    //test if grid has ships (add_ship() & load_grid_file())
    
    player1.print_grid();
    player1.print_guess_grid();
    player2.print_grid();
    player2.print_guess_grid();
    player3.print_grid();
    player3.print_guess_grid();
    player4.print_grid();
    player4.print_guess_grid();
    
    //test get_grid_at()
    cout << "Expected: * Actual: " << player1.get_grid_at(2, 0) << endl;
    cout << "Expected: * Actual: " << player2.get_grid_at(2, 5) << endl;
    cout << "Expected: - Actual: " << player2.get_grid_at(0, 3) << endl;
    
    //test get_guess_grid_at()
    cout << "Expected: - Actual: " << player1.get_guess_grid_at(2, 0) << endl;
    cout << "Expected: - Actual: " << player2.get_guess_grid_at(2, 5) << endl;
    cout << "Expected: - Actual: " << player2.get_guess_grid_at(0, 3) << endl;
    
    //test attack()
    Position attackP('1', 'F');
    cout << "Expected: Joan (1,F) hit Actual: ";
    player1.attack(player2, attackP);
    
    //test failed attack()
    Position failAttack('2', 'E');
    cout << "Expected: (2,E) miss Actual: ";
    player1.attack(player2, failAttack);
    
    //test failed attack()
    Position failAttack2('1', 'F');
    cout << "Expected: (1,F) miss Actual: ";
    player1.attack(player2, failAttack2);
    
    //attack more to sink
    Position attack2('1', 'G');
    cout << "Expected: (1,G) hit Actual: ";
    player1.attack(player2, attack2);
    
    //test announce_ship_sunk
    Position attack3('1', 'H');
    cout << "Expected: (1,H) miss Actual: ";
    player1.attack(player2, attack3);
    
    //another set of attack
    Position attack4('6', 'H');
    cout << "Expected: (6,H) miss Actual: ";
    player1.attack(player2, attack4);
    
    Position attack5('7', 'H');
    cout << "Expected: (7,H) miss Actual: ";
    player1.attack(player2, attack5);
    
    Position attack6('8', 'H');
    cout << "Expected: (8,H) hit Actual: ";
    player1.attack(player2, attack6);
    
    return;
}

void test_game() {
    cout << "Now testing game()" << endl;
    Player player3("Joan");
    Player player2("Allison");
    Game game1(player3, "grid1", player2, "grid2");
    cout << "Expected: 1 Actual: " << game1.check_valid_move("2A") << endl;
    cout << "Expected: Joan you entered an invalid input Actual: " << game1.check_valid_move("2");
    cout << "Expected: Joan you entered an invalid input Actual: " << game1.check_valid_move("2A4f");
    cout << "Expected: 1 Actual: " << game1.check_valid_move("2a") << endl;
    cout << "Expected: 1 Actual: " << game1.check_valid_move("2A") << endl;
    cout << "Expected: Joan you entered an invalid position Actual: " << game1.check_valid_move("9R") << endl;
    
    //testing get_p1()
    cout << "Expected: Joan Actual: " << game1.get_p1().get_name() << endl;
    cout << "Expected: 5 Actual: " << game1.get_p1().get_num_ships() << endl;
    cout << "Expected: 5 Actual: " << game1.get_p1().get_remaining_ships() << endl;
    //testing get_p2()
    cout << "Expected: Allison Actual: " << game1.get_p2().get_name() << endl;
    cout << "Expected: ranNum Actual: " << game1.get_p2().get_num_ships() << endl;
    cout << "Expected: ranNum Actual: " << game1.get_p2().get_remaining_ships() << endl;
}
