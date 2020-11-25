#include "battleship.h"

/**
 * Ship class
 */

Ship::Ship(int size, string type) {
    this->size = size;
    this->type = type;
    hits = 0;
}

bool Ship::isSunk() {
    return size == hits;
}

int Ship::getSize() {
    return size;
}

string Ship::getType() {
    return type;
}

void Ship::hit() {
    if(!isSunk()) {
        hits++;
    }
}


/**
 * BattleshipSquare class
 */

BattleshipSquare::BattleshipSquare() {
    reset();
}

void BattleshipSquare::reset() {
    isFired =  false;
    ship = NULL;
}

bool BattleshipSquare::addShip(Ship * ship) {
    if(this->ship == NULL) {
        this->ship = ship;
        return true;
    }
    else {
        return false;
    }
}

char BattleshipSquare::getStatus() {
    if(ship == NULL) {
        if(isFired) { return 'M'; }
        else { return ' '; }
    }
    else {
        if(isFired) { return 'H'; }
        else { return 'S'; }
    }
}

void BattleshipSquare::fire() {
    isFired = true;
    if(ship != NULL) {
        ship->hit();
    }
}

/**
 * Board class
 */

Board::Board() {
    resetBoard();
}

// Display the board while shooting
void Board::displayBoardShooting() {
    cout << "  ";
    for(char a = 'A'; a < 'A'+8; a++) {
        cout << setw(5) << a;
    }
    cout << endl;

    for(int i = 0; i < 8; i++) {
        if(i >= 9)
            cout << i+1;
        else
            cout << " " << i+1 ;

        for(int j = 0; j < 8 ; j++) {
            if(squares[i][j].getStatus() == 'S') {
                cout << setw(5) << ' ';
            }
            else {
                cout << setw(5) << squares[i][j].getStatus();
            }
        }
        cout << endl;
    }
}

// Display the board while placing ships
void Board::displayBoardPlacing() {
    cout << "  ";
    for(char a = 'A'; a < 'A'+8; a++) {
        cout << setw(5) << a;
    }
    cout << endl;

    for(int i = 0; i < 8; i++) {
        if(i >= 9)
            cout << i+1;
        else
            cout << " " << i+1 ;

        for(int j = 0; j < 8 ; j++) {
            cout << setw(5) << squares[i][j].getStatus();
        }
        cout << endl;
    }
}

int Board::getSquareState(int x, int y) {
    return squares[x][y].getStatus();
}

bool Board::placeShip(int x, int y, int direction, Ship * ship) {
    int size = ship->getSize();
    int row = x - 49;
    int col = y - 65;

    switch(direction) {
        case 'N':
            if(row-size < 0) { return false; }
            for(int i = row; i > row-size; i--) {
                if(!squares[i][col].addShip(ship)) {
                    return false;
                }
            }
            break;
        case 'E':
            if(col+size >= 8) { return false; }
            for(int i = col; i < col+size; i++) {
                if(!squares[row][i].addShip(ship)) {
                    return false;
                }
            }
            break;
        case 'S':
            if(row+size >= 8) { return false; }
            for(int i = row; i < row+size; i++) {
                if(!squares[i][col].addShip(ship)) {
                    return false;
                }
            }
            break;
        case 'W':
            if(col-size < 0) { return false; }
            for(int i = col; i > col-size; i--) {
                if(!squares[row][i].addShip(ship)) {
                    return false;
                }
            }
            break;
    }

    return true;
}

bool Board::fireAtSquare(int x, int y) {
    if (squares[x][y].getStatus() == 'H' || squares[x][y].getStatus() == 'M') {
        cout << "Already shot at this position, try again" << endl;
        return false;
    }
    else {
        squares[x][y].fire();
        return true;
    }
}


// The method sets all squares on the board to empty.
void Board::resetBoard() {
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            squares[x][y].reset();
        }
    }
}

/**
 * Player class
 */

Player::Player() {
    //
}

void Player::setName(string name) {
    this->name = name;
}

string Player::getName() {
    return name;
}

void Player::shoot(int turn, Player *enemy) {
    char xCoord, yCoord;
    cout << "Turn " <<  turn << endl;
    enemy->displayBoard(0);

    cout << "Player " << name << " enter coordinates to fire"<< std::endl;
    bool ok = true;
    do {
        do {
            cout << "Enter the x coordinate (A-H): ";
            cin >> xCoord;
            cin.get(); // get return here
            if (xCoord < 'A' || xCoord > 'H') {
                cout << "Invalid try again" << endl;
            }
        } while (xCoord < 'A' || xCoord > 'H');
        do {
            cout << "Enter the y coordinate (1-8): ";
            cin >> yCoord;
            // cin.get(); // get return here
            if (yCoord < '1' || yCoord > '8') {
                cout << "Invalid try again" << endl;
            }
        } while (yCoord < '1' || yCoord > '8');
        int row = yCoord - 49;
        int col = xCoord - 65;

        ok = enemy->fire(row, col);

    } while(!ok);
}

bool Player::fire(int x, int y) {
    return board.fireAtSquare(x, y);
}

void Player::addShip(int n) {
    int shipSize[] = {0, 5, 4, 3, 3, 2};
    bool ok = false;
    do {
        char xCoord, yCoord, xDirection;
        cout << "---Adding ship " << n << " of 5---" << std::endl;

        do {
            cout << "Enter the x coordinate (A-H): ";
            cin >> xCoord;
            cin.get(); // get return here
            if (xCoord < 'A' || xCoord > 'H') {
                cout << "Invalid try again" << endl;
            }
        } while (xCoord < 'A' || xCoord > 'H');
        do {
            cout << "Enter the y coordinate (1-8): ";
            cin >> yCoord;
            cin.get(); // get return here
            if (yCoord < '1' || yCoord > '8') {
                cout << "Invalid try again" << endl;
            }
        } while (yCoord < '1' || yCoord > '8');

        do {
            cout << "Enter the direction (N/E/S/W): ";
            cin >> xDirection;
            cin.get(); // get return here
            if (xDirection != 'N' && xDirection != 'E' && xDirection != 'S' && xDirection != 'W') {
                cout << "Invalid try again" << endl;
            }
        } while (xDirection != 'N' && xDirection != 'E' && xDirection != 'S' && xDirection != 'W');

        cout << "" << endl;
        ok = placeShip(yCoord, xCoord, xDirection, n);
        if(!ok) {
            cout << "Invalid location, try again" << endl;
        }
    } while(!ok);
}

bool Player::placeShip(int x, int y, int direction, int idx) {
    idx--;
    int shipSize[] = {5, 4, 3, 3, 2};
    string types[] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    Ship * ship = new Ship(shipSize[idx], types[idx]);
    ships[idx] = ship;
    return board.placeShip(x, y, direction, ship);
}

// Display player’s board. Type 0 for shooting, 1 for setting ships
void Player::displayBoard(int type) {
    if(type == 0) {
        board.displayBoardShooting();
    }
    else if(type == 1) {
        board.displayBoardPlacing();
    }

}

bool Player::checkLost() {
    for(int i = 0; i < 5; i++) {
        if(ships[i] != NULL && !ships[i]->isSunk()) {
            return false;
        }
    }
    return true;
}
