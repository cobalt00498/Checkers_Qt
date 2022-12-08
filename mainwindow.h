#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qlabel.h"
#include "QtWidgets/qpushbutton.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resetGameStatus();
private slots:

    void on_SettingsButton_clicked();

    void on_RuleButton_clicked();

    void on_PlayButton_clicked();

    void on_CPUPlayButton_clicked();

    void on_ExitButton_clicked();

    void on_BackButton_clicked();

    void on_PlayButton2_clicked();

    void on_HomeButton_clicked();

    void on_ResetButton_clicked();

    void on_HomeButton2_clicked();

    void on_ExitButton2_clicked();

    void on_NoButton3_clicked();

    void on_YesButton3_clicked();

    void on_ReplayButton_clicked();

    void on_BackButton_2_clicked();

    void on_PlayButton3_clicked();

    //Settings
    void on_BoardButton_1_clicked();
    void on_BoardButton_2_clicked();
    void on_BoardButton_3_clicked();
    void on_BoardButton_4_clicked();
    void on_BoardButton_5_clicked();
    void on_BoardButton_6_clicked();
    void on_BoardButton_7_clicked();
    void on_BoardButton_8_clicked();
    void on_BoardButton_9_clicked();
    void on_PieceButton_1_clicked();
    void on_PieceButton_2_clicked();
    void on_PieceButton_3_clicked();
    void on_PieceButton_4_clicked();
    void on_PieceButton_5_clicked();
    void on_PieceButton_6_clicked();
    void on_PieceButton_7_clicked();
    void on_PieceButton_8_clicked();
    void on_PieceButton_9_clicked();

    void on_Player1Button_clicked();

    void on_Player2Button_clicked();

    void on_CloseButton_clicked();

    void on_YesButton2_clicked();

    void on_NoButton2_clicked();

private:
    Ui::MainWindow *ui;
    QList<QLabel*> player1PieceLabels;
    QList<QLabel*> player2PieceLabels;
    QList<QPushButton*> boardButtons;

    void on_button_clicked();

    int turn;
};
#endif // MAINWINDOW_H
