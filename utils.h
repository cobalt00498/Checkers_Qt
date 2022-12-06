#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <stdexcept>

namespace Ui { class MainWindow; }
using namespace std;

extern bool isLiftTurn;
extern bool isPlayer1Turn;
//extern bool endGameNow;
extern int hitPieceCount_player1;
extern int hitPieceCount_player2;

extern string moveFromButtonName;
extern string moveToButtonName;
extern QLabel* movingLabelPtr;

extern map<string, QLabel*> map_s_Q;

// Check if the movingPiece(=movingLabel) should be King ( = reaches the end line). And if yes, handle it.
void handleKingPiece(QLabel* movingLabelPtr, string moveToButtonName) {
    int moveToButtonY = stoi(moveToButtonName.substr(4,1));
    if (isPlayer1Turn && moveToButtonY == 1) {
        QPixmap blueKingPiece = QPixmap(":/image/blue_king.png");
        movingLabelPtr->setPixmap(blueKingPiece);
        movingLabelPtr->setProperty("king", true); // Set the 'king' property to true.
    } else if (!isPlayer1Turn && moveToButtonY == 8) {
        QPixmap yellowKingPiece = QPixmap(":/image/yellow_king.png");
        movingLabelPtr->setPixmap(yellowKingPiece);
        movingLabelPtr->setProperty("king", true); // Set the 'king' property to true.
    }
}

// Return if the winner is decided (bool). It should be true when one of two players catches all of opponent's pieces.
bool isWinnerDecided(){
    if (hitPieceCount_player1 == 12 || hitPieceCount_player2 == 12){
        return true;
    }
    return false;
}

// Get winner who catched all of opponent's pieces.
string getWinner(){
    if (hitPieceCount_player1 == 12){
        if (hitPieceCount_player2 == 12){
            return "tie";
        }
        return "blue";
    }
    return "yellow";
}

// If the winner is decided, redirect the user to winner celebration page and show who is the winner.
void CheckAndHandleWinCase(Ui::MainWindow* ui) {
    if (!isWinnerDecided()){return;}
    ui->page_4->setVisible(false);
    ui->stackedWidget->setCurrentWidget(ui->page_4);

    if (getWinner() == "blue"){
        ui->comment_4->setFont(QFont("Cooper Black",20));
        ui->comment_4->setText("Player1 had won the game!");

    } else if (getWinner() == "yellow"){
        ui->comment_4->setFont(QFont("Cooper Black",20));
        ui->comment_4->setText("Player2 had won the game!");
    } else{ //tie
        ui->comment_4->setFont(QFont("Cooper Black",20));
        ui->comment_4->setText("Tie!");
    }
}
