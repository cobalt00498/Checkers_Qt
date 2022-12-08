#include <windows.h>
#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Move.h"
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool isPlayer1PieceChoice = true; // This is the flag reprensenting whether the click is meant to set the color of player1's or player2's.
bool isSoundMuted = false; // This is the flag representing whether to play the sound. default value is true, therefore muted. TODO
int choiceOfBoard = 1; // This variable stores the choice of board.
int choiceOfPlayer1Piece = 1; // This variable sotres the choice of player1 piece.
int choiceOfPlayer2Piece = 2; // This variable stores the choice of player2 piece.
bool isLiftTurn = true; // This is the flag representing whether the click is Lifting the piece or Dropping the piece.
bool isPlayer1Turn = true; // This is the flag representing whether the turn is player1's or player2's.
bool isComputer; // This is the flag representing whether the player play the game with computer or player.
int hitPieceCount_player1 = 0; // This shows the number of pieces that player1 captued.
int hitPieceCount_player2 = 0; // This shows the number of pieces that player2 captued.
string moveFromButtonName; // This variable stores the button name where the piece move from.
string moveToButtonName; // This variable stores the button name where the piece move to.

QLabel* movingLabelPtr; // This variable stores the pointer to the label(piece).
// This maps the Button name(string) to the Labels(QLabel ptr) located on the button.
map<string, QLabel*> map_s_Q;
map<int, QPixmap> map_boardidx_source; // This is map containing the key(board idx: 1-9) and mapped value(imgae source)
map<int, QPixmap> map_pieceidx_source; // This is map containing the key(piece idx: 1-9) and mapped value(image source to the idexed pieace, which will be show up in main game screen)
map<int, QPixmap> map_pieceidx_kingsource; // This is map containing the key(piece idx: 1-9) and mapped value(king imgae source)
map<int, QLabel*> map_boardidx_underbarptr; // This is map containing the key(board idx: 1-9) and mapped value(pointer to the underbar label of the board idx)
map<int, QLabel*> map_pieceidx_underbarptr; // This is map containing the key(piece idx: 1-9) and mapped value(pointer to the underbar label of the piece idx)
vector<string> boardButton_vec; // It is used when the computer picks and drops a piece

