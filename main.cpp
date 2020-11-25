#include "battleship.h"

//NAME : ANTZELO GKERTSOS , STUDENT ID : 190664088
using namespace std;


void enterToContinue(){
    cout<<"Press enter to continue!";
    cin.clear(); //clears the stream
    cin.ignore(50,'\n'); //ignores next line(enter)
    cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work
}

void displayShipInfo() {
    cout << "          Add Ship          "<< std::endl << "---------------------------\n";
    cout << "   No Name       Squares    "<< std::endl << "---------------------------\n";
    cout << "   1  Carrier       5    "<< std::endl;
    cout << "   1  Battleship    4    "<< std::endl;
    cout << "   1  Cruiser       3    "<< std::endl;
    cout << "   1  Submarine     3    "<< std::endl;
    cout << "   1  Destroyer     2    "<< std::endl;
    cout << "" << endl;
}

int main()
{
    char choice;
    int iChoice;
    string name;

    Player a, b;

    std::cout << "Battleship Menu"<< std::endl << "--------------\n";
    std::cout << "1.Start Game"<< std::endl << "2.Exit Game\n";

    do {
        std::cout << "Enter menu selection 1-2" << std::endl;
        cin >> choice;
        cin.get();
        if (choice < '1' || choice > '2') {
            cout << "Invalid choice try again" << endl;
        }
    } while(choice < '1' || choice > '2');

    iChoice = choice - '0';


    int turn = 1;
    switch(iChoice)
    {
        case 1:
            cout << "Enter player 1 name: \n";
            cin >> name;
            a.setName(name);
            cin.get();
            displayShipInfo();
            for(int i = 1; i < 6; i++) {
                a.addShip(i);
                a.displayBoard(1);
            }

            cout << "Enter player 2 name: \n";
            cin >> name;
            b.setName(name);
            cin.get();
            displayShipInfo();
            for(int i = 1; i < 6; i++) {
                b.addShip(i);
                b.displayBoard(1);
            }

            while(true) {
                a.shoot(turn, &b);
                enterToContinue();
                if(b.checkLost()) {
                    cout << a.getName() << " you won!" << endl;
                    break;
                }
                b.shoot(turn, &a);
                enterToContinue();
                if(a.checkLost()) {
                    cout << b.getName() << " you won!" << endl;
                    break;
                }
                turn++;
            }

            return 0;

        case 2:
            std::cout << "Goodbye\n";
            break;

    }
}