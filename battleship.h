#ifndef TEST_BATTLESHIP_H
#define TEST_BATTLESHIP_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Ship {
private:
    int size;
    int hits;
    string type;
public:
    Ship(int size, string type);
    bool isSunk();
    int getSize();
    string getType();
    void hit();
};

class BattleshipSquare {
private:
    Ship * ship;
    bool isFired;
public:
    BattleshipSquare();
    void reset();
    bool addShip(Ship * ship);
    char getStatus();
    void fire();
};

class Board {
private:
    BattleshipSquare squares[8][8];
public:
    Board();
    void displayBoardShooting();
    void displayBoardPlacing();
    int getSquareState(int x, int y);
    bool placeShip(int x, int y, int direction, Ship * ship);
    bool fireAtSquare(int x, int y);
    void resetBoard();
};

class Player {
private:
    string name;
    Board board;
    Ship * ships[5];
public:
    Player();
    void setName(string name);
    string getName();
    void shoot(int turn, Player *enemy);
    bool fire(int x, int y);
    void addShip(int n);
    bool placeShip(int x, int y, int direction, int idx);
    void displayBoard(int type);
    bool checkLost();
    Ship * getShip(int idx);
};


#endif //TEST_BATTLESHIP_H
