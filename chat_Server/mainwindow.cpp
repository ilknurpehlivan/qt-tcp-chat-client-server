#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpworker.h"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox_receiver->addItem("Broadcast");

    worker = new TcpWorker(this);
    worker->startServer(8080);
    qDebug() << " Server başlatıldı, 8080 portu dinleniyor.";

    connect(worker, &TcpWorker::messageReady, this, &MainWindow::displayMessage);
    connect(worker, &TcpWorker::clientListChanged, this, &MainWindow::updateClientList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_sendMessage_clicked()
{
    QString message = ui->lineEdit_message->text();
    if (message.isEmpty()) return;

    QString target = ui->comboBox_receiver->currentText();
    qintptr id = (target == "Broadcast") ? -1 : target.toLongLong();

    worker->sendMessageTo(id, message);
    ui->lineEdit_message->clear();
}

void MainWindow::on_pushButton_sendAttachment_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Dosya Seç");
    if (filePath.isEmpty()) return;

    QString target = ui->comboBox_receiver->currentText();
    qintptr id = (target == "Broadcast") ? -1 : target.toLongLong();

    worker->sendAttachmentTo(id, filePath);
}

void MainWindow::displayMessage(const QString &msg)
{
    ui->textEdit->append(msg);
}

void MainWindow::updateClientList()
{
    ui->comboBox_receiver->clear();
    ui->comboBox_receiver->addItem("Broadcast");

    for (const QString &idStr : worker->getClientIdList()) {
        ui->comboBox_receiver->addItem(idStr);
    }
}
