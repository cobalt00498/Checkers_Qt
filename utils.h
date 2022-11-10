#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include "ui_mainwindow.h"
#include "Move.h"
#include <QPushButton>
#include <QLabel>
#include <stdexcept>

namespace Ui { class MainWindow; }
using namespace std;

extern bool isLiftTurn;
extern bool isBlueTurn;
extern bool endGameNow;
extern int hitPieceCount_b;
extern int hitPieceCount_y;

extern string moveFromButtonName;
extern QLabel* movingLabelPtr;

extern map<string, QLabel*> map_s_Q;

void Pick(string pickedButtonName, QLabel*& pickedLabelPtr) {
    if (pickedLabelPtr != nullptr) {
        string pickedLabelcolor = pickedLabelPtr->objectName().toStdString().substr(0,1);
        if (isBlueTurn && pickedLabelcolor== "y") {
            throw invalid_argument("THIS_IS_BLUE'S_TURN");
        } else if (!isBlueTurn && pickedLabelcolor== "b") {
            throw invalid_argument("THIS_IS_YELLOW'S_TURN");
        } else {
            moveFromButtonName = pickedButtonName;
            movingLabelPtr = pickedLabelPtr;
        }
    } else {
        throw invalid_argument("USER_CLICKED_EMPTY_PLACE");
    }
}


void Move(QLabel* movingLabelPtr, string moveFromButtonName, string moveToButtonName){
    int fromX = stoi(moveFromButtonName.substr(2,1));
    int fromY = stoi(moveFromButtonName.substr(4,1));

    int toX = stoi(moveToButtonName.substr(2,1));
    int toY = stoi(moveToButtonName.substr(4,1));
    if (movingLabelPtr->property("king") == false && (isBlueTurn? toY>=fromY: toY<=fromY)){throw invalid_argument("MOVING_FORWARD_ONLY_ALLOWED_FOR_NON_KING");}
    if (abs(toX-fromX) != abs(toY-fromY)) {throw invalid_argument("ONLY_DIAGONAL_MOVE_ALLOWED");}
    if (abs(toX-fromX) ==2 && abs(toY-fromY)==2){
        string midX = to_string(fromX+(int)(toX-fromX)/2);
        string midY = to_string(fromY+(int)(toY-fromY)/2);
        string midButtonName = "B_";
        midButtonName.append(midX);
        midButtonName.append("_");
        midButtonName.append(midY);
        QLabel* midLabelPtr = map_s_Q.at(midButtonName);

        if (midLabelPtr == nullptr) {throw invalid_argument("NO_PIECE_IN_BETWEEN");} //early return

        string color = midLabelPtr->objectName().toStdString().substr(0,1);
        if (isBlueTurn && color=="y"){
            movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
            QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
            map_s_Q[moveFromButtonName] = nullptr;
            map_s_Q[moveToButtonName] = tempLabelPtr;

            map_s_Q.at(midButtonName)->setVisible(false);
            map_s_Q[midButtonName] = nullptr;
            hitPieceCount_b++;
        } else if (!isBlueTurn && color=="b") {
            movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
            QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
            map_s_Q[moveFromButtonName] = nullptr;
            map_s_Q[moveToButtonName] = tempLabelPtr;

            map_s_Q.at(midButtonName)->setVisible(false);
            map_s_Q[midButtonName] = nullptr;
            hitPieceCount_y++;
        } else{throw invalid_argument("INVALID_PIECE_COLOR_IN_BEWEEN");}

    } else if ((movingLabelPtr->property("king") == false && abs(toX-fromX) >= 3)){throw invalid_argument("INVALID_MOVEMENT");
    } else {
        movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
        QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
        map_s_Q[moveFromButtonName] = nullptr;
        map_s_Q[moveToButtonName] = tempLabelPtr;
    }
}


void handleKingPiece(QLabel* movingLabelPtr, string moveToButtonName) {
    int moveToButtonY = stoi(moveToButtonName.substr(4,1));
    if (isBlueTurn && moveToButtonY == 1) {
        QPixmap blueKingPiece = QPixmap(":/image/yellow_piece.png"); //(":/image/blue_king_piece.png");
        movingLabelPtr->setPixmap(blueKingPiece);
        movingLabelPtr->setProperty("king", true);
    } else if (!isBlueTurn && moveToButtonY == 8) {
        QPixmap yellowKingPiece = QPixmap(":/image/blue_piece.png"); //(":/image/yellow_king_piece.png")
        movingLabelPtr->setPixmap(yellowKingPiece);
        movingLabelPtr->setProperty("king", true);
    }
}

bool isWinnerDecided(){
    if (hitPieceCount_b==12 || hitPieceCount_y==12){
        return true;
    }
    return false;
}

string getWinner(){
    if (hitPieceCount_b==12){
        if (hitPieceCount_y==12){
            return "tie";
        }
        return "blue";
    }
    return "yellow";
}

void CheckAndHandleWinCase(Ui::MainWindow* ui) {
    if (!isWinnerDecided()){return;}
    ui->stackedWidget->setCurrentWidget(ui->page_4);
    if (getWinner() == "blue"){
        ui->comment_4->setText("Blue had won the game!");
    } else if (getWinner()=="yellow"){
        ui->comment_4->setText("Yellow had won the game!");
    } else{ //tie
        ui->comment_4->setText("Tie!");
    }
}


QList<QLabel*> getAllPossibleComputerMove(Ui::MainWindow* ui) {
    vector<Move> possibleMoves;
    for (auto [key, value]: map_s_Q) {
        if (value->objectName().toStdString().substr(0,1) == "b" || value == nullptr) {
            continue;
        } else{
            QList<map<string, QLabel*>> temp;
            int fromX = stoi(key.substr(2,1));
            int fromY = stoi(key.substr(4,1));
            if (fromY == 8) { continue; } // 맨아랫줄에 있으면 움직일 수가 없음
            if (fromX == 8) {
                if (fromY==7) {}
                int toX = fromX-1;
                int toY = fromY+1;
                string toButtonName = "B_";
                toButtonName.append(to_string(toX));
                toButtonName.append("_");
                toButtonName.append(to_string(toY));
                bool isJumped = false;
                if (map_s_Q[toButtonName] == nullptr) {
                    class Move possibleMove(fromX, fromY, toX, toY, isJumped);
                    possibleMoves.push_back(possibleMove);
                }
            } else if (){}
        }
    }
}

void computerMove(Ui::MainWindow* ui) {
    QList<QLabel*> possibleMoves = getAllPossibleComputerMove(ui);
}
