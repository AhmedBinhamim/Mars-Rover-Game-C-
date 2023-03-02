#include <iostream>
#include <iomanip>
#include <time.h>
#include <sstream>
#include <cmath>
#include <windows.h>
#include <cctype>
#include <vector>
#include <conio.h>
#include <limits>
#include "Mars.h"
#include "Rover.h"
#include "Colors.h"
#include "Validation.h"
using namespace std;

// Functions Prototype
void showMap(Map);
void gameOn(Map, Rover);
void menu();
void instructions();
void userChoice();

void userInstructions()
{
    cout << BOLDWHITE << "Mission: Get all the golds!! Do not get trapped!!\n" << RESET << endl;
    cout << "   L => Turn Left | R => Turn Right |"  // 56, 62, 36
         << " M => Move | Q => Quit" <<endl;
    cout << "==============================================================" << endl;
    cout << "          ";
    cout << setw(2) << MAGENTA << char(178) << RESET << setw(11) << " => HILL  |"
         << setw(2) << BOLDRED << '#' << RESET << setw(11) << " => TRAP  |"
         << setw(2) << YELLOW << char(4) << RESET << setw(8) << " => GOLD" << endl 
         << "          " << setw(2) << RED << char(237) << RESET << setw(11) 
         << " => ROCK  |" << setw(2) << GREEN << char(15) << RESET << setw(11) 
         << " => FIXER |" << setw(2) << BOLDMAGENTA << char(233) << RESET 
         << setw(8) << " => HOLE" << endl << endl;
}

void initGame()
{
    system("cls");

    int dimX, dimY;
    string prompt, data;
    char L = 178, // Hill
    R = 237, // Rock
    H = 233, // Hole
    F = 15,  // Fixer / Repair Station
    T = 35;  // Trap

    char objectList[] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                          ' ',' ',' ',' ',' ', T , T , T , T , L ,
                           L , L , L , L , R , R , R , R , F , H };

    data = "Dimensions";
    prompt = "Enter Y Dimensions: ";
    dimY = validateInput(data, prompt, 0, 0);

    prompt = "Enter X Dimensions: ";
    dimX = validateInput(data, prompt, dimY, 0);

    Map mars( dimY, dimX );

    mars.resizeMap();
    mars.initMap(objectList);
    mars.setGold();
    mars.goldScatter();

    Rover marsRover(&mars);

    marsRover.land();
    userInstructions();
    marsRover.displayScore();

    gameOn(mars, marsRover);
}

void winning()
{
    cout << BOLDYELLOW << "*   *   oo   +  +   @   @@   @   00   $   $" << endl;
    cout << BOLDGREEN  << " ***   o  o  +  +    @@@  @@@   0  0  $ $ $" << endl;
    cout << BOLDRED    << "  *    o  o  +  +     @    @    0  0  $   $" << endl;
    cout << BOLDCYAN   << "  *     oo    ++      @    @     00   $   $" << RESET << endl;
}

void losing()
{
    cout << BOLDYELLOW << "*   *   oo   +  +   @     00    SSS  TTT " << endl;
    cout << BOLDGREEN  << " ***   o  o  +  +   @    0  0  SS     T  " << endl;
    cout << BOLDRED    << "  *    o  o  +  +   @    0  0     SS  T  " << endl;
    cout << BOLDCYAN   << "  *     oo    ++    @@@@  00    SSS   T  "<< RESET << endl;
}

void gameOn(Map mars, Rover marsRover)
{
    bool quit = marsRover.endGame;
    bool win;

    while(!quit)
    {
        marsRover.setCommand();
        marsRover.takeAction();
        userInstructions();
        marsRover.displayScore();
        
        quit = marsRover.endGame;
        win = marsRover.win;
    }
    
    marsRover.message();

    if ( win )
        winning();
    else
        losing();
    
    showMap(mars);
}

void playAgain()
{    
    char choice;
    bool playOn = true;
    do
    {
        cout << "Would You Like To Play Again (Y/N) => ";
        choice = toupper(getch());
        cout << BOLDGREEN << choice << RESET << endl;
        
        if( choice == 'Y' )
            menu();
        
        else if ( choice == 'N' )
            playOn = false;
    
    } while (playOn);

    cin.clear();
    exit(EXIT_SUCCESS);
}

void showMap(Map mars)
{
    char choice;
    bool valid = false;
    
    do
    {
        cout << "Would You Like To See Mars Map (Y/N) => ";
        choice = toupper(getch());
        cout << BOLDGREEN << choice << RESET << endl;
        
        if( choice == 'Y' ){
            valid = true;
            cout << endl;
            mars.display();
        }
        else if( choice == 'N' ){
            valid = true;
            break;
        }

    } while(!valid);

    cin.clear();
    playAgain();
}

