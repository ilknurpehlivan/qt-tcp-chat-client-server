#ifndef TCPWORKER_H
#define TCPWORKER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class TcpWorker : public QObject
{
    Q_OBJECT
public:
    explicit TcpWorker(QObject *parent = nullptr);
    ~TcpWorker();

    void startServer(quint16 port = 8080);
    void sendMessageTo(qintptr socketId, const QString &message);
    void sendAttachmentTo(qintptr socketId, const QString &filePath);

    QStringList getClientIdList() const;

signals:
    void messageReady(const QString &msg);
    void clientListChanged();

private slots:
    void handleNewConnection();
    void readFromSocket();
    void clientDisconnected();

private:
    QTcpServer *server;
    QMap<qintptr, QTcpSocket*> clients;

    // void broadcastMessage(const QByteArray &data);
    void broadcastMessage(const QByteArray &data, QTcpSocket* exclude);
    void broadcastMessage(const QByteArray &data);


    void sendToSocket(QTcpSocket* socket, const QByteArray &data);
};

#endif
