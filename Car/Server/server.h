#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:

    void server_New_Connect();

    void socket_Read_Data();

    void socket_Disconnected();

private:
    Ui::Server *ui;
    QTcpServer* server;
    QTcpSocket* socket;
};
#endif // SERVER_H
