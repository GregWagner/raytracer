//
// Created by chris on 30/06/2020.
//

#ifndef RAYTRACER_RENDERTARGET_H
#define RAYTRACER_RENDERTARGET_H

/** RenderTarget is the abstract base for rendering control/receivers.
 *
 * It lets us have separate implementations for CLI and GUI without changing the
 * raytracer itself
 */
class RenderTarget {
public:
    /** setPixel sets a pixel on the current backing.  It's NOT synchronised (on purpose), so
     * having two threads hit the same pixel simultaneously is undefined.
     *
     * This is exposed so the RayTracing Camera API can hit it directly.
     *
     * @param x x coordinate.  Must be within the bounds expected after the last newBackingImage call.
     * @param y y coordinate.  Must be within the bounds expected after the last newBackingImage call.
     * @param r Red component - 0-255 range.
     * @param g Green component - 0-255 range.
     * @param b Blue component - 0-255 range.
     */
    virtual void setPixel(int x, int y, int r, int g, int b) = 0;
};


#endif //RAYTRACER_RENDERTARGET_H
