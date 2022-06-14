#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private:

    QTcpSocket *TcpSocket;

private slots:
    void incomingConnection(qintptr handle);
    void receiveMessage();

signals:
    void buf(QString str);

};

#endif // SERVER_H
