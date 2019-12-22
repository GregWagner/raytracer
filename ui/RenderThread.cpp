//
// Created by kuroneko on 19/12/19.
//

#include "RenderThread.h"

RenderThread::RenderThread(const std::shared_ptr<World> &w, int threadNumber, int threadsTotal):
    QThread(),
    threadNumber(threadNumber),
    threadsTotal(threadsTotal),
    world(w)
{
}

void
RenderThread::run()
{
    this->world->camera_ptr->render_scene(*this->world, threadNumber, threadsTotal);
}
