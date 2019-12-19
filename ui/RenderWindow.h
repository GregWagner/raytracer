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
#include <QPainter>

#include <memory>

#include "../World/World.h"

class RenderWindow : public QMdiSubWindow {
Q_OBJECT
public:
    RenderWindow(QSize size);

    QImage CanvasBacking;
    QPainter Canvas;

    QString getStatus() const;

public slots:

    void setPixel(int x, int y, int r, int g, int b);

    void renderComplete();



    void SaveAs();

    void RenderStart();

    void RenderPause();

    void RenderResume();

    void updateEvent();

signals:
    void StatusUpdated(QString newStatus);

protected:
    void scheduleRedraw();

    QLabel imageLabel;
    RenderThread *renderThread;
    QElapsedTimer timer;
    QTimer updateTimer;

    unsigned long pixelsRendered;
    unsigned long pixelsToRender;
    qint64 totalTime;

    std::shared_ptr<World>   theWorld;

    void setStatus(const QString &newStatus);
};


#endif //RAYTRACER_RENDERWINDOW_H
