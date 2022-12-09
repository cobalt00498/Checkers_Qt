#pragma once

#ifndef OPTION_H
#define OPTION_H

#endif // OPTION_H

#include <QtWidgets/QLabel>
#include <iostream>
using namespace std;

// Move class contains the user's choice regarding the design and play mode.
class Option
{
    public:
    // Create the instance using the constructor.
    static Option createOption(){
        return Option();
    };
    // Set 'IsPlayer1PieceChoice' variable. The parameter is bool type.
    void setIsPlayer1PieceChoice(bool isPlayer1Choice){
        isPlayer1PieceChoice = isPlayer1Choice;
    }
    // Set 'choiceOfBoard' variable. The parameter is int type.
    void setChoiceOfBoard(int boardChosen){
        choiceOfBoard = boardChosen;
    }
    // Set 'choiceOfPlayer1Piece' variable. The parameter is int type.
    void setChoiceOfPlayer1Piece(int pieceChosen){
        choiceOfPlayer1Piece = pieceChosen;
    }

    // Set 'ChoiceOfPlayer2Piece' variable. The parameter is int type.
    void setChoiceOfPlayer2Piece(int pieceChosen){
        choiceOfPlayer2Piece = pieceChosen;
    }
    // Set 'IsComputerPlayerMode' variable. The parameter is bool type.
    void setIsComputerPlayerMode(bool isComputerMode){
        isComputerPlayerMode = isComputerMode;
    }
     // Get 'IsPlayer1PieceChoice' variable. Output is bool type.
    bool getIsPlayer1PieceChoice(){
        return isPlayer1PieceChoice;
    };
    // Get 'choiceOfBoard' variable. Output is int type.
    int getChoiceOfBoard(){
        return choiceOfBoard;
    };
    // Get 'choiceOfPlayer1Piece' variable. Output is int type.
    int getChoiceOfPlayer1Piece(){
        return choiceOfPlayer1Piece;
    };
    // Get 'ChoiceOfPlayer2Piece' variable. Output is int type.
    int getChoiceOfPlayer2Piece(){
        return choiceOfPlayer2Piece;
    };
    // Get 'IsComputerPlayerMode' variable. Output is bool type.
    bool getIsComputerPlayerMode(){
        return isComputerPlayerMode;
    };

    private:
    Option(); // Constructor

    bool isPlayer1PieceChoice; // This variable stores the choice of board.

    int choiceOfBoard; // This variable stores the choice of board.

    int choiceOfPlayer1Piece; // This variable sotres the choice of player1 piece.

    int choiceOfPlayer2Piece; // This variable stores the choice of player2 piece.

    bool isComputerPlayerMode; // This is the flag representing whether the player play the game with computer or player.
};
