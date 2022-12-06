#include <windows.h>
#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Move.h"
#include <QMessageBox>
#include <map>
//#include <QSound>
using namespace std;

//QSound bells(":/image/steppinstone.wav");
bool isPlayer1PieceChoice = true; // This is the flag reprensenting whether the click is meant to set the color of player1's or player2's.
bool isSoundMuted = false; // This is the flag representing whether to play the sound. default value is true, therefore muted.
int choiceOfBoard=1; // This variable stores the choice of board.
int choiceOfPlayer1Piece=1; // This variable sotres the choice of player1 piece.
int choiceOfPlayer2Piece=2; // This variable stores the choice of player2 piece.
bool isLiftTurn = true; // This is the flag representing whether the click is Lifting the piece or Dropping the piece.
bool isPlayer1Turn = true; // This is the flag representing whether the turn is player1's or player2's.
//bool endGameNow = false; // This is the flag userd to check for urgent game end.
int hitPieceCount_player1 = 0; // This shows the number of pieces that player1 captued.
int hitPieceCount_player2 = 0; // This shows the number of pieces that player2 captued.
string moveFromButtonName; // This variable stores the button name where the piece move from.
string moveToButtonName; // This variable stores the button name where the piece move to.

QLabel* movingLabelPtr; // This variable stores the pointer to the label(piece).
// This maps the Button name(string) to the Labels(QLabel ptr) located on the button.
map<string, QLabel*> map_s_Q;
QPixmap* player1PiecePtr;
QPixmap* player2PiecePtr;

// Constructor of the mainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Q_INIT_RESOURCE(resource2);
    // Push blue pieces to List member data (bluePieceLabels)
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

    // Push yellow pieces to List member data (yellowPieceLabels)
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

    // Push buttons pieces to List member data (boardButtons)
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

    // Connect signal and slots and set elements visible - page3
    for(QPushButton* button: boardButtons) {
        connect(button, &QPushButton::pressed, this, &MainWindow::on_button_clicked);
    }

    // Insert mapped pair of a button name and the label(pointer) on the button
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

    //Set elements visible - page5
    //TODO 말 색깔따라서 KING모양도 바꾸기
    // yTurnLabel이랑, 다른것도 이름 바꾸기 label, piece, 이미지 파일들 TODO
    QPixmap player1_piece= QPixmap(":/image/white_piece.png");
    player1PiecePtr = &player1_piece;

    for(QLabel* label: bluePieceLabels) {
        label->setVisible(true);
        label->setPixmap(player1_piece);
    }

    QPixmap player2_piece = QPixmap(":/image/blue_piece.png");
    player2PiecePtr = &player2_piece;

    for(QLabel* label: yellowPieceLabels) {
        label->setVisible(true);
        label->setPixmap(player2_piece);
    }

    ui->yTurnLabel->setVisible(false);
    ui->bTurnLabel->setVisible(true);

    choiceOfBoard = 1; // Set the board to default
    choiceOfPlayer1Piece = 1;// Set the piece for player1 to default
    choiceOfPlayer2Piece = 2;// Set the piece for player2 to default

    ui->BoardButton_1->setVisible(true);
    ui->BoardButton_2->setVisible(true);
    ui->BoardButton_3->setVisible(true);
    ui->BoardButton_4->setVisible(true);
    ui->BoardButton_5->setVisible(true);
    ui->BoardButton_6->setVisible(true);
    ui->BoardButton_7->setVisible(true);
    ui->BoardButton_8->setVisible(true);
    ui->BoardButton_9->setVisible(true);

    ui->PieceButton_1->setVisible(true);
    ui->PieceButton_2->setVisible(true);
    ui->PieceButton_3->setVisible(true);
    ui->PieceButton_4->setVisible(true);
    ui->PieceButton_5->setVisible(true);
    ui->PieceButton_6->setVisible(true);
    ui->PieceButton_7->setVisible(true);
    ui->PieceButton_8->setVisible(true);
    ui->PieceButton_9->setVisible(true);

    ui->stackedWidget->setCurrentWidget(ui->page);
}

