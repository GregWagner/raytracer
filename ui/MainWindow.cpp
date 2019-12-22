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
    MdiArea(),
    useMultithreading(true)
{
    setWindowTitle(tr("RayTracer"));

    if (QThread::idealThreadCount() <= 2) {
        useMultithreading = false;
    }

    auto *mb = menuBar();
    auto *fileMenu = mb->addMenu(tr("&File"));

    fileMenu->addAction(QIcon::fromTheme("document-new"), tr("&New"), this, &MainWindow::FileNew);
//    fileMenu->addAction(QIcon::fromTheme("document-open"), tr("&Open..."), this, &MainWindow::FileOpen);
    ActionFileSaveAs = fileMenu->addAction(QIcon::fromTheme("document-save-as"), tr("&Save as..."), this, &MainWindow::FileSaveAs);
    ActionFileSaveAs->setEnabled(false);
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon::fromTheme("application-exit"), tr("E&xit"), QApplication::instance(), &QApplication::closeAllWindows);

    auto *renderMenu = mb->addMenu(tr("&Render"));
    MultiThreadedRendering = renderMenu->addAction(tr("Enable &Multithreaded Renderer"), this, &MainWindow::RenderToggleMultithreading);
    MultiThreadedRendering->setCheckable(true);
    MultiThreadedRendering->setChecked(useMultithreading);
    if (QThread::idealThreadCount() <= 1) {
        MultiThreadedRendering->setEnabled(false);
    }

    ActionRenderStart = renderMenu->addAction(tr("&Start"), this, &MainWindow::RenderStart);
    ActionRenderStart->setEnabled(false);
//    renderMenu->addAction(tr("&Pause"), this, &MainWindow::RenderPause);
//    renderMenu->addAction(tr("&Resume"), this, &MainWindow::RenderResume);

    setCentralWidget(&MdiArea);

    auto *sb = statusBar();

    connect(&MdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::focusSubWindow);

    FileNew();
}

void MainWindow::RenderToggleMultithreading() {
    useMultithreading = !useMultithreading;
    MultiThreadedRendering->setChecked(useMultithreading);
}

void
MainWindow::FileNew()
{
    auto *subWindow = new RenderWindow();
    MdiArea.addSubWindow(subWindow);
    connect(subWindow, &RenderWindow::ActionsUpdated,  this, &MainWindow::updateMenusForFocus);
    subWindow->show();
}

void MainWindow::RenderStart() {
    auto *current = MdiArea.activeSubWindow();

    auto *renderWindow = dynamic_cast<RenderWindow *>(current);
    if (nullptr != renderWindow) {
        renderWindow->RenderStart(useMultithreading);
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
    updateMenusForFocus();
}

void MainWindow::updateMenusForFocus() {
    auto *window = MdiArea.currentSubWindow();
    RenderWindow *wrecast = (window != nullptr)?dynamic_cast<RenderWindow *>(window):nullptr;
    if (wrecast == nullptr) {
        // no window, or non-render, don't bother.
        ActionRenderStart->setEnabled(false);
        ActionFileSaveAs->setEnabled(false);
        return;
    }
    // only enable File Save As if there's something to save.
    ActionRenderStart->setEnabled(!wrecast->isRendering());
    ActionFileSaveAs->setEnabled(wrecast->CanvasBacking);
}