// Constructor of the mainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Q_INIT_RESOURCE(resource2);
    // Push player1's pieces to List member data (player1PieceLabels)
    player1PieceLabels.push_back(ui->b1Label);
    player1PieceLabels.push_back(ui->b2Label);
    player1PieceLabels.push_back(ui->b3Label);
    player1PieceLabels.push_back(ui->b4Label);
    player1PieceLabels.push_back(ui->b5Label);
    player1PieceLabels.push_back(ui->b6Label);
    player1PieceLabels.push_back(ui->b7Label);
    player1PieceLabels.push_back(ui->b8Label);
    player1PieceLabels.push_back(ui->b9Label);
    player1PieceLabels.push_back(ui->b10Label);
    player1PieceLabels.push_back(ui->b11Label);
    player1PieceLabels.push_back(ui->b12Label);

    // Push player2's pieces to List member data (player2PieceLabels)
    player2PieceLabels.push_back(ui->y1Label);
    player2PieceLabels.push_back(ui->y2Label);
    player2PieceLabels.push_back(ui->y3Label);
    player2PieceLabels.push_back(ui->y4Label);
    player2PieceLabels.push_back(ui->y5Label);
    player2PieceLabels.push_back(ui->y6Label);
    player2PieceLabels.push_back(ui->y7Label);
    player2PieceLabels.push_back(ui->y8Label);
    player2PieceLabels.push_back(ui->y9Label);
    player2PieceLabels.push_back(ui->y10Label);
    player2PieceLabels.push_back(ui->y11Label);
    player2PieceLabels.push_back(ui->y12Label);

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

    // Make a vector consists of the BoardButtons
    for (auto iter:map_s_Q){
      boardButton_vec.push_back(iter.first);
    }


    // Insert mapped pair of a board idx(1-9) and the pointer to the underbar belonging to the board idexed.
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(1, ui->BoardUnderbar_1));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(2, ui->BoardUnderbar_2));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(3, ui->BoardUnderbar_3));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(4, ui->BoardUnderbar_4));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(5, ui->BoardUnderbar_5));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(6, ui->BoardUnderbar_6));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(7, ui->BoardUnderbar_7));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(8, ui->BoardUnderbar_8));
    map_boardidx_underbarptr.insert(pair<int, QLabel*>(9, ui->BoardUnderbar_9));

    // Insert mapped pair of a piece idx(1-9) and the pointer to the underbar belonging to the piece idexed.
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(1, ui->PieceUnderbar_1));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(2, ui->PieceUnderbar_2));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(3, ui->PieceUnderbar_3));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(4, ui->PieceUnderbar_4));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(5, ui->PieceUnderbar_5));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(6, ui->PieceUnderbar_6));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(7, ui->PieceUnderbar_7));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(8, ui->PieceUnderbar_8));
    map_pieceidx_underbarptr.insert(pair<int, QLabel*>(9, ui->PieceUnderbar_9));

    // Insert mapped pair of a board idx(1-9) and the QPixamp of the board idexed.
    map_boardidx_source.insert(pair<int, QPixmap>(1, QPixmap(":/image/board1.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(2, QPixmap(":/image/board2.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(3, QPixmap(":/image/board3.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(4, QPixmap(":/image/board4.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(5, QPixmap(":/image/board5.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(6, QPixmap(":/image/board6.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(7, QPixmap(":/image/board7.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(8, QPixmap(":/image/board8.jpeg")));
    map_boardidx_source.insert(pair<int, QPixmap>(9, QPixmap(":/image/board9.jpeg")));

    // Insert mapped pair of a piece idx(1-9) and the QPixamp of the piece idexed.
    map_pieceidx_source.insert(pair<int, QPixmap>(1, QPixmap(":/image/white_piece.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(2, QPixmap(":/image/blue_piece.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(3, QPixmap(":/image/black_piece.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(4, QPixmap(":/image/flag1.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(5, QPixmap(":/image/flag2.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(6, QPixmap(":/image/flag3.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(7, QPixmap(":/image/flag4.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(8, QPixmap(":/image/flag5.png")));
    map_pieceidx_source.insert(pair<int, QPixmap>(9, QPixmap(":/image/flag7.png")));

    // Insert mapped pair of a piece idx(1-9) and the QPixamp of the piece idexed.
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(1, QPixmap(":/image/white_piece.png"))); // TODO
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(2, QPixmap(":/image/blue_piece.png"))); //TODO
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(3, QPixmap(":/image/black_piece.png"))); //TODO
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(4, QPixmap(":/image/flag1_king.png")));
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(5, QPixmap(":/image/flag2_king.png")));
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(6, QPixmap(":/image/flag3_king.png")));
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(7, QPixmap(":/image/flag4_king.png")));
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(8, QPixmap(":/image/flag5_king.png")));
    map_pieceidx_kingsource.insert(pair<int, QPixmap>(9, QPixmap(":/image/flag7_king.png")));

    ui->player2Turn->setChecked(false);
    ui->player1Turn->setChecked(true);

    ui->messageBackgroundLabel->setVisible(false);
    ui->messageTextLabel->setVisible(false);

    ui->CloseButton->setVisible(false);
    ui->messageBackgroundLabel2->setVisible(false);
    ui->messageTextLabel2->setVisible(false);
    ui->YesButton2->setVisible(false);
    ui->NoButton2->setVisible(false);

    ui->messageBackgroundLabel3->setVisible(false);
    ui->messageTextLabel3->setVisible(false);
    ui->YesButton3->setVisible(false);
    ui->NoButton3->setVisible(false);

    ui->stackedWidget->setCurrentWidget(ui->page);
}

// Destructor of MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Reset the game status to the initial status
void MainWindow::resetGameStatus(){

    QPixmap player1_piece = map_pieceidx_source[choiceOfPlayer1Piece];
    for(QLabel* label: player1PieceLabels) {
        label->setPixmap(player1_piece);
        label->setVisible(true);
    }

    QPixmap player2_piece = map_pieceidx_source[choiceOfPlayer2Piece];
    for(QLabel* label: player2PieceLabels) {
        label->setPixmap(player2_piece);
        label->setVisible(true);
    }

    // Set the default vaue When the MainWindow is initialized.
    isLiftTurn = true; // Start with the action 'lift'.
    isPlayer1Turn = true; // Player1 starts first.
    hitPieceCount_player1 = 0; // Player1 captured nothing when the game starts.
    hitPieceCount_player2 = 0; // Player2 captured nothing hwen the game starts.
    moveFromButtonName = ""; // Since not moved any piece, the name of the starting button should be empty string.
    moveToButtonName = ""; // Since not moved any piece, the name of the ending button should be empty string.
    movingLabelPtr = nullptr;
    isComputer = false;

    // Reset the labels.
    ui->player2Turn->setChecked(false);
    ui->player1Turn->setChecked(true);
    ui->player2Turn->setFont(QFont("Cooper Black", 16));
    ui->player2Turn->setText("Player2");
    ui->player1Turn->setText("Player1");

    // Place the pieces in the original position(matching the buttons' names) by setting them in map_s_Q
   /*Since the labels are not actually moving. But set to visible/invisible, which means respectively 'existing' or 'removed from the place'.
   We utilized the map to move the labels logically, but not visually, by mapping them with the buttons' names.*/

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

    // Place the labels to the original poisitions visually.
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

// When SettingsButton(in page) is clicked, show the the chosen option(or default option if the user hasn't set it).
void MainWindow::on_SettingsButton_clicked()
{
    // Set all the underbars to invisible, and then set the underbar of the board the user chose visible.
    for (auto iter = map_boardidx_underbarptr.begin(); iter != map_boardidx_underbarptr.end(); ++iter){
        iter->second->setVisible(false);
    }
    map_boardidx_underbarptr[choiceOfBoard]->setVisible(true);

    // Set all the underbars to invisible, and then set the underbar of the player1 piece the user chose visible.
    for (auto iter = map_pieceidx_underbarptr.begin(); iter != map_pieceidx_underbarptr.end(); ++iter){
        iter->second->setVisible(false);
    }
    map_pieceidx_underbarptr[choiceOfPlayer1Piece]->setVisible(true);

    // The Player1Button should be highlighted. -> Therefore, setting the border color of the button as grey.
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


// When RuleButton(in page) is clicked, redict user to page_2 that shows rules.
void MainWindow::on_RuleButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);

}
// When 'VS Player'(in page) is clicked, redict user to page_3 that enables users to play game.
void MainWindow::on_PlayButton_clicked()
{
    resetGameStatus(); // Reset the game status.
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}
// When 'VS Computer'(in page) is clicked, redict user to page_3 that enables users to play with a computer.
void MainWindow::on_CPUPlayButton_clicked()
{
    resetGameStatus(); // Reset the game status.
    isComputer = true; // Change the status.
    // Change the label
    ui->player2Turn->setText("Computer Player");
    ui->player2Turn->setFont(QFont("Cooper Black", 13));
    ui->player1Turn->setText("Player");
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// When ExitButton(in page) is clicked, ask user again with floating message.
void MainWindow::on_ExitButton_clicked()
{
        ui->messageTextLabel2->setText("Do you want to quit the game?");
        ui->messageBackgroundLabel2->setVisible(true);
        ui->messageTextLabel2->setVisible(true);
        ui->CloseButton->setVisible(false);
        ui->CloseButton->setEnabled(false);
        ui->YesButton2->setVisible(true);
        ui->YesButton2->setEnabled(true);
        ui->NoButton2->setVisible(true);
        ui->NoButton2->setEnabled(true);
}

// When user clicks ExitButton, it asks users if he wants to quit.
// If answered 'Yes', close the game.
void MainWindow::on_YesButton2_clicked()
{
    this->close();
}

// When user clicks ExitButton, it asks users if he wants to quit.
// If answered 'No', make the message invisble.
void MainWindow::on_NoButton2_clicked()
{
    ui->messageBackgroundLabel2->setVisible(false);
    ui->messageTextLabel2->setVisible(false);
    ui->YesButton2->setVisible(false);
    ui->NoButton2->setVisible(false);
}

// When BackeButton(in page_2) clicked, redict user to page that shows back page(Home page).
void MainWindow::on_BackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// When PlayButton2(in page_2) is clicked, redict user to page3 and reset game status.
void MainWindow::on_PlayButton2_clicked()
{
    resetGameStatus();
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// When HomeButton2(in page_3) is clicked, redict user to page that shows Home page and reset game status.
void MainWindow::on_HomeButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// When PlayAgainButton(in page_3) is clicked, redict user to page_3 that enables users to play game and reset gane status.
void MainWindow::on_ResetButton_clicked()
{
    resetGameStatus();
}

// When ExitButton2(in page4) is clicked, ask user again with floating message.
void MainWindow::on_ExitButton2_clicked()
{
        ui->messageTextLabel3->setText("Do you want to quit the game?");
        ui->messageBackgroundLabel3->setVisible(true);
        ui->messageTextLabel3->setVisible(true);
        ui->CloseButton->setVisible(false);
        ui->CloseButton->setEnabled(false);
        ui->YesButton3->setVisible(true);
        ui->YesButton3->setEnabled(true);
        ui->NoButton3->setVisible(true);
        ui->NoButton3->setEnabled(true);
}

// When user clicks Exit Button2, it asks users if he wants to quit.
// If answered 'Yes', close the game.
void MainWindow::on_YesButton3_clicked()
{
    this->close();
}

// When user clicks ExitButton2, it asks users if he wants to quit.
// If answered 'No', make the message invisble.
void MainWindow::on_NoButton3_clicked()
{
    ui->messageBackgroundLabel3->setVisible(false);
    ui->messageTextLabel3->setVisible(false);
    ui->YesButton3->setVisible(false);
    ui->NoButton3->setVisible(false);
}


// When HomeButton2(in page4) is clicked, redirect user to page.
void MainWindow::on_HomeButton2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// When ReplayButton(in page_4) is clicked, redict user to page_3 that enables users to play game and reset gane status.
void MainWindow::on_ReplayButton_clicked()
{
    resetGameStatus();
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// When BackeButton(in page_5) clicked, redict user to page that shows back page(Home page).
void MainWindow::on_BackButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// When PlayButton3(in page_5) is clicked, redict user to page_3 that enables users to play game.
void MainWindow::on_PlayButton3_clicked()
{
    resetGameStatus();
    ui->stackedWidget->setCurrentWidget(ui->page_3);

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
            ui->messageTextLabel->setText(e.what());
            ui->messageBackgroundLabel->setVisible(true);
            ui->messageTextLabel->setVisible(true);
            ui->CloseButton->setVisible(true);
            ui->CloseButton->setEnabled(true);
            return;
        }

    } else { // When user drops a piece...
            if (pickedLabelPtr != nullptr) { // If the place button the piece is to drop on is not empty (has another piece)...

                try {
                    Move::pickPiece(pickedButtonName, pickedLabelPtr); // Consider it as 'pickPiece' movement.
                } catch (invalid_argument& e) {
                    ui->messageTextLabel->setText(e.what());
                    ui->messageBackgroundLabel->setVisible(true);
                    ui->messageTextLabel->setVisible(true);
                    ui->CloseButton->setVisible(true);
                    ui->CloseButton->setEnabled(true);
                    return;
                }
            } else{  // If the place button the piece is to drop on is empty...
                try {
                  Move::movePiece(movingLabelPtr, moveFromButtonName, pickedButtonName); // Do 'movePiece' and If the 'movePiece' function throws and exception, show the exception message.
                  moveToButtonName = pickedButtonName;
                  handleKingPiece(movingLabelPtr, moveToButtonName); // If movePiece is done, check if the moved piece is King and handle it.
                } catch (invalid_argument& e) {
                    ui->messageTextLabel->setText(e.what());
                    ui->messageBackgroundLabel->setVisible(true);
                    ui->messageTextLabel->setVisible(true);
                    ui->CloseButton->setVisible(true);
                    ui->CloseButton->setEnabled(true);
                    return;
                }

                // Change the turn and make it visible the turn switch.
                isLiftTurn = !isLiftTurn;
                isPlayer1Turn = !isPlayer1Turn;
                ui->player1Turn->setChecked(isPlayer1Turn);
                ui->player2Turn->setChecked(!isPlayer1Turn);
                CheckAndHandleWinCase(ui); // Check if the winner is decided, and if decided redirect user to page for winner celebration.
                }
            // After player put down a piece, it's time to CPU (player2)
            if (!isPlayer1Turn && isComputer){
                // Computer picks and drops a piece randomly
                random_shuffle(boardButton_vec.begin(), boardButton_vec.end());
                cout << "============ Computer Turn =================" << endl;
                string pickedButtonName;
                // When CPU picks up the piece
                for (string liftBtn: boardButton_vec){
                  pickedButtonName = liftBtn;
                  QLabel* pickedLabelPtr = map_s_Q.at(pickedButtonName);
                  if (pickedLabelPtr == nullptr) continue; // there is no piece
                  try {
                      Move::pickPiece(pickedButtonName, pickedLabelPtr);// @assign: moveFromButtonName, movingLabelPtr
                      cout << pickedButtonName << " :valid pick" << endl;
                  }
                  catch (invalid_argument& e) {
                      cout << pickedButtonName << " :invalid pick" << endl;
                      continue; // invalid picking is skipped
                  }
                  // When Computer player put down the piece
                  isLiftTurn = false;
                  cout << "============ Drop =================" << endl;
                  for (string dropBtn: boardButton_vec){
                    string droppedButtonName = dropBtn;
                    QLabel* droppedLabelPtr = map_s_Q.at(droppedButtonName);
                    // explore all the boardButtons
                    if (droppedLabelPtr != nullptr) continue; // Other pieces already exists -> skip!
                    try {
                      Move::movePiece(movingLabelPtr, moveFromButtonName, droppedButtonName);
                      cout << droppedButtonName << " :valid drop" << endl;
                      moveToButtonName = droppedButtonName;
                      handleKingPiece(movingLabelPtr, moveToButtonName); // if movePiece is done, check if the moved piece is King and handle it.

                      CheckAndHandleWinCase(ui); // check if the game ends or not
                      // change the status
                      isLiftTurn = true;
                      isPlayer1Turn = true;
                      ui->player1Turn->setChecked(isPlayer1Turn);
                      ui->player2Turn->setChecked(!isPlayer1Turn);
                      return;
                    } catch (invalid_argument& e) {
                        cout << droppedButtonName << " :invalid drop" << endl;
                        continue;
                    }
                  }
            }
            }
            cout << "============ Computer END =================" << endl;

    }
}

// When BoardButton_1 is chosen from user, set the underbar to the BoarButton_1 and set the board in the main game page.
void MainWindow::on_BoardButton_1_clicked()
{
    choiceOfBoard = 1; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_1 Visible.
    map_boardidx_underbarptr[1]->setVisible(true);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_2 is chosen from user, set the underbar to the BoarButton_2 and set the board in the main game page.
void MainWindow::on_BoardButton_2_clicked()
{
    choiceOfBoard = 2; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_2 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(true);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_3 is chosen from user, set the underbar to the BoarButton_3 and set the board in the main game page.
void MainWindow::on_BoardButton_3_clicked()
{
    choiceOfBoard = 3; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_3 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(true);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_4 is chosen from user, set the underbar to the BoarButton_4 and set the board in the main game page.
void MainWindow::on_BoardButton_4_clicked()
{
    choiceOfBoard = 4; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_4 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(true);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_5 is chosen from user, set the underbar to the BoarButton_5 and set the board in the main game page.
void MainWindow::on_BoardButton_5_clicked()
{
    choiceOfBoard = 5; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_5 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(true);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_6 is chosen from user, set the underbar to the BoarButton_6 and set the board in the main game page.
void MainWindow::on_BoardButton_6_clicked()
{
    choiceOfBoard = 6; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_6 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(true);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_7 is chosen from user, set the underbar to the BoarButton_7 and set the board in the main game page.
void MainWindow::on_BoardButton_7_clicked()
{
    choiceOfBoard = 7; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_7 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(true);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_8 is chosen from user, set the underbar to the BoarButton_8 and set the board in the main game page.
void MainWindow::on_BoardButton_8_clicked()
{
    choiceOfBoard= 8; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_8 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(true);
    map_boardidx_underbarptr[9]->setVisible(false);
}

// When BoardButton_9 is chosen from user, set the underbar to the BoarButton_9 and set the board in the main game page.
void MainWindow::on_BoardButton_9_clicked()
{
    choiceOfBoard = 9; // Store the chosen board to the var 'choiceOfBoard'.
    // Set the board in the main game page visible.
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(map_boardidx_source[choiceOfBoard]);

    // Set the underbar to the BoarButton_9 Visible.
    map_boardidx_underbarptr[1]->setVisible(false);
    map_boardidx_underbarptr[2]->setVisible(false);
    map_boardidx_underbarptr[3]->setVisible(false);
    map_boardidx_underbarptr[4]->setVisible(false);
    map_boardidx_underbarptr[5]->setVisible(false);
    map_boardidx_underbarptr[6]->setVisible(false);
    map_boardidx_underbarptr[7]->setVisible(false);
    map_boardidx_underbarptr[8]->setVisible(false);
    map_boardidx_underbarptr[9]->setVisible(true);
}

// When Player1Button is clicked, it shows the player1's piece which is chosen from the user.
void MainWindow::on_Player1Button_clicked()
{

    isPlayer1PieceChoice = true; // Save the var to true, so that the computer knows the flag to be chosen belongs to player1.

    for (auto iter = map_pieceidx_underbarptr.begin(); iter != map_pieceidx_underbarptr.end(); ++iter){
        iter->second->setVisible(false); // Set every pieces' underbar to invisible.
    }
    map_pieceidx_underbarptr[choiceOfPlayer1Piece]->setVisible(true); // And then set undebar to the chosen piece's.


    // Highlight the border of the player1's button to inform the user that he is choosing the piece for player1.
    ui->Player1Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid white;"
                                     "border-radius: 20px;");
    ui->Player2Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid grey;"
                                     "border-radius: 20px;");
}

// When Player2Button is clicked, it shows the player2's piece which is chosen from the user.
void MainWindow::on_Player2Button_clicked()
{
    isPlayer1PieceChoice = false; // Save the var to false, so that the computer knows the flag to be chosen belongs to player2.

    for (auto iter = map_pieceidx_underbarptr.begin(); iter != map_pieceidx_underbarptr.end(); ++iter){
        iter->second->setVisible(false); // Set every pieces' underbar to invisible.
    }
    map_pieceidx_underbarptr[choiceOfPlayer2Piece]->setVisible(true); // And then set undebar to the chosen piece's.

    // Highlight the border of the players2' button to inform the user that he is choosing the piece for player2.
    ui->Player1Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid grey;"
                                     "border-radius: 20px;");
    ui->Player2Button->setStyleSheet("color: white;"
                                     "background-color:qlineargradient(spread:reflect, x1:1, y1:0, x2:0.995, y2:1, stop:0 rgba(218, 218, 218, 255), stop:0.305419 rgba(0, 7, 11, 255), stop:0.935961 rgba(2, 11, 18, 255), stop:1 rgba(240, 240, 240, 255));"
                                     "border: 1px solid white;"
                                     "border-radius: 20px;");
}

// When PieceButton1 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_1_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(true);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 1; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 1; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton2 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_2_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(true);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 2; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 2; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton3 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_3_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(true);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 3; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 3; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton4 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_4_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(true);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 4; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 4; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton5 is clicked,
//show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_5_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(true);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 5; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 5; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton6 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_6_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(true);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 6; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 6; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton7 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_7_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(true);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 7; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 7; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton8 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_8_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(true);
    map_pieceidx_underbarptr[9]->setVisible(false);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 8; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 8; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// When PieceButton9 is clicked,
// show the underline matching to the chosen piece's, remember the chosen piece, and then set the piece image in the main game screen.
void MainWindow::on_PieceButton_9_clicked()
{
    // Show the underline matching to the chosen piece's.
    map_pieceidx_underbarptr[1]->setVisible(false);
    map_pieceidx_underbarptr[2]->setVisible(false);
    map_pieceidx_underbarptr[3]->setVisible(false);
    map_pieceidx_underbarptr[4]->setVisible(false);
    map_pieceidx_underbarptr[5]->setVisible(false);
    map_pieceidx_underbarptr[6]->setVisible(false);
    map_pieceidx_underbarptr[7]->setVisible(false);
    map_pieceidx_underbarptr[8]->setVisible(false);
    map_pieceidx_underbarptr[9]->setVisible(true);

    // Check whether the chosen piece is for player1 or player2.
    if (isPlayer1PieceChoice == true){
        choiceOfPlayer1Piece = 9; // Remember the chosen piece
        for(QLabel* label: player1PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer1Piece]);
        }
    } else {
        choiceOfPlayer2Piece = 9; // Remember the chosen piece
        for(QLabel* label: player2PieceLabels) { // Set the pieces' labels to the chosen piece's image and make it visible.
            label->setVisible(true);
            label->setPixmap(map_pieceidx_source[choiceOfPlayer2Piece]);
        }
    }
}

// If user clicks 'Close' on the alert message, make the message invisible so that he can play game.
void MainWindow::on_CloseButton_clicked()
{
    ui->messageBackgroundLabel->setVisible(false);
    ui->messageTextLabel->setVisible(false);
    ui->CloseButton->setVisible(false);
}