// Destructor of MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Reset the game status to the initial status
void MainWindow::resetGameStatus(){

    if (choiceOfPlayer1Piece == 1){
        *player1PiecePtr = QPixmap(":/image/white_piece.png");
    } else if(choiceOfPlayer1Piece == 2){
        *player1PiecePtr = QPixmap(":/image/blue_piece.png");
    } else if(choiceOfPlayer1Piece == 3){
        *player1PiecePtr = QPixmap(":/image/black_piece.png");
    } else if(choiceOfPlayer1Piece == 4){
        *player1PiecePtr = QPixmap(":/image/flag1.png");
    } else if(choiceOfPlayer1Piece == 5){
        *player1PiecePtr = QPixmap(":/image/flag2.png");
    } else if(choiceOfPlayer1Piece == 6){
        *player1PiecePtr = QPixmap(":/image/flag3.png");
    } else if(choiceOfPlayer1Piece == 7){
        *player1PiecePtr = QPixmap(":/image/flag4.png");
    } else if(choiceOfPlayer1Piece == 8){
        *player1PiecePtr = QPixmap(":/image/flag5.png");
    } else {
        *player1PiecePtr = QPixmap(":/image/flag7.png");
    }
    for(QLabel* label: bluePieceLabels) {
        label->setVisible(true);
        label->setPixmap(*player1PiecePtr);
    }


    if (choiceOfPlayer2Piece == 1){
        *player2PiecePtr = QPixmap(":/image/white_piece.png");
    } else if(choiceOfPlayer2Piece == 2){
        *player2PiecePtr = QPixmap(":/image/blue_piece.png");
    } else if(choiceOfPlayer2Piece == 3){
        *player2PiecePtr = QPixmap(":/image/black_piece.png");
    } else if(choiceOfPlayer2Piece == 4){
        *player2PiecePtr = QPixmap(":/image/flag1.png");
    } else if(choiceOfPlayer2Piece == 5){
        *player2PiecePtr= QPixmap(":/image/flag2.png");
    } else if(choiceOfPlayer2Piece == 6){
        *player2PiecePtr= QPixmap(":/image/flag3.png");
    } else if(choiceOfPlayer2Piece == 7){
        *player2PiecePtr= QPixmap(":/image/flag4.png");
    } else if(choiceOfPlayer2Piece == 8){
        *player2PiecePtr= QPixmap(":/image/flag5.png");
    } else {
        *player2PiecePtr = QPixmap(":/image/flag7.png");
    }
    for(QLabel* label: yellowPieceLabels) {
        label->setVisible(true);
        label->setPixmap(*player2PiecePtr);
    }

    isLiftTurn = true;
    isPlayer1Turn = true;
//    endGameNow = false;
    hitPieceCount_player1 = 0;
    hitPieceCount_player2 = 0;
    moveFromButtonName = "";
    moveToButtonName = "";
    movingLabelPtr = nullptr;

    map_s_Q["B_1_1"] = ui-> y1Label;
    map_s_Q["B_3_1"] = ui-> y2Label;
    map_s_Q["B_5_1"] = ui-> y3Label;
    map_s_Q["B_7_1"] = ui-> y4Label;
    map_s_Q["B_2_2"] = ui-> y5Label;
    map_s_Q["B_4_2"] = ui-> y6Label;
    map_s_Q["B_6_2"] = ui-> y7Label;
    map_s_Q["B_8_2"] = ui-> y8Label;
    map_s_Q["B_1_3"] = ui-> y9Label;
    map_s_Q["B_3_3"] = ui-> y10Label;
    map_s_Q["B_5_3"] = ui-> y11Label;
    map_s_Q["B_7_3"] = ui-> y12Label;
    map_s_Q["B_2_4"] = nullptr;
    map_s_Q["B_4_4"] = nullptr;
    map_s_Q["B_6_4"] = nullptr;
    map_s_Q["B_8_4"] = nullptr;
    map_s_Q["B_1_5"] = nullptr;
    map_s_Q["B_3_5"] = nullptr;
    map_s_Q["B_5_5"] = nullptr;
    map_s_Q["B_7_5"] = nullptr;
    map_s_Q["B_2_6"] = ui-> b9Label;
    map_s_Q["B_4_6"] = ui-> b10Label;
    map_s_Q["B_6_6"] = ui-> b11Label;
    map_s_Q["B_8_6"] = ui-> b12Label;
    map_s_Q["B_1_7"] = ui-> b5Label;
    map_s_Q["B_3_7"] = ui-> b6Label;
    map_s_Q["B_5_7"] = ui-> b7Label;
    map_s_Q["B_7_7"] = ui-> b8Label;
    map_s_Q["B_2_8"] = ui-> b1Label;
    map_s_Q["B_4_8"] = ui-> b2Label;
    map_s_Q["B_6_8"] = ui-> b3Label;
    map_s_Q["B_8_8"] = ui-> b4Label;

    ui->y1Label->move(35, 30);
    ui->y2Label->move(163, 30);
    ui->y3Label->move(291, 30);
    ui->y4Label->move(419, 30);
    ui->y5Label->move(99, 94);
    ui->y6Label->move(227, 94);
    ui->y7Label->move(355, 94);
    ui->y8Label->move(483, 94);
    ui->y9Label->move(35, 158);
    ui->y10Label->move(163, 158);
    ui->y11Label->move(291, 158);
    ui->y12Label->move(419, 158);
    ui->b9Label->move(99, 350);
    ui->b10Label->move(227, 350);
    ui->b11Label->move(355, 350);
    ui->b12Label->move(483, 350);
    ui->b5Label->move(35, 414);
    ui->b6Label->move(163, 414);
    ui->b7Label->move(291, 414);
    ui->b8Label->move(419, 414);
    ui->b1Label->move(99, 478);
    ui->b2Label->move(227, 478);
    ui->b3Label->move(355, 478);
    ui->b4Label->move(483, 478);
}

