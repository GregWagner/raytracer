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
    RenderThread(std::shared_ptr<World> world);

    void run() override;

    void setPixel(int x, int y, int red, int green, int blue);

signals:
    void pixel(int x, int y, int red, int green, int blue);

protected:
    std::shared_ptr<World>      world;

};


#endif //RAYTRACER_RENDERTHREAD_H
