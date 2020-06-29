//
// Created by chris on 30/06/2020.
//

#include <cstring>
#include "ImageTarget.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

ImageTarget::ImageTarget(intptr_t width, intptr_t height):
    width(width), height(height)
{
    const intptr_t dataSize = width*height*bytesPerPixel;
    imageData = new unsigned char[dataSize];
    memset(imageData, 0, dataSize);
}

ImageTarget::~ImageTarget() {
    delete[] imageData;
}

void ImageTarget::setPixel(int x, int y, int r, int g, int b) {
    intptr_t baseOffset = (static_cast<intptr_t>(x) + (static_cast<intptr_t>(y) * width)) * bytesPerPixel;

    imageData[baseOffset] = r;
    imageData[baseOffset+1] = g;
    imageData[baseOffset+2] = b;
}

bool ImageTarget::saveImage(const std::string &filename) {
    return stbi_write_png(filename.c_str(), width, height, bytesPerPixel, imageData, width*bytesPerPixel) != 0;
}

