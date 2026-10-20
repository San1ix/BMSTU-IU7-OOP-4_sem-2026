#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "exception/base_exception.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    try
    {
        MainWindow window;
        window.show();
        return app.exec();
    }
    catch (const BaseException& e)
    {
        QMessageBox::critical(nullptr, "Error", e.what());
        return 1;
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error", e.what());
        return 1;
    }
}