#include <windows.h>
#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Move.h"
#include <QMessageBox>
#include <map>
using namespace std;

bool isLiftTurn = true; // This is the flag representing whether the click is Lifting the piece or Dropping the piece.
bool isBlueTurn = true; // This is the flag representing whether the turn is Blue's or Yellow's.
//bool endGameNow = false; // This is the flag userd to check for urgent game end.
int hitPieceCount_b = 0; // This shows the number of pieces that Blue captued.
int hitPieceCount_y = 0; // This shows the number of pieces that Yellow captued.
string moveFromButtonName; // This variable stores the button name where the piece move from.
string moveToButtonName; // This variable stores the button name where the piece move to.

QLabel* movingLabelPtr; // This variable stores the pointer to the label(piece).
// This maps the Button name(string) to the Labels(QLabel ptr) located on the button.
map<string, QLabel*> map_s_Q;

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

    //set elements visible - page
    ui->StartButton->setVisible(true);
    ui->RuleButton->setVisible(true);
    ui->WelcomeLabel->setVisible(true);

    //set elements visible - page2
    ui->BackButton->setVisible(true);
    ui->RuleBrowser->setVisible(true);
    ui->RuleLabel->setVisible(true);
    ui->StartButton_2->setVisible(true);

    // Connect signal and slots and set elements visible - page3
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

    ui->yTurnLabel->setVisible(false);
    ui->bTurnLabel->setVisible(true);

    //Set elements visible - page4
    QPixmap celebrating_background = QPixmap(":/image/celebrate.jpg");
    ui->page_4->setVisible(false);

    ui->BackgroundLabel_4->setPixmap(celebrating_background);

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
}

// Destructor of MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Reset the game status to the initial status
void MainWindow::resetGameStatus(){
    isLiftTurn = true;
    isBlueTurn = true;
//    endGameNow = false;
    hitPieceCount_b = 0;
    hitPieceCount_y = 0;
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
    ui->stackedWidget->setCurrentWidget(ui->page);
    resetGameStatus();
}

// When PlayAgainButton(in page_3) is clicked, redict user to page_3 that enables users to play game and reset gane status.
void MainWindow::on_PlayAgainButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
    resetGameStatus();
}

// When EndGameButton(in page_3) is clicked, close the window and end game.
void MainWindow::on_EndGameButton_clicked()
{
    this->close();
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
                isBlueTurn = !isBlueTurn;
                ui->yTurnLabel->setVisible(!isBlueTurn);
                ui->bTurnLabel->setVisible(isBlueTurn);

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

