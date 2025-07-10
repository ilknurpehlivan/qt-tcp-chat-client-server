#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TcpWorker;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();

    void displayMessage(const QString &msg);
    void updateClientList();

private:
    Ui::MainWindow *ui;
    TcpWorker *worker;

    void refreshComboBox();
};

#endif
