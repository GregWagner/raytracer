//
// Created by kuroneko on 19/12/19.
//

#include "RenderThread.h"

RenderThread::RenderThread(std::shared_ptr<World> w):
    QThread(),
    world(w)
{
}

void
RenderThread::run()
{
    world->paintArea = this;
    world->camera_ptr->render_scene(*world);
}

void
RenderThread::setPixel(int x, int y, int red, int green, int blue)
{
    emit pixel(x, y, red, green, blue);
}
