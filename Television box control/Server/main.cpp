﻿#pragma execution_character_set("utf-8")
#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    w.move(1000, 200);
    w.show();
    return a.exec();
}
