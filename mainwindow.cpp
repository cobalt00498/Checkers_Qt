#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


extern bool lift;
extern QLabel* moveFromLabel;
extern QLabel* moveToLabel;
extern QLabel* targetLabel;
extern QList<QLabel*> hitPieces;
extern bool endGameNow;


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

    bluePieceButtons.push_back(ui->b1Button);
    bluePieceButtons.push_back(ui->b2Button);
    bluePieceButtons.push_back(ui->b3Button);
    bluePieceButtons.push_back(ui->b4Button);
    bluePieceButtons.push_back(ui->b5Button);
    bluePieceButtons.push_back(ui->b6Button);
    bluePieceButtons.push_back(ui->b7Button);
    bluePieceButtons.push_back(ui->b8Button);
    bluePieceButtons.push_back(ui->b9Button);
    bluePieceButtons.push_back(ui->b10Button);
    bluePieceButtons.push_back(ui->b11Button);
    bluePieceButtons.push_back(ui->b12Button);

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

    yellowPieceButtons.push_back(ui->y1Button);
    yellowPieceButtons.push_back(ui->y2Button);
    yellowPieceButtons.push_back(ui->y3Button);
    yellowPieceButtons.push_back(ui->y4Button);
    yellowPieceButtons.push_back(ui->y5Button);
    yellowPieceButtons.push_back(ui->y6Button);
    yellowPieceButtons.push_back(ui->y7Button);
    yellowPieceButtons.push_back(ui->y8Button);
    yellowPieceButtons.push_back(ui->y9Button);
    yellowPieceButtons.push_back(ui->y10Button);
    yellowPieceButtons.push_back(ui->y11Button);
    yellowPieceButtons.push_back(ui->y12Button);

    boardLabels.push_back(ui->Board1);
    buttons.push_back(ui->ResetButton);

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
    for(QPushButton* button: bluePieceButtons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);
    }
    for(QPushButton* button: yellowPieceButtons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);
    }

    QPixmap blue_piece = QPixmap(":/image/blue_piece.png");
    for(QLabel* label: bluePieceLabels) {
        label->setVisible(true);
        label->setPixmap(blue_piece);
    }

    for (QPushButton* button: bluePieceButtons) {
        button->setVisible(true);
    }

    QPixmap yellow_piece = QPixmap(":/image/yellow_piece.png");
    for(QLabel* label: yellowPieceLabels) {
        label->setVisible(true);
        label->setPixmap(yellow_piece);
    }

    for (QPushButton* button: yellowPieceButtons) {
        button->setVisible(true);
    }

    QPixmap board = QPixmap(":/image/board.jpeg");
    ui->Board1->setVisible(true);
    ui->Board1->setPixmap(board);

    ui->ResetButton->setVisible(true);
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


// Play screen- 'page_3'
void MainWindow::on_ResetButton_clicked()
{
 // Todos
}


void MainWindow::on_HomeButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// connect함수로 다 이어줬기 때문에, yellow or blue piece button이 클릭되면, 어떤 일을 할 것인지 정해야 함.
void MainWindow::on_button_clicked(){
/* lift = true, fale를 둬서 처음 말을 들어올리는 것이 가능한 순서는 true, 내려놓는 것이 가능한 순서는 false로 정의.
 * 클릭했을 때,
 * if lift=true일 때,
 *     if 선택한 칸에 말이 있으면, map을 이용해서..?
 *          if 내 쪽 말이 아니면, {오류 메세지 보내기}
 *          else {잡아올린 말을 기억 (집는 행위, 여러번 잡을 수 있음) & lift = false로 바꾸기
 *      else {들어올릴 말이 없다고 에러 메세지를 띄움}
 * else
 *      if 선택한 위치에 말이있으면, {잡아올린 말을 바꿈}
 *      else if 선택한 위치가 움직일 수 있는 위치(대각선에 위치했는지)가 아니면, {에러 메세지를 띄움}.
 *            else if 기억하고 있는 말과 클릭한 곳 사이에 말을 딸 수 있으면, {점수를 증가시키고, lift는 0으로 만들고, 따먹힌 상대 piece는 화면에서 invisible하게 만들기}.
 *                else pass
*/
    QObject* senderObj = sender(); //This will give sender object
    QString senderObjectName = senderObj->objectName();
    // extract the index from button object name
    string senderObjectNameStr = senderObjectName.toStdString();
    int index = getIndexFromPieceButtonName(senderObjectNameStr);
    QLabel* label;
    label = bluePieceLabels.at(index-1);

    if (lift) {
        if (label->isVisible()) {
            if (!isButtonBlue(senderObjectNameStr)){
                //오류메세지
                QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours.");
            } else {
                moveFromLabel = label; //잡아올린 말을 기억
                lift = false; //lift = false로 바꾸기
            }
        } else {QMessageBox::warning(this,"Warn","Piece does not exists. Please click other places.");}
    } else {
            if (label->isVisible()) {
                moveFromLabel = label; //잡아올린 말을 기억(만약 전에 있었다고 바꿔서 기억할 것)
            } else if (!isMoveAllowed(moveFromLabel, label)){
                QMessageBox::warning(this,"Warn","This piece is not yours. Please move yours.");/*에러 메세지를 띄움*/
            } else {
                lift = true;//lift는 true으로 만들고,
                moveToLabel = label; //잡아올린 말을 기억
                moveFromLabel->setVisible(false); // 옮기기 전 위치의 라벨을 안보이게 하기
                moveToLabel->setVisible(true); // 옮긴 후 위치의 라벨을 보이게 하기
                QLabel* targetPiece;
                targetPiece = GetRemoveableTarget(moveFromLabel, moveToLabel);
                if (targetPiece != NULL){ /* 기억하고 있는 말과 클릭한 곳 사이에 말을 딸 수 있다면*/
                    hitPieces.push_back(targetPiece);
                    targetPiece->setVisible(false);
                } else {
                    //pass
                }
            }
        }
    }
