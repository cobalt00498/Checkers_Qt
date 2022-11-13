#include <windows.h>
#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <map>
using namespace std;

bool isLiftTurn = true;
bool isBlueTurn = true;
bool endGameNow = false;
int hitPieceCount_b = 0;
int hitPieceCount_y = 0;
bool isComputerPlayer = true:
string moveFromButtonName;
string moveToButtonName;

QLabel* movingLabelPtr;
map<string, QLabel*> map_s_Q;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Q_INIT_RESOURCE(resource2);

    bluePieceLabels.push_back(ui->b1Label);
    bluePieceLabels.push_back(ui->b2Label);
    bluePieceLabels.push_back(ui->b3Label);
    bluePieceLabels.push_back(ui->b4Label);
    bluePieceLabels.push_back(ui->b5Label);
    bluePieceLabels.push_back(ui->b6Label);
    bluePieceLabels.push_back(ui->b7Label);
    bluePieceLabels.push_back(ui->b8Label);
    bluePieceLabels.push_back(ui->b9Label);
    bluePieceLabels.push_back(ui->b10Label);
    bluePieceLabels.push_back(ui->b11Label);
    bluePieceLabels.push_back(ui->b12Label);

    yellowPieceLabels.push_back(ui->y1Label);
    yellowPieceLabels.push_back(ui->y2Label);
    yellowPieceLabels.push_back(ui->y3Label);
    yellowPieceLabels.push_back(ui->y4Label);
    yellowPieceLabels.push_back(ui->y5Label);
    yellowPieceLabels.push_back(ui->y6Label);
    yellowPieceLabels.push_back(ui->y7Label);
    yellowPieceLabels.push_back(ui->y8Label);
    yellowPieceLabels.push_back(ui->y9Label);
    yellowPieceLabels.push_back(ui->y10Label);
    yellowPieceLabels.push_back(ui->y11Label);
    yellowPieceLabels.push_back(ui->y12Label);

    boardButtons.push_back(ui->B_1_1);
    boardButtons.push_back(ui->B_1_3);
    boardButtons.push_back(ui->B_1_5);
    boardButtons.push_back(ui->B_1_7);
    boardButtons.push_back(ui->B_2_2);
    boardButtons.push_back(ui->B_2_4);
    boardButtons.push_back(ui->B_2_6);
    boardButtons.push_back(ui->B_2_8);
    boardButtons.push_back(ui->B_3_1);
    boardButtons.push_back(ui->B_3_3);
    boardButtons.push_back(ui->B_3_5);
    boardButtons.push_back(ui->B_3_7);
    boardButtons.push_back(ui->B_4_2);
    boardButtons.push_back(ui->B_4_4);
    boardButtons.push_back(ui->B_4_6);
    boardButtons.push_back(ui->B_4_8);
    boardButtons.push_back(ui->B_5_1);
    boardButtons.push_back(ui->B_5_3);
    boardButtons.push_back(ui->B_5_5);
    boardButtons.push_back(ui->B_5_7);
    boardButtons.push_back(ui->B_6_2);
    boardButtons.push_back(ui->B_6_4);
    boardButtons.push_back(ui->B_6_6);
    boardButtons.push_back(ui->B_6_8);
    boardButtons.push_back(ui->B_7_1);
    boardButtons.push_back(ui->B_7_3);
    boardButtons.push_back(ui->B_7_5);
    boardButtons.push_back(ui->B_7_7);
    boardButtons.push_back(ui->B_8_2);
    boardButtons.push_back(ui->B_8_4);
    boardButtons.push_back(ui->B_8_6);
    boardButtons.push_back(ui->B_8_8);

    //set elements visible - page
    ui->StartButton->setVisible(true);
    ui->RuleButton->setVisible(true);
    ui->WelcomeLabel->setVisible(true);

    //set elements visible - page2
    ui->BackButton->setVisible(true);
    ui->RuleBrowser->setVisible(true);
    ui->RuleLabel->setVisible(true);
    ui->StartButton_2->setVisible(true);

    //set elements visible - page3
        //connect
    for(QPushButton* button: boardButtons) {
        connect(button, &QPushButton::pressed, this, &MainWindow::on_button_clicked);
        button->setVisible(true);
    }

    QPixmap blue_piece = QPixmap(":/image/blue_piece.png");
    for(QLabel* label: bluePieceLabels) {
        label->setVisible(true);
        label->setPixmap(blue_piece);
    }
    QPixmap yellow_piece = QPixmap(":/image/yellow_piece.png");
    for(QLabel* label: yellowPieceLabels) {
        label->setVisible(true);
        label->setPixmap(yellow_piece);
    }

    QPixmap board = QPixmap(":/image/board.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);

    ui->StopButton->setVisible(true);

    ui -> yturnlabel -> setVisible(false);
    ui -> bturnlabel -> setVisible(true);

    //set elements visible - page4
    QPixmap celebrating_background = QPixmap(":/image/celebrate.jpg");
    ui->page_4->setVisible(true);
    ui->BackgroundLabel_4->setPixmap(celebrating_background);

    // insert mapped pair of a button name and the label(pointer) on the button
    map_s_Q.insert(pair<string, QLabel*>(ui->B_1_1->objectName().toStdString(),ui->y1Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_3_1->objectName().toStdString(), ui->y2Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_5_1->objectName().toStdString(), ui->y3Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_7_1->objectName().toStdString(), ui->y4Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_2_2->objectName().toStdString(), ui->y5Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_4_2->objectName().toStdString(), ui->y6Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_6_2->objectName().toStdString(), ui->y7Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_8_2->objectName().toStdString(), ui->y8Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_1_3->objectName().toStdString(), ui->y9Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_3_3->objectName().toStdString(), ui->y10Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_5_3->objectName().toStdString(), ui->y11Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_7_3->objectName().toStdString(), ui->y12Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_2_4->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_4_4->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_6_4->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_8_4->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_1_5->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_3_5->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_5_5->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_7_5->objectName().toStdString(), nullptr));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_2_6->objectName().toStdString(), ui->b9Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_4_6->objectName().toStdString(), ui->b10Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_6_6->objectName().toStdString(), ui->b11Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_8_6->objectName().toStdString(), ui->b12Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_1_7->objectName().toStdString(), ui->b5Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_3_7->objectName().toStdString(), ui->b6Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_5_7->objectName().toStdString(), ui->b7Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_7_7->objectName().toStdString(), ui->b8Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_2_8->objectName().toStdString(), ui->b1Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_4_8->objectName().toStdString(), ui->b2Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_6_8->objectName().toStdString(), ui->b3Label));
    map_s_Q.insert(pair<string, QLabel*>(ui->B_8_8->objectName().toStdString(), ui->b4Label));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Home screen - 'page'
