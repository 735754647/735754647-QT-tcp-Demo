#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();


private slots:


    void socket_Read_Data();

    void socket_Disconnected();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *socket;
};
#endif // CLIENT_H
