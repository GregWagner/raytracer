//
// Created by chris on 19/12/2019.
//

#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QApplication>

MainWindow::MainWindow():
    QMainWindow(),
    MdiArea()
{
    setWindowTitle(tr("RayTracer"));

    auto *mb = menuBar();
    auto *fileMenu = mb->addMenu(tr("&File"));

    fileMenu->addAction(QIcon::fromTheme("document-open"), tr("&Open..."), this, &MainWindow::FileOpen);
    fileMenu->addAction(QIcon::fromTheme("document-save-as"), tr("&Save as..."), this, &MainWindow::FileSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon::fromTheme("application-exit"), tr("E&xit"), QApplication::instance(), &QApplication::closeAllWindows);

    auto *renderMenu = mb->addMenu(tr("&Render"));
    renderMenu->addAction(tr("&Start"), this, &MainWindow::RenderStart);
    renderMenu->addAction(tr("&Pause"), this, &MainWindow::RenderPause);
    renderMenu->addAction(tr("&Resume"), this, &MainWindow::RenderResume);

    setCentralWidget(&MdiArea);
}

void MainWindow::RenderStart() {

}

void MainWindow::RenderPause() {

}

void MainWindow::RenderResume() {

}

void MainWindow::FileOpen() {

}

void MainWindow::FileSaveAs() {

}
