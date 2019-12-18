//
// Created by chris on 19/12/2019.
//

#include "RenderWindow.h"

#include <QScrollArea>
#include <QColor>

RenderWindow::RenderWindow(QSize size):
    QMdiSubWindow(),
    Canvas(size),
    imageLabel()
{
    imageLabel.setPixmap(Canvas);
    imageLabel.setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(&imageLabel);
}

void RenderWindow::SaveAs() {

}

void RenderWindow::RenderStart() {
    theWorld = std::make_shared<World>();

    setStatus(tr("Building world..."));
    theWorld->build();

    setStatus(tr("Rendering..."));

    pixelsRendered = 0;
    pixelsToRender = Canvas.width() * Canvas.height();

    //set the background
    Canvas.fill(QColor("darkGray"));

    updateTimer.setInterval(250);
    updateTimer.start();

    timer.start();

    //FIXME: start the actual renderer...

//    thread = new RenderThread(this, w);
//    thread->Create();
//    w->paintArea = thread;
//    thread->SetPriority(20);
//    thread->Run();
}

void RenderWindow::RenderPause() {

}

void RenderWindow::RenderResume() {

}

void RenderWindow::updateEvent() {

}

QString RenderWindow::getStatus() const {
    return statusText;
}

void
RenderWindow::setStatus(const QString &newStatus) {
    statusText = newStatus;
    emit StatusUpdated(statusText);
}