// When RuleButton(in page) is clicked, redict user to page_2 that shows rules.
void MainWindow::on_RuleButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);

}

// When StartButton(in page) is clicked, redict user to page_3 that enables users to play game.
void MainWindow::on_StartButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// When BackeButton(in page_2) clicked, redict user to page that shows back page(Home page).
void MainWindow::on_BackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// When StartButton2(in page_2) is clicked, redict user to page_3 that enables users to play game.
void MainWindow::on_StartButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


// When HomeButton(in page_2) is clicked, redict user to page that shows Home page and reset game status.
void MainWindow::on_HomeButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    resetGameStatus();
}


// When HomeButton2(in page_3) is clicked, redict user to page that shows Home page and reset game status.
void MainWindow::on_HomeButton2_clicked()
{
    resetGameStatus();
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// When PlayAgainButton(in page_3) is clicked, redict user to page_3 that enables users to play game and reset gane status.
void MainWindow::on_PlayAgainButton_clicked()
{
    resetGameStatus();
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// When EndGameButton(in page_3) is clicked, close the window and end game.
void MainWindow::on_EndGameButton_clicked()
{
    this->close();
}

// When BackeButton(in page_5) clicked, redict user to page that shows back page(Home page).
void MainWindow::on_BackButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// When StartButton_3(in page) is clicked, redict user to page_3 that enables users to play game.
void MainWindow::on_StartButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);

}

void MainWindow::on_SettingsButton_clicked()
{   
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
    if (choiceOfBoard == 1){
        ui->BoardUnderbar_1->setVisible(true);
    } else if(choiceOfBoard == 2){
        ui->BoardUnderbar_2->setVisible(true);
    } else if(choiceOfBoard == 3){
        ui->BoardUnderbar_3->setVisible(true);
    } else if(choiceOfBoard == 4){
        ui->BoardUnderbar_4->setVisible(true);
    } else if(choiceOfBoard == 5){
        ui->BoardUnderbar_5->setVisible(true);
    } else if(choiceOfBoard == 6){
        ui->BoardUnderbar_6->setVisible(true);
    } else if(choiceOfBoard == 7){
        ui->BoardUnderbar_7->setVisible(true);
    } else if(choiceOfBoard == 8){
        ui->BoardUnderbar_8->setVisible(true);
    } else {
        ui->BoardUnderbar_9->setVisible(true);
    }

    // When the user enters the Settings first, it pieceunderbar represents piece of players'
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    if (choiceOfPlayer1Piece == 1){
        ui->PieceUnderbar_1->setVisible(true);
    } else if(choiceOfPlayer1Piece == 2){
        ui->PieceUnderbar_2->setVisible(true);
    } else if(choiceOfPlayer1Piece == 3){
        ui->PieceUnderbar_3->setVisible(true);
    } else if(choiceOfPlayer1Piece == 4){
        ui->PieceUnderbar_4->setVisible(true);
    } else if(choiceOfPlayer1Piece == 5){
        ui->PieceUnderbar_5->setVisible(true);
    } else if(choiceOfPlayer1Piece == 6){
        ui->PieceUnderbar_6->setVisible(true);
    } else if(choiceOfPlayer1Piece == 7){
        ui->PieceUnderbar_7->setVisible(true);
    } else if(choiceOfPlayer1Piece == 8){
        ui->PieceUnderbar_8->setVisible(true);
    } else {
        ui->PieceUnderbar_9->setVisible(true);
    }
    ui->Player1Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid white;"
                                     "border-radius: 20px;");
    ui->Player2Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid grey;"
                                     "border-radius: 20px;");
    // redirect users to
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}

