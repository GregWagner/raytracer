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

RenderWindow::RenderWindow(QSize size):
    QMdiSubWindow(),
    CanvasBacking(size, QImage::Format::Format_RGB888),
    Canvas(),
    imageLabel()
{
    totalTime = 0;
    CanvasBacking.fill(QColor("darkGray"));

    imageLabel.setPixmap(QPixmap::fromImage(CanvasBacking));
    imageLabel.setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(&imageLabel);
    setWidget(scrollArea);

}

void RenderWindow::SaveAs() {

    auto filename = QFileDialog::getSaveFileName(this,
        tr("Save Image As..."),
        "",
        tr("Windows Bitmap (*.bmp);;JPEG Image (*.jpeg);;Portable Network Graphics (*.png);;Portable Pixmap (*.ppm)"));
    if (filename.isEmpty()) {
        return;
    }
    auto didSave = CanvasBacking.save(filename);
    if (!didSave) {
        QMessageBox error(QMessageBox::Icon::Critical, tr("Save As..."),
            tr("An error occurred whilst saving the file \"%1\".").arg(filename));
        error.exec();
        return;
    }
}

void RenderWindow::RenderStart() {
    theWorld = std::make_shared<World>();

    setStatus(tr("Building world..."));
    theWorld->build();

    setStatus(tr("Rendering..."));

    pixelsRendered = 0;
    pixelsToRender = CanvasBacking.width() * CanvasBacking.height();

    //set the background
    CanvasBacking.fill(QColor("darkGray"));
    scheduleRedraw();

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

void
RenderWindow::setPixel(int x, int y, int r, int g, int b)
{
    CanvasBacking.setPixelColor(x, y, QColor(r,g,b));
}

void RenderWindow::RenderPause() {

}

void
RenderWindow::renderComplete()
{
    // stop the periodic and overall time timers.
    updateTimer.stop();
    totalTime += timer.elapsed();

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
    imageLabel.setPixmap(QPixmap::fromImage(CanvasBacking));
}
