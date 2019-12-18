//
// Created by chris on 19/12/2019.
//

#ifndef RAYTRACER_RENDERWINDOW_H
#define RAYTRACER_RENDERWINDOW_H

#include <QMdiSubWindow>
#include <QSize>
#include <QLabel>
#include <QThread>
#include <QElapsedTimer>
#include <QTimer>

#include <memory>

#include "../World/World.h"

class RenderWindow : public QMdiSubWindow {
Q_OBJECT
public:
    RenderWindow(QSize size);

    QPixmap Canvas;

    QString getStatus() const;

public slots:

    void SaveAs();

    void RenderStart();

    void RenderPause();

    void RenderResume();

    void updateEvent();

signals:
    void RenderComplete();
    void StatusUpdated(QString newStatus);

protected:
    QLabel imageLabel;
    QThread *renderThread;
    QElapsedTimer timer;
    QTimer updateTimer;

    unsigned long pixelsRendered;
    unsigned long pixelsToRender;

    std::shared_ptr<World>   theWorld;

    void setStatus(const QString &newStatus);

private:
    QString statusText;
};


#endif //RAYTRACER_RENDERWINDOW_H
