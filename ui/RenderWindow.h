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
#include "../Utilities/RenderTarget.h"

class RenderWindow : public QMdiSubWindow, public RenderTarget {
Q_OBJECT
public:
    RenderWindow();

    QSharedPointer<QImage> CanvasBacking;
    QPainter Canvas;

    QSize sizeHint() const override;

    QString getStatus() const;

    std::vector<unsigned char> RawImageBacking;
    unsigned backingWidth;
    unsigned backingHeight;

    /** setPixel sets a pixel on the current backing.  It's NOT synchronised (on purpose), so
     * having two threads hit the same pixel simultaneously is undefined.
     *
     * This is exposed so the RayTracing Camera API can hit it directly.
     *
     * @param x x coordinate.  Must be within the bounds expected after the last newBackingImage call.
     * @param y y coordinate.  Must be within the bounds expected after the last newBackingImage call.
     * @param r Red component - 0-255 range.
     * @param g Green component - 0-255 range.
     * @param b Blue component - 0-255 range.
     */
    void setPixel(int x, int y, int r, int g, int b) override;

    bool isRendering() const;

public slots:
    void SaveAs();

    void RenderStart(bool useMultithreading);

    void RenderPause();

    void RenderResume();

    void updateEvent();

protected slots:
    void threadFinished();

signals:
    void StatusUpdated(QString newStatus);
    void ActionsUpdated();

protected:
    void renderFinished();
    void scheduleRedraw();

    QAtomicInt ThreadsPending;
    QLabel imageLabel;
    QElapsedTimer timer;
    QTimer updateTimer;

    QAtomicInt pixelsRendered;
    unsigned long pixelsToRender;
    qint64 totalTime;

    std::shared_ptr<World>   theWorld;

    void setStatus(const QString &newStatus);

    void newBackingImage(int width, int height);
};


#endif //RAYTRACER_RENDERWINDOW_H
