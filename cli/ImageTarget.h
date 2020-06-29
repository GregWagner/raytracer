//
// Created by chris on 30/06/2020.
//

#ifndef RAYTRACER_IMAGETARGET_H
#define RAYTRACER_IMAGETARGET_H

#include <cstdint>
#include <string>
#include "../Utilities/RenderTarget.h"

class ImageTarget: public RenderTarget {
public:
    ImageTarget(intptr_t width, intptr_t height);
    virtual ~ImageTarget();

    void setPixel(int x, int y, int r, int g, int b) override;

    bool saveImage(const std::string &filename);

protected:
    const intptr_t bytesPerPixel = 3;

    unsigned char *imageData;
    intptr_t width;
    intptr_t height;
};


#endif //RAYTRACER_IMAGETARGET_H
