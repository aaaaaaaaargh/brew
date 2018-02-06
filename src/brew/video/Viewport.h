/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 06.01.18
 *
 */

#ifndef BREW_VIEWPORT_H
#define BREW_VIEWPORT_H

#include <brew/core/Types.h>
#include <brew/math/Vec2.h>
#include <brew/video/Camera.h>

#include <memory>

namespace brew {

/**
 * This class manages the cameras viewport.
 * Each viewport is described by a set of virtual and physical dimensions.
 * Physical dimensions describe the real size of the render canvas (e.g. the window or fullscreen size), whereas
 * virtual dimensions can be used for scaling or fitting the scene into the canvas.
 */
class Viewport {
public:
    /**
     * Creates a new viewport.
     * @param virtualWidth The virtual width of the viewport.
     * @param virtualHeight The virtual height of the viewport.
     * @param camera (optional) The camera to use for this viewport.
     */
    Viewport(Real virtualWidth,
             Real virtualHeight,
             std::shared_ptr<Camera> camera = std::shared_ptr<Camera>()
    );

    /**
     * Creates a new viewport.
     * @param virtualSize The virtual width of the viewport.
     * @param camera (optional) The camera to use for this viewport.
     */
    explicit Viewport(const Vec2& virtualSize, std::shared_ptr<Camera> camera = std::shared_ptr<Camera>());

    /**
     * Sets the virtual size of the viewport.
     * @param width The virtual size.
     * @param height The virtual height.
     */
    void setVirtualSize(Real width, Real height);

    /**
     * Sets the virtual size of the viewport.
     * @param size The virtual size.
     */
    inline void setVirtualSize(const Vec2& size) {
        setVirtualSize(size.x, size.y);
    }

    /**
     * Sets the virtual width of the viewport.
     * @param width The virtual width.
     */
    void setVirtualWidth(Real width) {
        setVirtualSize(width, virtualSize.y);
    }

    /**
     * Sets the virtual height of the viewport.
     * @param height The virtual height.
     */
    void setVirtualHeight(Real height) {
        setVirtualSize(virtualSize.x, height);
    }

    /**
     * @return This viewports virtual size.
     */
    inline const Vec2& getVirtualSize() const {
        return virtualSize;
    }

    /**
     * Updates the physical dimensions of the viewport.
     * @param physicalWidth The new physical width.
     * @param physicalHeight The new physical height.
     */
    virtual void update(SizeT physicalWidth, SizeT physicalHeight);

    /**
     * Sets the physical dimensions of the viewport.
     * @param x The physical x offset.
     * @param y The physical y offset.
     * @param width The physical width.
     * @param height The physical height.
     */
    void setPhysicalBounds(SizeT x, SizeT y, SizeT width, SizeT height);

    /**
     * Sets the physical position of the viewport.
     * @param x The physical x offset.
     * @param y The physical y offset.
     */
    inline void setPhysicalPosition(SizeT x, SizeT y) {
        setPhysicalBounds(x, y, this->physicalWidth, this->physicalHeight);
    }

    /**
     * Sets the physical size of the viewport.
     * @param width The physical width.
     * @param height The physical height.
     */
    inline void setPhysicalSize(SizeT width, SizeT height) {
        setPhysicalBounds(this->physicalX, this->physicalY, width, height);
    }

    /**
     * @return The physical x offset.
     */
    inline SizeT getPhysicalX() const {
        return physicalX;
    }

    /**
     * @return The physical y offset.
     */
    inline SizeT getPhysicalY() const {
        return physicalY;
    }

    /**
     * @return The physical width.
     */
    inline SizeT getPhysicalWidth() const {
        return physicalWidth;
    }

    /**
     * @return The physical height.
     */
    inline SizeT getPhysicalHeight() const {
        return physicalHeight;
    }

    /**
     * @return The camera used for this viewport.
     */
    inline Camera& getCamera() const {
        return *camera;
    }

    /**
     * Sets the viewport camera.
     * @param camera The new camera.
     */
    void setCamera(std::shared_ptr<Camera> camera);

    /**
     * Performs a screen space to world space coordinate transformation-
     * @param screenCoords the screen coordinates to convert to world coordinates.
     */
    inline Vec3 unproject(const Vec2& screenCoords) const {
        return unproject(Vec3(screenCoords.x, screenCoords.y, 1));
    }

    /**
     * Performs a screen space to world space coordinate transformation-
     * @param screenCoords the screen coordinates to convert to world coordinates, along with a depth component.
     * @param useFarPlane projects the world coordinate onto the cameras far plane if set to true. Uses near plane instead if false.
     */
    Vec3 unproject(const Vec3& screenCoords) const;

    /**
     * Performs a world space to screen space coordinate transformation-
     * @param worldCoords the world coordinates to convert to screen coordinates.
     */
    Vec2 project(const Vec3& worldCoords) const;

private:
    SizeT physicalX, physicalY;
    SizeT physicalWidth, physicalHeight;
    Vec2 virtualSize;

    std::shared_ptr<Camera> camera;
};

} /* namespace brew */

#endif //BREW_VIEWPORT_H
