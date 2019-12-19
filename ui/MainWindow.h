//
// Created by chris on 19/12/2019.
//

#ifndef RAYTRACER_MAINWINDOW_H
#define RAYTRACER_MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>

class QMdiSubWindow;

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

    QMdiArea MdiArea;

public slots:
    void focusSubWindow(QMdiSubWindow *window);

    void FileNew();
    void FileOpen();
    void FileSaveAs();
    void RenderStart();
    void RenderPause();
    void RenderResume();
};


#endif //RAYTRACER_MAINWINDOW_H
