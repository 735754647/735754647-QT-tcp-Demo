#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include<QTime>
#include<QLineEdit>
#include<QTimerEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
   QTimer * time;//定时器
private slots:

    void on_timeEdit_userTimeChanged(const QTime &time);

    void server_New_Connect();

    void socket_Read_Data();

    void socket_Disconnected();

protected:
    void timerEvent(QTimerEvent *);

private:
    Ui::Server *ui;
    QTcpServer* server;
    QTcpSocket* socket;

    QTime timeSet;
    QLineEdit lineEditGet;
    int setSecond;
    int timerId;
    bool hasSetTime;
    bool btnStartHasClick;
    bool isStop;

};
#endif // SERVER_H
