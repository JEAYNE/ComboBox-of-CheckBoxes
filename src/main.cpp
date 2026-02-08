// SPDX-License-Identifier: GPL-3.0-only

#include "src/mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow   window;
    window.show();
    return app.exec();
}
