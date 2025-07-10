// tcpclientworker.h
#ifndef TCPCLIENTWORKER_H
#define TCPCLIENTWORKER_H

#include <QObject>
#include <QTcpSocket>

class TcpClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientWorker(QObject *parent = nullptr);
    ~TcpClientWorker();

    void connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message);
    void sendAttachment(const QString &filePath);


signals:
    void newMessage(const QString &msg);
    void connected();
    void disconnected();
    void errorOccurred(const QString &error);

private slots:
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
};



#endif
