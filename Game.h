#pragma once
#ifndef GAME_H
#define GAME_H

#endif // GAME_H
#include <QtWidgets/QLabel>
#include <iostream>

using namespace std;

// Game class contains records of game so far.
class Game
{
public:
    static Game createGame(){
        return Game();
    }
    // Increase the hit piece of player1 by 1
    void increaseHitPieceCount_player1(){
        hitPieceCount_player1++;
    };

    // Increase the hit piece of player2 by 1
    void increaseHitPieceCount_player2(){
        hitPieceCount_player2++;
    };
    // Get hit Piece count of player1(which player1 has hit)
    int getHitPieceCount_player1(){
        return hitPieceCount_player1;
    };
    // Get hit piece count of player2(which player2 has hit)
    int getHitPieceCount_player2(){
        return hitPieceCount_player2;
    };
    // Set the piece to zero
    void setHitPieceCountZero_player1(){
        hitPieceCount_player1 = 0;
    };
    // Set the piece to zero
    void setHitPieceCountZero_player2(){
        hitPieceCount_player2 = 0;
    };
private:
    Game(){
        hitPieceCount_player1 = 0;
        hitPieceCount_player2 = 0;
    }; // Constructor

    int hitPieceCount_player1; // This shows the number of pieces that player1 captured.
    int hitPieceCount_player2; // This shows the number of pieces that player2 captured.
};