// When the square of the board are clicker, execute the below.
void MainWindow::on_button_clicked(){
    QObject* senderObj = sender();
    string pickedButtonName = senderObj->objectName().toStdString(); // Get the name of Button picked by user.
    QLabel* pickedLabelPtr;
    pickedLabelPtr = map_s_Q.at(pickedButtonName);

    if (isLiftTurn) { // When user lifts a piece, do 'pickPiece' movement...
        try {
            Move::pickPiece(pickedButtonName, pickedLabelPtr);
            isLiftTurn = !isLiftTurn;
            return;
          // If the 'pickPiece' funtion throws an exception, show the exception message.

        } catch (invalid_argument& e) {
            QMessageBox::warning(this, "Warn", e.what());
        }

    } else { // when user drops a piece...
            if (pickedLabelPtr != nullptr) { // If the place button the piece is to drop on is not empty (has another piece)...

                try {
                    Move::pickPiece(pickedButtonName, pickedLabelPtr); // Consider it as 'pickPiece' movement.
                } catch (invalid_argument& e) {
                    QMessageBox::warning(this, "Warn", e.what()); // If the 'pickPiece' function throws and exception, show the exception message.
                }
            } else{  // If the place button the piece is to drop on is empty...
                try {
                  Move::movePiece(movingLabelPtr, moveFromButtonName, pickedButtonName); // Do 'movePiece' and If the 'movePiece' function throws and exception, show the exception message.
                  moveToButtonName = pickedButtonName;
                  handleKingPiece(movingLabelPtr, moveToButtonName); // if movePiece is done, check if the moved piece is King and handle it.
                } catch (invalid_argument& e) {
                    QMessageBox::warning(this, "Warn", e.what());
                    return;
                }

                // Change the turn and make it visible the turn switch.
                isLiftTurn = !isLiftTurn;
                isPlayer1Turn = !isPlayer1Turn;
                ui->yTurnLabel->setVisible(!isPlayer1Turn);
                ui->bTurnLabel->setVisible(isPlayer1Turn);

                CheckAndHandleWinCase(ui); // Check if the winner is decided, and if decided redirect user to page for winner celebration.
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
        }
}

// Settings
void MainWindow::on_BoardButton_1_clicked()
{
    choiceOfBoard = 1;
    QPixmap board = QPixmap(":/image/board1.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(true);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
}

void MainWindow::on_BoardButton_2_clicked()
{
    choiceOfBoard = 2;
    QPixmap board = QPixmap(":/image/board2.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(true);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
}

void MainWindow::on_BoardButton_3_clicked()
{
    choiceOfBoard = 3;
    QPixmap board = QPixmap(":/image/board3.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(true);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
}
void MainWindow::on_BoardButton_4_clicked()
{
    choiceOfBoard = 4;
    QPixmap board = QPixmap(":/image/board4.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(true);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
}
void MainWindow::on_BoardButton_5_clicked()
{
    choiceOfBoard = 5;
    QPixmap board = QPixmap(":/image/board5.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(true);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
}
void MainWindow::on_BoardButton_6_clicked()
{
    choiceOfBoard = 6;
    QPixmap board = QPixmap(":/image/board6.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(true);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
}
void MainWindow::on_BoardButton_7_clicked()
{
    choiceOfBoard = 7;
    QPixmap board = QPixmap(":/image/board7.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(true);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(false);
}
void MainWindow::on_BoardButton_8_clicked()
{
    choiceOfBoard= 8;
    QPixmap board = QPixmap(":/image/board8.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(true);
    ui->BoardUnderbar_9->setVisible(false);
}
void MainWindow::on_BoardButton_9_clicked()
{
    choiceOfBoard = 9;
    QPixmap board = QPixmap(":/image/board9.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);
    ui->BoardUnderbar_1->setVisible(false);
    ui->BoardUnderbar_2->setVisible(false);
    ui->BoardUnderbar_3->setVisible(false);
    ui->BoardUnderbar_4->setVisible(false);
    ui->BoardUnderbar_5->setVisible(false);
    ui->BoardUnderbar_6->setVisible(false);
    ui->BoardUnderbar_7->setVisible(false);
    ui->BoardUnderbar_8->setVisible(false);
    ui->BoardUnderbar_9->setVisible(true);
}

void MainWindow::on_Player1Button_clicked()
{

    isPlayer1PieceChoice = true;

    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    if (choiceOfPlayer1Piece == 1){
        ui->PieceUnderbar_1->setVisible(true);
    } else if(choiceOfPlayer1Piece == 2){
        ui->PieceUnderbar_2->setVisible(true);
    } else if(choiceOfPlayer1Piece == 3){
        ui->PieceUnderbar_3->setVisible(true);
    } else if(choiceOfPlayer1Piece == 4){
        ui->PieceUnderbar_4->setVisible(true);
    } else if(choiceOfPlayer1Piece == 5){
        ui->PieceUnderbar_5->setVisible(true);
    } else if(choiceOfPlayer1Piece == 6){
        ui->PieceUnderbar_6->setVisible(true);
    } else if(choiceOfPlayer1Piece == 7){
        ui->PieceUnderbar_7->setVisible(true);
    } else if(choiceOfPlayer1Piece == 8){
        ui->PieceUnderbar_8->setVisible(true);
    } else {
        ui->PieceUnderbar_9->setVisible(true);
    }
    ui->Player1Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid white;"
                                     "border-radius: 20px;");
    ui->Player2Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid grey;"
                                     "border-radius: 20px;");
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}

void MainWindow::on_Player2Button_clicked()
{
    isPlayer1PieceChoice = false;

    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    if (choiceOfPlayer2Piece == 1){
        ui->PieceUnderbar_1->setVisible(true);
    } else if(choiceOfPlayer2Piece == 2){
        ui->PieceUnderbar_2->setVisible(true);
    } else if(choiceOfPlayer2Piece == 3){
        ui->PieceUnderbar_3->setVisible(true);
    } else if(choiceOfPlayer2Piece == 4){
        ui->PieceUnderbar_4->setVisible(true);
    } else if(choiceOfPlayer2Piece == 5){
        ui->PieceUnderbar_5->setVisible(true);
    } else if(choiceOfPlayer2Piece == 6){
        ui->PieceUnderbar_6->setVisible(true);
    } else if(choiceOfPlayer2Piece == 7){
        ui->PieceUnderbar_7->setVisible(true);
    } else if(choiceOfPlayer2Piece == 8){
        ui->PieceUnderbar_8->setVisible(true);
    } else {
        ui->PieceUnderbar_9->setVisible(true);
    }
    ui->Player1Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid grey;"
                                     "border-radius: 20px;");
    ui->Player2Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid white;"
                                     "border-radius: 20px;");
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}

void MainWindow::on_PieceButton_1_clicked()
{
    ui->PieceUnderbar_1->setVisible(true);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag1.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 1;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 1;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_2_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(true);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag2.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 2;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 2;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_3_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(true);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag3.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 3;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 3;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_4_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(true);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag4.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 4;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 4;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_5_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(true);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag5.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 5;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 5;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_6_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(true);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag6.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 6;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 6;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_7_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(true);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag7.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 7;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 7;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_8_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(true);
    ui->PieceUnderbar_9->setVisible(false);

    QPixmap flag_imag = QPixmap(":/image/flag8.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 8;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 8;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}
void MainWindow::on_PieceButton_9_clicked()
{
    ui->PieceUnderbar_1->setVisible(false);
    ui->PieceUnderbar_2->setVisible(false);
    ui->PieceUnderbar_3->setVisible(false);
    ui->PieceUnderbar_4->setVisible(false);
    ui->PieceUnderbar_5->setVisible(false);
    ui->PieceUnderbar_6->setVisible(false);
    ui->PieceUnderbar_7->setVisible(false);
    ui->PieceUnderbar_8->setVisible(false);
    ui->PieceUnderbar_9->setVisible(true);

    QPixmap flag_imag = QPixmap(":/image/flag9.png");
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 9;
        for(QLabel* label: bluePieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    } else {
        choiceOfPlayer2Piece = 9;
        for(QLabel* label: yellowPieceLabels) {
            label->setVisible(true);
            label->setPixmap(flag_imag);
        }
    }
}

//void MainWindow::on_SoundButton_clicked()
//{
//    isSoundMuted = !isSoundMuted;
//    QPixmap sound;
//    if (isSoundMuted == true){ // When it is muted, when user clicks, it
//        sound = QPixmap(":/image/mute.png");
//        bells.stop();
//    } else {
//        sound = QPixmap(":/image/sound.png");
//        bells.play();
//    }
//    ui->SoundLabel->setPixmap(sound);
//}

