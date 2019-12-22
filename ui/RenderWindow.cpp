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
    ThreadsPending(0),
    imageLabel(),
    RawImageBacking(),
    backingWidth(0),
    backingHeight(0)
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

    pixelsToRender = CanvasBacking->width() * CanvasBacking->height();
    pixelsRendered.store(0);

    updateTimer.setInterval(200);
    connect(&updateTimer, &QTimer::timeout, this, &RenderWindow::updateEvent);
    updateTimer.start();

    timer.start();

    //FIXME: start the actual renderer...
    theWorld->paintArea = this;
    unsigned maxThreads = theWorld->camera_ptr->max_render_threads(*theWorld);
    unsigned workThreadCount = std::min<unsigned>(maxThreads, QThread::idealThreadCount());
    ThreadsPending.store(workThreadCount);
    for (unsigned t = 0; t < workThreadCount; t++) {
        auto *thr = new RenderThread(theWorld, t, workThreadCount);
        connect(thr, &RenderThread::finished, thr, &QObject::deleteLater);
        // these two are threadsafe and must have min latency.  use DirectConnection only.
        connect(thr, &RenderThread::finished, this, &RenderWindow::threadFinished);
        thr->start();
    }
}

void RenderWindow::threadFinished() {
    auto i = ThreadsPending.fetchAndSubOrdered(1);
    if (i == 1) {
        renderFinished();
    }
}

void RenderWindow::renderFinished() {
    // stop the periodic and overall time timers.
    updateTimer.stop();
    totalTime += timer.elapsed();

    // redraw.
    scheduleRedraw();
    setStatus(tr("Render Complete.  Took %1 ms").arg(totalTime));

    theWorld.reset();
}

void RenderWindow::newBackingImage(int width, int height) {
    CanvasBacking.reset();
    RawImageBacking.clear();
    backingWidth = width;
    backingHeight = height;
    RawImageBacking.resize(width * height * 4);
    CanvasBacking = QSharedPointer<QImage>::create(RawImageBacking.data(), width, height, QImage::Format_RGBA8888);
    //CanvasBacking->fill(QColor("darkGray"));
    scheduleRedraw();
}

void
RenderWindow::setPixel(int x, int y, int r, int g, int b)
{
    unsigned char *wp = &RawImageBacking[(x + (y * backingWidth)) * 4];
    *(wp++) = r;
    *(wp++) = g;
    *(wp++) = b;
    *wp = 0xFF;
    pixelsRendered++;
}

void RenderWindow::RenderPause() {

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

QSize RenderWindow::sizeHint() const {
    return {400, 400};
}
