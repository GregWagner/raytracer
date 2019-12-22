//
// Created by kuroneko on 19/12/19.
//

#ifndef RAYTRACER_RENDERTHREAD_H
#define RAYTRACER_RENDERTHREAD_H

#include <memory>
#include <QObject>
#include <QThread>

#include "../World/World.h"

class RenderThread: public QThread
{
    Q_OBJECT
public:
    RenderThread(const std::shared_ptr<World> &world, int threadNumber=0, int threadsTotal=1);

    void run() override;

protected:
    int         threadNumber;
    int         threadsTotal;
    std::shared_ptr<World>      world;
};


#endif //RAYTRACER_RENDERTHREAD_H
