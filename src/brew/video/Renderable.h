/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 02.01.18
 *
 */

#ifndef BREW_RENDERABLE_H
#define BREW_RENDERABLE_H

#include <brew/video/Mesh.h>
#include <brew/video/ShaderProgram.h>
#include <brew/video/ShaderVariables.h>

#include <brew/math/Matrix4.h>

#include <list>

namespace brew {

/**
 * A renderable is a simple structure that describes how to render a mesh.
 * Renderables should be used in conjunction with RenderBatches.
 */
class Renderable {
public:
    std::shared_ptr<SubMesh> mesh; //< The mesh or sub mesh to render.
    Matrix4 worldTransform; //< The world transformation for the rendered mesh.
    std::shared_ptr<ShaderProgram> shaderProgram; //< The shader program to use.
    std::shared_ptr<ShaderVariables> shaderVariables; //< The shader variables to use.
};

/**
 * A class for providing renderables.
 */
class RenderableProvider {
public:
    /**
     * Obtains a list of renderables from this provider.
     * @param result An array containing the results.
     */
    virtual void getRenderables(std::list<Renderable>& result) const = 0;
};

} /* namespace brew */

#endif //BREW_RENDERABLE_H
