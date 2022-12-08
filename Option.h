#pragma once

#ifndef OPTION_H
#define OPTION_H

#endif // OPTION_H

#include <QtWidgets/QLabel>
#include <iostream>
using namespace std;

// Move class contains two major movement, pick and move(drop).
class Option
{
    public:
    static Option createOption(){
        return Option();
    };

    void setIsPlayer1PieceChoice(bool isPlayer1Choice){
        isPlayer1PieceChoice = isPlayer1Choice;
    }

    void setChoiceOfBoard(int boardChosen){
        choiceOfBoard = boardChosen;
    }

    void setChoiceOfPlayer1Piece(int pieceChosen){
        choiceOfPlayer1Piece = pieceChosen;
    }

    void setChoiceOfPlayer2Piece(int pieceChosen){
        choiceOfPlayer2Piece = pieceChosen;
    }

    void setIsComputerPlayerMode(bool isComputerMode){
        isComputerPlayerMode = isComputerMode;
    }

    bool getIsPlayer1PieceChoice(){
        return isPlayer1PieceChoice;
    };

    int getChoiceOfBoard(){
        return choiceOfBoard;
    };

    int getChoiceOfPlayer1Piece(){
        return choiceOfPlayer1Piece;
    };

    int getChoiceOfPlayer2Piece(){
        return choiceOfPlayer2Piece;
    };

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
