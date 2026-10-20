#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*
обращаться либо только к модели, либо только к полям - это называется не прыгать по уровням
добавить трансформ модел где передавать указатель на функийю
*/