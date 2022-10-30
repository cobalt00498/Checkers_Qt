#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<map>
#include <string>
using namespace std;

extern bool lift;
extern QPushButton* moveFromButtonPtr;
extern QLabel* moveFromLabelPtr;
extern QLabel* targetLabelPtr;
extern QPushButton* moveToButtonPtr;
extern QLabel* moveToLabelPtr;
extern QList<QLabel*> hitPiecePtrList_b;
extern map<string, QLabel*> m_b;

extern QList<QLabel*> hitPiecePtrList_y;
extern map<string, QLabel*> m_y;
extern bool endGameNow;
extern bool isBlueTurn;


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
    boardButtons.push_back(ui->B_2_1);
    boardButtons.push_back(ui->B_3_1);
    boardButtons.push_back(ui->B_4_1);
    boardButtons.push_back(ui->B_1_2);
    boardButtons.push_back(ui->B_2_2);
    boardButtons.push_back(ui->B_3_2);
    boardButtons.push_back(ui->B_4_2);
    boardButtons.push_back(ui->B_1_3);
    boardButtons.push_back(ui->B_2_3);
    boardButtons.push_back(ui->B_3_3);
    boardButtons.push_back(ui->B_4_3);
    boardButtons.push_back(ui->B_1_4);
    boardButtons.push_back(ui->B_2_4);
    boardButtons.push_back(ui->B_3_4);
    boardButtons.push_back(ui->B_4_4);
    boardButtons.push_back(ui->B_1_5);
    boardButtons.push_back(ui->B_2_5);
    boardButtons.push_back(ui->B_3_5);
    boardButtons.push_back(ui->B_4_5);
    boardButtons.push_back(ui->B_1_6);
    boardButtons.push_back(ui->B_2_6);
    boardButtons.push_back(ui->B_3_6);
    boardButtons.push_back(ui->B_4_6);
    boardButtons.push_back(ui->B_1_7);
    boardButtons.push_back(ui->B_2_7);
    boardButtons.push_back(ui->B_3_7);
    boardButtons.push_back(ui->B_4_7);
    boardButtons.push_back(ui->B_1_8);
    boardButtons.push_back(ui->B_2_8);
    boardButtons.push_back(ui->B_3_8);
    boardButtons.push_back(ui->B_4_8);

    //set visible elements - page
    ui->StartButton->setVisible(true);
    ui->RuleButton->setVisible(true);
    ui->WelcomeLabel->setVisible(true);

    //set visible elements - page2
    ui->BackButton->setVisible(true);
    ui->RuleBrowser->setVisible(true);
    ui->RuleLabel->setVisible(true);
    ui->StartButton_2->setVisible(true);

    //set visible elements - page3
        //connect
    for(QPushButton* button: boardButtons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);
    }

    for (QPushButton* button: boardButtons) {
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

    // insert mapped pair of a button(pointer) and the label(pointer) on the button
    m_y.insert(pair<string, QLabel*>(ui->B_1_8->objectName().toStdString(),ui->y1Label));
    m_y.insert(pair<string, QLabel*>(ui->B_2_8->objectName().toStdString(), ui->y2Label));
    m_y.insert(pair<string, QLabel*>(ui->B_3_8->objectName().toStdString(), ui->y3Label));
    m_y.insert(pair<string, QLabel*>(ui->B_4_8->objectName().toStdString(), ui->y4Label));
    m_y.insert(pair<string, QLabel*>(ui->B_1_7->objectName().toStdString(), ui->y5Label));
    m_y.insert(pair<string, QLabel*>(ui->B_2_7->objectName().toStdString(), ui->y6Label));
    m_y.insert(pair<string, QLabel*>(ui->B_3_7->objectName().toStdString(), ui->y7Label));
    m_y.insert(pair<string, QLabel*>(ui->B_4_7->objectName().toStdString(), ui->y8Label));
    m_y.insert(pair<string, QLabel*>(ui->B_1_6->objectName().toStdString(), ui->y9Label));
    m_y.insert(pair<string, QLabel*>(ui->B_2_6->objectName().toStdString(), ui->y10Label));
    m_y.insert(pair<string, QLabel*>(ui->B_3_6->objectName().toStdString(), ui->y11Label));
    m_y.insert(pair<string, QLabel*>(ui->B_4_6->objectName().toStdString(), ui->y12Label));
    m_y.insert(pair<string, QLabel*>(ui->B_1_5->objectName().toStdString(), nullptr));
    m_y.insert(pair<string, QLabel*>(ui->B_2_5->objectName().toStdString(), nullptr));
    m_y.insert(pair<string, QLabel*>(ui->B_3_5->objectName().toStdString(), nullptr));
    m_y.insert(pair<string, QLabel*>(ui->B_4_5->objectName().toStdString(), nullptr));
    m_y.insert(pair<string, QLabel*>(ui->B_1_4->objectName().toStdString(), nullptr));
    m_y.insert(pair<string, QLabel*>(ui->B_2_4->objectName().toStdString(), nullptr));
    m_y.insert(pair<string, QLabel*>(ui->B_3_4->objectName().toStdString(), nullptr));
    m_y.insert(pair<string, QLabel*>(ui->B_4_4->objectName().toStdString(), nullptr));
    m_b.insert(pair<string, QLabel*>(ui->B_1_3->objectName().toStdString(), ui->b9Label));
    m_b.insert(pair<string, QLabel*>(ui->B_2_3->objectName().toStdString(), ui->b10Label));
    m_b.insert(pair<string, QLabel*>(ui->B_3_3->objectName().toStdString(), ui->b11Label));
    m_b.insert(pair<string, QLabel*>(ui->B_4_3->objectName().toStdString(), ui->b12Label));
    m_b.insert(pair<string, QLabel*>(ui->B_1_2->objectName().toStdString(), ui->b5Label));
    m_b.insert(pair<string, QLabel*>(ui->B_2_2->objectName().toStdString(), ui->b6Label));
    m_b.insert(pair<string, QLabel*>(ui->B_3_2->objectName().toStdString(), ui->b7Label));
    m_b.insert(pair<string, QLabel*>(ui->B_4_2->objectName().toStdString(), ui->b8Label));
    m_b.insert(pair<string, QLabel*>(ui->B_1_1->objectName().toStdString(), ui->b1Label));
    m_b.insert(pair<string, QLabel*>(ui->B_2_1->objectName().toStdString(), ui->b2Label));
    m_b.insert(pair<string, QLabel*>(ui->B_3_1->objectName().toStdString(), ui->b3Label));
    m_b.insert(pair<string, QLabel*>(ui->B_4_1->objectName().toStdString(), ui->b4Label));
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
/* lift = true, fale를 둬서 처음 말을 들어올리는 것이 가능한 순서는 true, 내려놓는 것이 가능한 순서는 false로 정의.*/

    if (isBlueTurn){ /*blue 차례일 때 실행*/
        QObject* senderObj = sender(); //This will give sender object

        QPushButton* pickedButtonPtr;
        pickedButtonPtr = getButtonPtrFromQObjectPtr(ui, senderObj);// return button by reference TODO

        QLabel* pickedLabelPtr;
        pickedLabelPtr = m_b.at(senderObj->objectName().toStdString());

        if (lift) {
            if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                if (pickedLabelPtr->property("color").value<string>()=="y"){
                    QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours."); //오류메세지
                } else {
                    moveFromButtonPtr = pickedButtonPtr; //클릭된 Qobject의 button ptr을 기억
                    moveFromLabelPtr = pickedLabelPtr;
                    lift = false; //lift = false로 바꾸기
                }
            } else {QMessageBox::warning(this,"Warn","Piece does not exists. Please click other places.");}
        } else {
                if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                    moveFromButtonPtr = pickedButtonPtr; //클릭한 버튼ptr을 기억(만약 들어올린 이미 있었다면, 교체됨)
                    moveFromLabelPtr = pickedLabelPtr;
                } else if (!isMoveAllowed(moveFromButtonPtr, pickedButtonPtr)){
                    QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours.");/*에러 메세지를 띄움*/
                } else {
                    lift = true;//lift는 다음 turn을 위해 true으로 만들고,
                    moveToButtonPtr= pickedButtonPtr; // 클릭한 버튼 Ptr을 기억
                    moveToLabelPtr = pickedLabelPtr;
                    Move(moveFromLabelPtr, moveToLabelPtr); // 옮기기& 이전에 있던 버튼위 라벨은 지우기(invisible & map변경) TODO
                    isBlueTurn = !isBlueTurn; // 상대방 차례로 바꾸기
                }
            }
    }else{
        /*yellow 차례일 때 실행*/
        QObject* senderObj = sender(); //This will give sender object

        QPushButton* pickedButtonPtr;
        pickedButtonPtr = getButtonPtrFromQObjectPtr(ui, senderObj);// return button by reference TODO

        QLabel* pickedLabelPtr;
        pickedLabelPtr = m_y.at(senderObj->objectName().toStdString());

        if (lift) {
            if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                if (pickedLabelPtr->property("color").value<string>()=="b"){
                    QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours."); //오류메세지
                } else {
                    moveFromButtonPtr = pickedButtonPtr; //클릭된 Qobject의 button ptr을 기억
                    moveFromLabelPtr = pickedLabelPtr;
                    lift = false; //lift = false로 바꾸기
                }
            } else {QMessageBox::warning(this,"Warn","Piece does not exists. Please click other places.");}
        } else {
                if (pickedLabelPtr != nullptr) { //label이 그 자리에 존재하면,
                    moveFromButtonPtr = pickedButtonPtr; //클릭한 버튼ptr을 기억(만약 들어올린 이미 있었다면, 교체됨)
                    moveFromLabelPtr = pickedLabelPtr;
                } else if (!isMoveAllowed(moveFromButtonPtr, pickedButtonPtr)){
                    QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours.");/*에러 메세지를 띄움*/
                } else {
                    lift = true;//lift는 다음 turn을 위해 true으로 만들고,
                    moveToButtonPtr= pickedButtonPtr; // 클릭한 버튼 Ptr을 기억
                    moveToLabelPtr = pickedLabelPtr;
                    Move(moveFromLabelPtr, moveToLabelPtr); // 옮기기& 이전에 있던 버튼위 라벨은 지우기(invisible & map변경) TODO
                    isBlueTurn = !isBlueTurn; // 상대방 차례로 바꾸기
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
        if ( MsgBox.exec() == QMessageBox::Ok ){
            this->close();
            // TODO 모든 상태를 처음으로 initialize하기
        }
}

