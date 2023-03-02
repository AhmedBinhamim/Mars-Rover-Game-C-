#include <vector>
#include <string>
#include "Mars.h"
using namespace std;

#ifndef ROVER_H
#define ROVER_H

class Rover
{
    private:
        char roverHeading;  // Direction Where Rover is Heading Towards
        int posX, posY;
        int roverHealth, maxHealth, roverFuel, maxFuel, moves = 0, score = 0;
        int goldCollected = 0;
        int numOfCommands = 0;
        int numOfCommandSequence = 0;
        int goldTarget;     // Required Gold Set By User To Be Collected
        bool execution;     // Decides If Command Can Be Executed Or Not

        vector<char> fuelBar;
        vector<char> healthBar;
        string command;
        Map *p_mars;        // Pointer To Map of Mars
        Map marsHidden;     // Keeps Track Of Discovered Positions In Planet Marss
    
    public:
        bool win, endGame = false;
        Rover(Map *ptr);
        void setRoverFuel();
        void setRoverHealth();
        void placeRoverRandomly();
        void setFuelBar();
        void setHealthBar();
        void showRoverFuel();
        void showRoverHealth();
        void controlHealth(int, int);
        void controlFuel(int, int);
        void land();
        void move();
        void turnLeft();
        void turnRight();
        void setCommand();      // Take Commad From User
        void takeAction();      // Call Execution Functions On Every Command In a Command Sequence
        void executeCommand(char);       
        void commandExecutable(char);       // Show Exectuion Message Based On Command Validity
        void threeDisappear();
        void goldScore();
        void displayScore();
        void message();
        void quit();
};

#endif