#include <QApplication>

#include "ui/MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    app.exec();
}
