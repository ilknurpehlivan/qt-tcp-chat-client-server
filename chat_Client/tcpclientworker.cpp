// #include "tcpclientworker.h"
// #include <QFile>
// #include <QFileInfo>
// #include <QFileDialog>
// #include <QStandardPaths>
// #include <QMessageBox>
// #include <QDataStream>

// TcpClientWorker::TcpClientWorker(QObject *parent)
//     : QObject(parent), socket(new QTcpSocket(this))
// {
//     connect(socket, &QTcpSocket::readyRead, this, &TcpClientWorker::readSocket);
//     connect(socket, &QTcpSocket::disconnected, this, &TcpClientWorker::discardSocket);
//     connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
//             this, &TcpClientWorker::displayError);
// }

// TcpClientWorker::~TcpClientWorker()
// {
//     if (socket->isOpen())
//         socket->close();
// }

// void TcpClientWorker::connectToServer(const QString &host, quint16 port)
// {
//     socket->connectToHost(host, port);
//     if (socket->waitForConnected(3000)) {
//         emit connected();
//     } else {
//         emit errorOccurred("Sunucuya bağlanılamadı: " + socket->errorString());
//     }
// }

// void TcpClientWorker::sendMessage(const QString &message)
// {
//     if (!socket || !socket->isOpen()) return;

//     QDataStream stream(socket);
//     stream.setVersion(QDataStream::Qt_5_15);

//     QByteArray header = QString("fileType:message,fileName:null,fileSize:%1;")
//                             .arg(message.size()).toUtf8();
//     header.resize(128);

//     QByteArray data = message.toUtf8();
//     data.prepend(header);

//     stream << data;
// }


// void TcpClientWorker::sendAttachment(const QString &filePath)
// {
//     if (!socket || !socket->isOpen()) return;

//     QFile file(filePath);
//     if (!file.open(QIODevice::ReadOnly)) return;

//     QByteArray content = file.readAll();
//     QString fileName = QFileInfo(filePath).fileName();

//     QByteArray header = QString("fileType:attachment,fileName:%1,fileSize:%2;")
//                             .arg(fileName)
//                             .arg(content.size())
//                             .toUtf8();
//     header.resize(128);
//     content.prepend(header);

//     QDataStream stream(socket);
//     stream.setVersion(QDataStream::Qt_5_15);
//     stream << content;
// }

// void TcpClientWorker::readSocket()
// {
//     QDataStream stream(socket);
//     stream.setVersion(QDataStream::Qt_5_15);

//     QByteArray buffer;
//     stream.startTransaction();
//     stream >> buffer;

//     if (!stream.commitTransaction()) {
//         emit newMessage("Veri tamamlanmamış, bekleniyor...");
//         return;
//     }

//     QString header = QString::fromUtf8(buffer.left(128));
//     buffer = buffer.mid(128);

//     QString fileType = header.section(",", 0, 0).section(":", 1);
//     QString fileName = header.section(",", 1, 1).section(":", 1);
//     QString fileSizeStr = header.section(",", 2, 2).section(":", 1).section(";", 0);

//     if (fileType == "attachment") {
//         QString question = QString("Dosya (%1, %2 bytes) alındı. Kaydetmek istiyor musunuz?")
//                                .arg(fileName).arg(fileSizeStr);
//         if (QMessageBox::question(nullptr, "Dosya Al", question) == QMessageBox::Yes) {
//             QString savePath = QFileDialog::getSaveFileName(
//                 nullptr,
//                 "Dosyayı Kaydet",
//                 QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + fileName);

//             if (savePath.isEmpty()) return;

//             QFile file(savePath);
//             if (file.open(QIODevice::WriteOnly)) {
//                 file.write(buffer);
//                 emit newMessage(QString("Dosya kaydedildi: %1").arg(savePath));
//             } else {
//                 emit newMessage("Hata: Dosya kaydedilemedi.");
//             }
//         } else {
//             emit newMessage("Dosya isteği reddedildi.");
//         }
//     } else if (fileType == "message") {
//         QString message = QString("Gelen mesaj: %1").arg(QString::fromUtf8(buffer));
//         emit newMessage(message);
//     }
// }

// void TcpClientWorker::discardSocket()
// {
//     emit disconnected();
//     socket->deleteLater();
//     socket = nullptr;
// }

// void TcpClientWorker::displayError(QAbstractSocket::SocketError)
// {
//     emit errorOccurred(socket->errorString());
// }

#include "tcpclientworker.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

TcpClientWorker::TcpClientWorker(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &TcpClientWorker::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClientWorker::discardSocket);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &TcpClientWorker::displayError);
}

TcpClientWorker::~TcpClientWorker()
{
    if (socket->isOpen())
        socket->close();
}

void TcpClientWorker::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    if (socket->waitForConnected(3000)) {
        emit connected();
    } else {
        emit errorOccurred("Sunucuya bağlanılamadı: " + socket->errorString());
    }
}

void TcpClientWorker::sendMessage(const QString &message)
{
    if (!socket || !socket->isOpen()) return;

    QByteArray header = QString("fileType:message,fileName:null,fileSize:%1;")
                            .arg(message.toUtf8().size()).toUtf8();
    header.resize(128);

    QByteArray data = header + message.toUtf8();
    socket->write(data);
}

void TcpClientWorker::sendAttachment(const QString &filePath)
{
    if (!socket || !socket->isOpen()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray content = file.readAll();
    QString fileName = QFileInfo(filePath).fileName();

    QByteArray header = QString("fileType:attachment,fileName:%1,fileSize:%2;")
                            .arg(fileName)
                            .arg(content.size())
                            .toUtf8();
    header.resize(128);

    QByteArray data = header + content;
    socket->write(data);
}

void TcpClientWorker::readSocket()
{
    QByteArray buffer = socket->readAll();
    if (buffer.size() < 128) {
        emit newMessage("Veri tamamlanmamış, bekleniyor...");
        return;
    }

    QString header = QString::fromUtf8(buffer.left(128));
    buffer = buffer.mid(128);

    QString fileType = header.section(",", 0, 0).section(":", 1);
    QString fileName = header.section(",", 1, 1).section(":", 1);
    QString fileSizeStr = header.section(",", 2, 2).section(":", 1).section(";", 0);

    if (fileType == "attachment") {
        QString question = QString("Dosya (%1, %2 bytes) alındı. Kaydetmek istiyor musunuz?")
                               .arg(fileName).arg(fileSizeStr);
        if (QMessageBox::question(nullptr, "Dosya Al", question) == QMessageBox::Yes) {
            QString savePath = QFileDialog::getSaveFileName(
                nullptr,
                "Dosyayı Kaydet",
                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + fileName);

            if (savePath.isEmpty()) return;

            QFile file(savePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(buffer);
                emit newMessage(QString("Dosya kaydedildi: %1").arg(savePath));
            } else {
                emit newMessage("Hata: Dosya kaydedilemedi.");
            }
        } else {
            emit newMessage("Dosya isteği reddedildi.");
        }
    } else if (fileType == "message") {
        QString message = QString("Gelen mesaj: %1").arg(QString::fromUtf8(buffer));
        emit newMessage(message);
    }
}

void TcpClientWorker::discardSocket()
{
    emit disconnected();
    socket->deleteLater();
    socket = nullptr;
}

void TcpClientWorker::displayError(QAbstractSocket::SocketError)
{
    emit errorOccurred(socket->errorString());
}
