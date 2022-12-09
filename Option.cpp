#include "Option.h"
#include <iostream>
#include <string>

using namespace std;
// Implementation of the constructor of class Option
Option::Option(){ // Constructor
    isPlayer1PieceChoice = 1;
    choiceOfBoard = 1;
    choiceOfPlayer1Piece  = 1;
    choiceOfPlayer2Piece  = 2;
    isComputerPlayerMode = false;
}
