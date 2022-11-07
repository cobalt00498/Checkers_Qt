#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <map>
#include <string>
using namespace std;

extern bool lift;
extern string moveFromButtonName;
extern QLabel* targetLabelPtr;
extern QLabel* movingLabelPtr;
extern string moveToButtonName;
extern QList<QLabel*> hitPiecePtrList_b;
extern int hitPieceCount_b;
extern map<string, QLabel*> m_b;

extern QList<QLabel*> hitPiecePtrList_y;
extern int hitPieceCount_y;
extern map<string, QLabel*> map_s_Q;
extern bool endGameNow;
extern bool isBlueTurn;
extern bool moveDone;


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
        connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);
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

    //set elements visible - page4
    QPixmap celebrating_background = QPixmap(":/image/celebrate.jpeg");
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

// connect함수로 다 이어줬기 때문에, yellow or blue piece button이 클릭되면, 어떤 일을 할 것인지 정해야 함.
void MainWindow::on_button_clicked(){
/* lift = true, false를 둬서 처음 말을 들어올리는 것이 가능한 순서는 true, 내려놓는 것이 가능한 순서는 false로 정의.*/
    if (endGameNow == false){
        if (isBlueTurn){ /*blue 차례일 때 실행*/
            QObject* senderObj = sender(); //This will give sender object
            string pickedButtonName = senderObj->objectName().toStdString();

//            //check the button is really blue one.
//            if (pickedButtonName.substr(0,1) == "y") {
//                QMessageBox::warning(this,"Warn","This turn is blue's. You picked yellow one.");/*에러 메세지를 띄움*/
//                return;
//            }

            QLabel* pickedLabelPtr;
            pickedLabelPtr = map_s_Q.at(pickedButtonName);
            if (lift) {
                if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                    if (pickedLabelPtr->objectName().toStdString().substr(0,1) == "y") {
                        QMessageBox::warning(this,"Warn","This turn is blue's. You picked yellow one.");/*에러 메세지를 띄움*/
                        return;
                    } else {
                        moveFromButtonName = pickedButtonName; //클릭된 Qobject의 button name을 기억
                        movingLabelPtr = pickedLabelPtr;
                        lift = false; //lift = false로 바꾸기
                        return;
                    }
                } else {
                    QMessageBox::warning(this,"Warn","Piece you're lifting does not exists. Please click other places.");
                    return;
                }
            } else {
                    if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                        moveFromButtonName = pickedButtonName; //클릭한 button name을 기억(만약 들어올린 이미 있었다면, 교체됨)
                        movingLabelPtr = pickedLabelPtr;
                        return;
                    } else if (!isMoveAllowed(isBlueTurn, moveFromButtonName, pickedButtonName)){
                        QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours.");/*에러 메세지를 띄움*/
                        return;
                    } else {
                        lift = true;//lift는 다음 turn을 위해 true으로 만들고,
                        moveToButtonName= pickedButtonName; // 클릭한 버튼 이름을 기억
                        int type = MoveAndGetMoveType(movingLabelPtr, moveFromButtonName, moveToButtonName); // 옮기기& 이전에 있던 버튼위 라벨은 지우기(invisible & map변경) TODO
                        if (type==2){
                            RemoveLabelInBetween(isBlueTurn, moveFromButtonName, moveToButtonName);
                        }
                        isBlueTurn = !isBlueTurn; // 상대방 차례로 바꾸기
                        if (isWinnerDecided()){ // Winner 이름 page에 띄워진 라벨에 넣기
                            ui->stackedWidget->setCurrentWidget(ui->page_4);
                            if (getWinner() == "blue"){
                                ui->comment_4->setText("Blue had won the game!");
                            } else if (getWinner()=="yellow"){
                                ui->comment_4->setText("Yellow had won the game!");
                            } else{//tie
                                ui->comment_4->setText("Tie!");
                            }
                        }
                        return;
                    }
                }
        }else{
            /*yellow 차례일 때 실행*/
            QObject* senderObj = sender(); //This will give sender object
            string pickedButtonName = senderObj->objectName().toStdString();

//            //check the button is really blue one.
//            if (pickedButtonName.substr(0,1) == "b") {
//                QMessageBox::warning(this,"Warn","This turn is yello's. You picked blue one.");/*에러 메세지를 띄움*/
//                return;
//            }

            QLabel* pickedLabelPtr;
            pickedLabelPtr = map_s_Q.at(pickedButtonName);
            if (lift) {
                if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                    if (pickedLabelPtr->objectName().toStdString().substr(0,1) == "b") {
                        QMessageBox::warning(this,"Warn","This turn is yello's. You picked blue one.");/*에러 메세지를 띄움*/
                        return;
                    } else {
                        moveFromButtonName = pickedButtonName; //클릭된 Qobject의 button name을 기억
                        movingLabelPtr = pickedLabelPtr;
                        lift = false; //lift = false로 바꾸기
                        return;
                    }
                } else {
                    QMessageBox::warning(this,"Warn","Piece you're lifting does not exists. Please click other places.");
                    return;
                }
            } else {
                    if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                        moveFromButtonName = pickedButtonName; //클릭한 button name을 기억(만약 들어올린 이미 있었다면, 교체됨)
                        movingLabelPtr = pickedLabelPtr;
                        return;
                    } else if (!isMoveAllowed(isBlueTurn, moveFromButtonName, pickedButtonName)){
                        QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours.");/*에러 메세지를 띄움*/
                        return;
                    } else {
                        lift = true;//lift는 다음 turn을 위해 true으로 만들고,
                        moveToButtonName= pickedButtonName; // 클릭한 버튼 이름을 기억
                        int type = MoveAndGetMoveType(movingLabelPtr, moveFromButtonName, moveToButtonName); // 옮기기& 이전에 있던 버튼위 라벨은 지우기(invisible & map변경) TODO
                        if (type==2){
                            RemoveLabelInBetween(isBlueTurn, moveFromButtonName, moveToButtonName);
                        }
                        isBlueTurn = !isBlueTurn; // 상대방 차례로 바꾸기
                        if (isWinnerDecided()){ // Winner 이름 page에 띄워진 라벨에 넣기
                            ui->stackedWidget->setCurrentWidget(ui->page_4);
                            if (getWinner() == "blue"){
                                ui->comment_4->setText("Blue had won the game!");
                            } else if (getWinner()=="yellow"){
                                ui->comment_4->setText("Yellow had won the game!");
                            } else{//tie
                                ui->comment_4->setText("Tie!");
                            }
                        }
                        return;
                    }
                }
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

