#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();
    w.move(400, 200);
    return a.exec();
}
