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
private slots:

    void on_RuleButton_clicked();

    void on_StartButton_clicked();

    void on_ResetButton_clicked();

    void on_BackButton_clicked();

    void on_StartButton_2_clicked();

    void on_HomeButton_clicked();

private:
    Ui::MainWindow *ui;

    QList<QLabel*> bluePieceLabels;
    QList<QLabel*> yellowPieceLabels;
    QList<QPushButton*> bluePieceButtons;
    QList<QPushButton*> yellowPieceButtons;
    QList<QLabel*> boardLabels;
    QList<QPushButton*> buttons;

//    void on_slot_clicked();
    void on_button_clicked();

    int turn;
};
#endif // MAINWINDOW_H
