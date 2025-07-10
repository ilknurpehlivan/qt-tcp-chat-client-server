#include "tcpworker.h"
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QDebug>

TcpWorker::TcpWorker(QObject *parent)
    : QObject(parent), server(new QTcpServer(this))
{
    connect(server, &QTcpServer::newConnection, this, &TcpWorker::handleNewConnection);
}

TcpWorker::~TcpWorker()
{
    server->close();
    qDeleteAll(clients);
}

void TcpWorker::startServer(quint16 port)
{
    if (!server->listen(QHostAddress::Any, port)) { //any ip'yi dinliyor.
        emit messageReady("HATA: Sunucu başlatılamadı: " + server->errorString());
    } else {
        emit messageReady("Sunucu " + QString::number(port) + " portunda başlatıldı.");
    }
}

void TcpWorker::handleNewConnection()
{

    qDebug() << "Yeni bağlantı geldi!";
    while (server->hasPendingConnections()) {
        QTcpSocket *socket = server->nextPendingConnection();
        qintptr id = socket->socketDescriptor();
        clients[id] = socket;

        connect(socket, &QTcpSocket::readyRead, this, &TcpWorker::readFromSocket);
        connect(socket, &QTcpSocket::disconnected, this, &TcpWorker::clientDisconnected);

        emit messageReady(QString("Yeni istemci bağlandı: %1").arg(id));
        emit clientListChanged();
    }
}

void TcpWorker::readFromSocket()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_5_15);

    QByteArray buffer;
    stream.startTransaction();
    stream >> buffer;

    if (!stream.commitTransaction()) return;

    QString header = QString::fromUtf8(buffer.left(128));
    QString type;

    int colonIndex = header.indexOf(":");
    int commaIndex = header.indexOf(",");
    if (colonIndex != -1 && commaIndex != -1 && commaIndex > colonIndex) {
        type = header.mid(colonIndex + 1, commaIndex - colonIndex - 1);
    }

    buffer = buffer.mid(128);
    qintptr id = socket->socketDescriptor();

    if (type == "message") {
        QString msg = QString("[%1] %2").arg(id).arg(QString::fromUtf8(buffer));
        emit messageReady(msg);
        QByteArray headerBytes = header.toUtf8();
        buffer.prepend(headerBytes);
        broadcastMessage(buffer);
    } else if (type == "attachment") {
        emit messageReady(QString("İstemci %1 bir dosya gönderdi.").arg(id));
        // Gerekirse buraya dosya kaydetme de eklenebilir
    }
}



void TcpWorker::clientDisconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    qintptr id = socket->socketDescriptor();
    clients.remove(id);
    socket->deleteLater();

    emit messageReady(QString("İstemci %1 bağlantıyı kapattı.").arg(id));
    emit clientListChanged();
}

void TcpWorker::broadcastMessage(const QByteArray &data)
{
    for (auto it = clients.constBegin(); it != clients.constEnd(); ++it)
        sendToSocket(it.value(), data);

}

void TcpWorker::sendToSocket(QTcpSocket* socket, const QByteArray &data)
{
    if (socket && socket->isOpen()) {
        QDataStream stream(socket);
        stream.setVersion(QDataStream::Qt_5_15);
        stream << data;
    }
}

void TcpWorker::sendMessageTo(qintptr socketId, const QString &message)
{
    QByteArray header = QString("fileType:message,fileName:null,fileSize:%1;").arg(message.size()).toUtf8();
    header.resize(128);
    QByteArray data = message.toUtf8();
    data.prepend(header);

    if (socketId == -1) {
        broadcastMessage(data);
    } else if (clients.contains(socketId)) {
        sendToSocket(clients[socketId], data);
    }
}


void TcpWorker::sendAttachmentTo(qintptr socketId, const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray content = file.readAll();
    QString fileName = QFileInfo(filePath).fileName();
    QByteArray header = QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(content.size()).toUtf8();
    header.resize(128);
    content.prepend(header);

    if (socketId == -1) {
        broadcastMessage(content);
    } else if (clients.contains(socketId)) {
        sendToSocket(clients[socketId], content);
    }
}

QStringList TcpWorker::getClientIdList() const
{
    QStringList list;
    for (auto it = clients.constBegin(); it != clients.constEnd(); ++it) {
        list << QString::number(it.key());
    }
    return list;
}
