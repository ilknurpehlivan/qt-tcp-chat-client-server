#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clientWorker = new TcpClientWorker(this);
    clientWorker->connectToServer("127.0.0.1", 8080);

     qDebug() << "istemci.";

    connect(clientWorker, &TcpClientWorker::newMessage, this, &MainWindow::displayMessage);
    connect(clientWorker, &TcpClientWorker::connected, this, &MainWindow::updateStatusConnected);
    connect(clientWorker, &TcpClientWorker::disconnected, this, &MainWindow::updateStatusDisconnected);
    connect(clientWorker, &TcpClientWorker::errorOccurred, this, &MainWindow::showError);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_sendMessage_clicked()
{
    QString message = ui->lineEdit_message->text().trimmed();
    if (!message.isEmpty()) {
        clientWorker->sendMessage(message);
        ui->lineEdit_message->clear();
    }
}

void MainWindow::on_pushButton_sendAttachment_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Dosya Seç", "", "Dosyalar (*.txt *.png *.jpg *.jpeg *.json)");
    if (!filePath.isEmpty()) {
        clientWorker->sendAttachment(filePath);
    }
}

void MainWindow::displayMessage(const QString &msg)
{
    ui->textBrowser_receivedMessages->append(msg);
}

void MainWindow::updateStatusConnected()
{
    ui->statusbar->showMessage("Sunucuya bağlandı.");
}

void MainWindow::updateStatusDisconnected()
{
    ui->statusbar->showMessage("Bağlantı kesildi.");
}

void MainWindow::showError(const QString &error)
{
    QMessageBox::critical(this, "Bağlantı Hatası", error);
    ui->statusbar->showMessage("Hata: " + error);
}