void MainWindow::on_RuleButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);

}

void MainWindow::on_StartButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// Rule intoduction screen - 'page_2'
void MainWindow::on_BackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void MainWindow::on_StartButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void MainWindow::on_HomeButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    //값 초기화 TODO
}

void MainWindow::on_button_clicked(){
    QObject* senderObj = sender();
    string pickedButtonName = senderObj->objectName().toStdString();
    QLabel* pickedLabelPtr;
    pickedLabelPtr = map_s_Q.at(pickedButtonName);

    if (isLiftTurn) { // when user lifts a piece
        try {
            Pick(pickedButtonName, pickedLabelPtr); // throw the exception to catch
            isLiftTurn = !isLiftTurn;
            return;
          // show the exception message
        } catch (invalid_argument& e) {
            QMessageBox::warning(this, "Warn", e.what());
        } catch (logic_error& e) {
            QMessageBox::warning(this, "Warn", e.what());
        }
    } else { // when user put down a piece
            if (pickedLabelPtr != nullptr) {
                try {
                    Pick(pickedButtonName, pickedLabelPtr);
                } catch (invalid_argument& e) {
                    QMessageBox::warning(this, "Warn", e.what());
                }
            } else{
                try {
                  moveToButtonName = pickedButtonName;
                  Move(movingLabelPtr, moveFromButtonName, moveToButtonName);
                  handleKingPiece(movingLabelPtr, moveToButtonName);
                  if (isComputerPlayer) {
                      Sleep(10*1000); // sleep 10 seconds
                      computerMove(ui);
                  }

                } catch (invalid_argument& e) {
                    QMessageBox::warning(this, "Warn", e.what());
                    return;
                }
                // change the turn
                isLiftTurn = !isLiftTurn;
                isBlueTurn = !isBlueTurn;
                ui -> yturnlabel -> setVisible(!isBlueTurn);
                ui -> bturnlabel -> setVisible(isBlueTurn);

                CheckAndHandleWinCase(ui);
                }
    }
}


// Play screen- 'page_3'
void MainWindow::on_StopButton_clicked()
{
    QMessageBox MsgBox;
        MsgBox.setText("Do you want to end this game?");
       // MsgBox.setInformativeText("Do you want to end this game?");
        MsgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
        MsgBox.setDefaultButton(QMessageBox::Ok);
        if (MsgBox.exec() == QMessageBox::Ok ){
            this->close();
            // TODO 모든 상태를 처음으로 initialize하기
        }
}

