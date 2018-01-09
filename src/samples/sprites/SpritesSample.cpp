#include <brew/asset/AssetManager.h>
#include <brew/asset/core/CoreAssetProcessors.h>

#include <brew/video/gl/GLContext.h>
#include <brew/video/linux/GLXCanvas.h>
#include <brew/video/RenderBatch.h>
#include <brew/video/NativeViewport.h>
#include <brew/asset/core/PixmapProcessor.h>

#include "SampleConfig.h"

using namespace brew;

class MyRenderListener : public RenderListener {
public:
    explicit MyRenderListener(VideoContext& ctx) {
        // Create the virtual file system.
        auto vfs = std::make_shared<VirtualFileSystem>();
        vfs->mountLocal("/", BREW_SAMPLE_VFS_ROOT);

        // Create the asset manager.
        assets = std::make_shared<AssetManager>(vfs);
        CoreAssetProcessors::registerTo(*assets, ctx);

        // Attempt to load the sample texture.
        PixmapProcessorParams params;
        params.invertYAxis = true;

        if(!assets->load("sample.png", "texture", params).getResult()) {
            throw RuntimeException("Could not load sample image.");
        }

        // Create a mesh for our sprite.
        VertexAttributeLayout vertLayout;
        vertLayout
                .add<PositionAttribute>()
                .add<TexCoordAttribute>()
                .add<NormalAttribute>()
                ;

        auto vBuffer = ctx.createVertexBuffer(4, vertLayout);
        auto iBuffer = ctx.createIndexBuffer(6);

        vBuffer->write<PositionAttribute>(0, Vec3(0,0,0));
        vBuffer->write<TexCoordAttribute>(0, Vec2(0,1));
        vBuffer->write<NormalAttribute>(0, Vec3(0,0,-1));

        vBuffer->write<PositionAttribute>(1, Vec3(1,0,0));
        vBuffer->write<TexCoordAttribute>(1, Vec2(1,1));
        vBuffer->write<NormalAttribute>(1, Vec3(0,0,-1));

        vBuffer->write<PositionAttribute>(2, Vec3(1,1,0));
        vBuffer->write<TexCoordAttribute>(2, Vec2(1,0));
        vBuffer->write<NormalAttribute>(2, Vec3(0,0,-1));

        vBuffer->write<PositionAttribute>(3, Vec3(0,1,0));
        vBuffer->write<TexCoordAttribute>(3, Vec2(0,0));
        vBuffer->write<NormalAttribute>(3, Vec3(0,0,-1));

        iBuffer->write(0, 0);
        iBuffer->write(1, 1);
        iBuffer->write(2, 2);
        iBuffer->write(3, 2);
        iBuffer->write(4, 3);
        iBuffer->write(5, 0);

        iBuffer->syncToGPU();
        vBuffer->syncToGPU();

        // Create the mesh.
        this->mesh = ctx.createMesh(vBuffer, iBuffer);

        // Create the shader and shader variables.
        ShaderVariablesLayout shaderVarLayout = {};
        shaderVarLayout.define(ShaderVarType::Real, "t"); // t := time.
        shaderVarLayout.define(ShaderVarType::Texture, "texture"); // The texture to render.

        this->shaderVars = ctx.createShaderVariables(shaderVarLayout);

        // Get the texture and set it in our shader.
        auto texture = assets->getDefaultBundle().get<brew::Texture>("sample.png");
        this->shaderVars->set("texture", texture);

        // Create the GLSL source code.
        String uniformDeclarationSrc = GLContext::getUniformDeclarations(shaderVars);

        String vertexShaderSrc =
                "#version 430\n"
                + uniformDeclarationSrc +
                "layout(location=0) in vec3 position;"
                "layout(location=1) in vec2 texCoords;"
                "out vec2 uv;"
                "void main() { gl_Position = combinedCamera * vec4(position, 1.0); uv = texCoords; }";

        String fragmentShaderSrc =
                "#version 430\n"
                + uniformDeclarationSrc +
                "in vec2 uv;"
                "void main() { gl_FragColor = texture2D(texture, uv) * t; }";

        // Create the shaders.
        auto vertexShader = ctx.createShader(ShaderType::Vertex, vertexShaderSrc);
        auto fragmentShader = ctx.createShader(ShaderType::Fragment, fragmentShaderSrc);
        this->shaderProgram = ctx.createShaderProgram({vertexShader, fragmentShader});
    }

    void onBeginFrame(const RenderEvent& evt) override {
        RenderTarget& target = evt.renderTarget;

        // Increase time in our shader.
        this->shaderVars->set<Real>("t", 1.0f + std::sin(t) * 0.5f);
        t+= 0.1f;

        // Update the camera.
        viewport.getCamera().setPosition(
                std::sin(t*0.1f) * 3.0f,
                3,
                std::cos(t*0.1f) * 3.0f
        );
        viewport.getCamera().lookAt(0,0,0);

        // Render the scene.
        evt.renderTarget.getContext().execute([&](GPUExecutionContext& ctx) {
            RenderBatch batch;

            Renderable renderable;
            renderable.mesh = mesh;
            renderable.worldTransform = Matrix4::ID;
            renderable.shaderProgram = shaderProgram;
            renderable.shaderVariables = shaderVars;

            batch.add(renderable);
            batch.flush(target, viewport, ctx);
        });
    }

    std::shared_ptr<AssetManager> assets;

    NativeViewport viewport;
    std::shared_ptr<Mesh> mesh;

    std::shared_ptr<Texture> texture;
    std::shared_ptr<ShaderVariables> shaderVars;
    std::shared_ptr<ShaderProgram> shaderProgram;

    Real t = 0;
};

int main() {
    GLContext ctx;
    GLXCanvas canvas(ctx);

    canvas.init(640, 480);

    auto myListener = std::make_shared<MyRenderListener>(ctx);
    auto& viewport = myListener->viewport;

    canvas.addRenderListener(myListener);

    while(canvas.isInitialized()) {
        viewport.update(canvas.getWidth(), canvas.getHeight());

        canvas.pumpMessages();
        canvas.renderFrame();
    }
}