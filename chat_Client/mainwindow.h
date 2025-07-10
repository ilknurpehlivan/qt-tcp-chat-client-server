#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclientworker.h"

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
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();

    void displayMessage(const QString &msg);
    void updateStatusConnected();
    void updateStatusDisconnected();
    void showError(const QString &error);

private:
    Ui::MainWindow *ui;
    TcpClientWorker *clientWorker;
};

#endif
