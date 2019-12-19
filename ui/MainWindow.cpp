//
// Created by chris on 19/12/2019.
//

#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QApplication>

#include "RenderWindow.h"

MainWindow::MainWindow():
    QMainWindow(),
    MdiArea()
{
    setWindowTitle(tr("RayTracer"));

    auto *mb = menuBar();
    auto *fileMenu = mb->addMenu(tr("&File"));

    fileMenu->addAction(QIcon::fromTheme("document-new"), tr("&New"), this, &MainWindow::FileNew);
//    fileMenu->addAction(QIcon::fromTheme("document-open"), tr("&Open..."), this, &MainWindow::FileOpen);
    fileMenu->addAction(QIcon::fromTheme("document-save-as"), tr("&Save as..."), this, &MainWindow::FileSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon::fromTheme("application-exit"), tr("E&xit"), QApplication::instance(), &QApplication::closeAllWindows);

    auto *renderMenu = mb->addMenu(tr("&Render"));
    renderMenu->addAction(tr("&Start"), this, &MainWindow::RenderStart);
//    renderMenu->addAction(tr("&Pause"), this, &MainWindow::RenderPause);
//    renderMenu->addAction(tr("&Resume"), this, &MainWindow::RenderResume);

    setCentralWidget(&MdiArea);

    auto *sb = statusBar();

    connect(&MdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::focusSubWindow);
}

void
MainWindow::FileNew()
{
    auto *subWindow = new RenderWindow(QSize(640,480));
    MdiArea.addSubWindow(subWindow);
    subWindow->show();
}

void MainWindow::RenderStart() {
    auto *current = MdiArea.activeSubWindow();

    auto *renderWindow = dynamic_cast<RenderWindow *>(current);
    if (nullptr != renderWindow) {
        renderWindow->RenderStart();
    }
}

void MainWindow::RenderPause() {

}

void MainWindow::RenderResume() {

}

void MainWindow::FileOpen() {

}

void MainWindow::FileSaveAs() {
    auto *current = MdiArea.activeSubWindow();

    auto *renderWindow = dynamic_cast<RenderWindow *>(current);
    if (nullptr != renderWindow) {
        renderWindow->SaveAs();
    }
}

void
MainWindow::focusSubWindow(QMdiSubWindow *window)
{
}
