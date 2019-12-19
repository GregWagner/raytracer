//
// Created by chris on 19/12/2019.
//

#include "RenderWindow.h"

#include <QScrollArea>
#include <QColor>
#include <QImage>
#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>

#include "RenderThread.h"

RenderWindow::RenderWindow() :
    QMdiSubWindow(),
    CanvasBacking(),
    Canvas(),
    imageLabel()
{
    totalTime = 0;

    imageLabel.setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(&imageLabel);
    setWidget(scrollArea);
}

void RenderWindow::SaveAs() {
    if (CanvasBacking) {
        auto filename = QFileDialog::getSaveFileName(this,
                                                     tr("Save Image As..."),
                                                     "",
                                                     tr("Windows Bitmap (*.bmp);;JPEG Image (*.jpeg);;Portable Network Graphics (*.png);;Portable Pixmap (*.ppm)"));
        if (filename.isEmpty()) {
            return;
        }
        auto didSave = CanvasBacking->save(filename);
        if (!didSave) {
            QMessageBox error(QMessageBox::Icon::Critical, tr("Save As..."),
                              tr("An error occurred whilst saving the file \"%1\".").arg(filename));
            error.exec();
            return;
        }
    } else {
        QMessageBox error(QMessageBox::Icon::Critical, tr("Save As..."),
                          tr("There's no image to save."));
        error.exec();
    }
}

void RenderWindow::RenderStart() {
    theWorld = std::make_shared<World>();

    setStatus(tr("Building world..."));
    theWorld->build();

    setStatus(tr("Creating Canvas..."));
    newBackingImage(theWorld->vp.hres, theWorld->vp.vres);

    setStatus(tr("Rendering..."));

    pixelsRendered = 0;
    pixelsToRender = CanvasBacking->width() * CanvasBacking->height();

    updateTimer.setInterval(250);
    connect(&updateTimer, &QTimer::timeout, this, &RenderWindow::updateEvent);
    updateTimer.start();

    timer.start();

    //FIXME: start the actual renderer...
    renderThread = new RenderThread(theWorld);
    connect(renderThread, &RenderThread::pixel, this, &RenderWindow::setPixel, Qt::QueuedConnection);
    connect(renderThread, &RenderThread::finished, this, &RenderWindow::renderComplete, Qt::QueuedConnection);
    renderThread->start(QThread::Priority::LowPriority);
}

void RenderWindow::newBackingImage(int width, int height) {
    CanvasBacking = QSharedPointer<QImage>::create(width, height, QImage::Format_RGB888);
    CanvasBacking->fill(QColor("darkGray"));
    scheduleRedraw();
}

void
RenderWindow::setPixel(int x, int y, int r, int g, int b)
{
    if (CanvasBacking) {
        CanvasBacking->setPixelColor(x, y, QColor(r, g, b));
        pixelsRendered++;
    }
}

void RenderWindow::RenderPause() {

}

void
RenderWindow::renderComplete()
{
    // stop the periodic and overall time timers.
    updateTimer.stop();
    totalTime += timer.elapsed();

    disconnect(renderThread, nullptr, nullptr, nullptr);
    delete renderThread;
    renderThread = nullptr;

    scheduleRedraw();
    setStatus(tr("Render Complete.  Took %1 ms").arg(totalTime));

    theWorld.reset();
}

void RenderWindow::RenderResume() {

}

void RenderWindow::updateEvent() {
    scheduleRedraw();
}

QString RenderWindow::getStatus() const {
    return statusTip();
}

void
RenderWindow::setStatus(const QString &newStatus) {
    setStatusTip(newStatus);
    emit StatusUpdated(newStatus);
}

void
RenderWindow::scheduleRedraw()
{
    if (CanvasBacking) {
        imageLabel.setPixmap(QPixmap::fromImage(*CanvasBacking));
        imageLabel.resize(CanvasBacking->size());
    } else {
        imageLabel.clear();
    }
}