void menu()
{
    system("cls");
    cout << BOLDCYAN << "*    " << BOLDMAGENTA << "_-_-_-_-_-_-_-_-_-_-_" << BOLDCYAN << "    *" << endl;
    cout << "*  *     " << BOLDYELLOW << "_-EXPLORING-_" << BOLDCYAN <<"     *  *" << endl;
    cout << "*     *     " << BOLDYELLOW << "_-MARS-_" << BOLDCYAN << "    *     *" << endl;
    cout << "*        *    " << BOLDMAGENTA << "-_-" << BOLDCYAN <<"    *        *" << endl;
    cout << "*           *     *           *" << endl;
    cout << "*              *              *" << endl;
    cout << "*           *     *           *" << endl;
    cout << "*        *           *        *" << endl;
    cout << "*     *                 *     *" << endl;
    cout << "*  *      " << BOLDGREEN << "[P] => StArT" << BOLDCYAN << "     *  *" << endl;
    cout << "*         " << BOLDRED << "[Q] => QuIt" << BOLDCYAN << "         *" << endl;
    cout << "*  *      " << BOLDBLUE << "[?] => Help" << BOLDCYAN << "      *  *" << endl;
    cout << "*     *                 *     *" << endl;
    cout << "*        *           *        *" << endl;
    cout << "*           *     *           *" << endl;
    cout << "*              *              *" << endl;
    cout << "*           *     *           *" << endl;
    cout << "*        *    " << BOLDMAGENTA << "-_-" << BOLDCYAN << "    *        *" << endl;
    cout << "*     *    " << BOLDYELLOW << "_- HAVE -_" << BOLDCYAN <<"   *     *" << endl;
    cout << "*  *    " << BOLDYELLOW << "_- FUN PLAYING -_" << BOLDCYAN << "  *  *" << endl;
    cout << "*    " << BOLDMAGENTA << "_-_-_-_-_-_-_-_-_-_-_ " << BOLDCYAN << "   *" << RESET << endl << endl;
    userChoice();
}

void userChoice()
{
    char choice;

    do
    {
        cout << BOLDBLUE << "Your Choice => " << RESET;
        choice = toupper(getch());
        cout << BOLDGREEN << choice  << RESET << endl;

        switch (choice)
        {
            case 'P':   initGame();
                        break;

            case 'Q':   exit(EXIT_SUCCESS);
                        break;
            
            case '?':   instructions();
                        break;
        }

    } while ( choice != 'Q' );
}

void instructions()
{
    system("cls");
    cout << "+--------------------------------------+" << endl;
    cout << "|            EXPLORING MARS            |" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << "|  GAME INSTRUCTIONS:                  |" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << "|  Game Mission:                       |" << endl;
    cout << "|    Get All The Golds !!              |" << endl;
    cout << "|    Do Not Get Trapped !!             |" << endl;
    cout << "|  Movement Commands:                  |" << endl;
    cout << "|    L => Turn Left                    |" << endl;
    cout << "|    R => Turn Right                   |" << endl;
    cout << "|    M => Move                         |" << endl;
    cout << "|    Q => Quit                         |" << endl;           
    cout << "|  Game Objects:                       |" << endl;
    cout << "|    " << BLUE << "?" << RESET << " => Hidden Object                |" << endl;
    cout << "|    Hides The Main Map Objects        |" << endl;
    cout << "|    " << MAGENTA << char(178) << RESET << " => Hill                         |" << endl;
    cout << "|    Block The Rover Way               |" << endl;
    cout << "|    " << BOLDRED << "#" << RESET << " => Trap                         |" << endl;
    cout << "|    User Loses The Game If Trapped    |" << endl;
    cout << "|    " << BOLDRED << "@" << RESET << " => User Trapped                 |" << endl;
    cout << "|    Position Where User Got Trapped   |" << endl;
    cout << "|    " << YELLOW << char(4) << RESET << " => Gold                         |" << endl;
    cout << "|    Main Object To Collect            |" << endl;
    cout << "|    " << RED << char(237) << RESET << " => Rock                         |" << endl;
    cout << "|    Damages The Rover                 |" << endl;
    cout << "|    " << GREEN << char(15) << RESET << " => Fixer                        |" << endl;
    cout << "|    Refuel And Heal The Rover         |" << endl;
    cout << "|    " << BOLDMAGENTA << char(233) << RESET << " => Hole                         |" << endl;
    cout << "|    Reposition Rover Randomly In Map  |" << endl;
    cout << "+--------------------------------------+" << endl;

    system("pause");
    menu();
}

int main()
{
    srand ( time(NULL) );
    
    menu();

    return 0;
}