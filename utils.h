#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include "ui_mainwindow.h"
#include <string>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>

namespace Ui { class MainWindow; }

using namespace std;


QPushButton*& getButtonPtrFromQObjectPtr(Ui::MainWindow* ui, QObject* ObjectPtr){
    string objectStr= ObjectPtr->objectName().toStdString();
    if (objectStr[2] == 1){
        if (objectStr[4] == 1){
            return ui->B_1_1;
        }else if(objectStr[4] == 2){
            return ui->B_1_2;
        }else if(objectStr[4] == 3){
            return ui->B_1_3;
        }else if(objectStr[4] == 4){
            return ui->B_1_4;
        }else if(objectStr[4] == 5){
            return ui->B_1_5;
        }else if(objectStr[4] == 6){
            return ui->B_1_6;
        }else if(objectStr[4] == 7){
            return ui->B_1_7;
        }else{return ui->B_1_8;}
    }else if (objectStr[2] == 2){
        if (objectStr[4] == 1){
            return ui->B_2_1;
        }else if(objectStr[4] == 2){
            return ui->B_2_2;
        }else if(objectStr[4] == 3){
            return ui->B_2_3;
        }else if(objectStr[4] == 4){
            return ui->B_2_4;
        }else if(objectStr[4] == 5){
            return ui->B_2_5;
        }else if(objectStr[4] == 6){
            return ui->B_2_6;
        }else if(objectStr[4] == 7){
            return ui->B_2_7;
        }else{return ui->B_2_8;}
    }else if(objectStr[2] == 3){
        if (objectStr[4] == 1){
            return ui->B_3_1;
        }else if(objectStr[4] == 2){
            return ui->B_3_2;
        }else if(objectStr[4] == 3){
            return ui->B_3_3;
        }else if(objectStr[4] == 4){
            return ui->B_3_4;
        }else if(objectStr[4] == 5){
            return ui->B_3_5;
        }else if(objectStr[4] == 6){
            return ui->B_3_6;
        }else if(objectStr[4] == 7){
            return ui->B_3_7;
        }else{return ui->B_3_8;}
    }else{
        if (objectStr[4] == 1){
            return ui->B_4_1;
        }else if(objectStr[4] == 2){
            return ui->B_4_2;
        }else if(objectStr[4] == 3){
            return ui->B_4_3;
        }else if(objectStr[4] == 4){
            return ui->B_4_4;
        }else if(objectStr[4] == 5){
            return ui->B_4_5;
        }else if(objectStr[4] == 6){
            return ui->B_4_6;
        }else if(objectStr[4] == 7){
            return ui->B_4_7;
        }else{return ui->B_4_8;}
    }
}

bool isMoveAllowed(QPushButton* startButtonPtr, QPushButton* endButtonPtr){
    //Todo moveFromLabel에서 moveFromLabel까지 움직일 수 있는 지 확인하기
    return true; // Todo
}

void Move(QLabel* moveFromButtonPtr, QLabel* moveToButtonPtr){
    //TODO
}

QLabel* GetRemoveableTarget(QPushButton* startButtonPtr, QPushButton* endButtonPtr){
    //Todo
//    QLabel* targetPiecePtr; // 가운데 있는 상대 말은 삼키기
//    targetPiecePtr = GetRemoveableTarget(moveFromButtonPtr, moveToButtonPtr);
//    if (targetPiecePtr != NULL){ /* 기억하고 있는 말과 클릭한 곳 사이에 말을 딸 수 있다면*/
//        hitPiecePtrList.push_back(targetPiecePtr);
//    } else {
//        //pass
    QLabel* fake = nullptr;
    return fake;
}
