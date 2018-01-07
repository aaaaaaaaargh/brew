#include <brew/video/gl/GLContext.h>
#include <brew/video/linux/GLXCanvas.h>
#include <brew/video/RenderBatch.h>

using namespace brew;

class MyRenderListener : public RenderListener {
public:
    explicit MyRenderListener(VideoContext& ctx) {
        VertexAttributeLayout vertLayout;
        vertLayout
                .add<PositionAttribute>()
                .add<TexCoordAttribute>()
                .add<NormalAttribute>()
                ;

        auto vBuffer = ctx.createVertexBuffer(4, vertLayout);
        auto iBuffer = ctx.createIndexBuffer(6);

        vBuffer->write<PositionAttribute>(0, Vec3(0,0,0));
        vBuffer->write<TexCoordAttribute>(0, Vec2(0,0));
        vBuffer->write<NormalAttribute>(0, Vec3(0,0,-1));

        vBuffer->write<PositionAttribute>(1, Vec3(1,0,0));
        vBuffer->write<TexCoordAttribute>(1, Vec2(1,0));
        vBuffer->write<NormalAttribute>(1, Vec3(0,0,-1));

        vBuffer->write<PositionAttribute>(2, Vec3(1,1,0));
        vBuffer->write<TexCoordAttribute>(2, Vec2(1,1));
        vBuffer->write<NormalAttribute>(2, Vec3(0,0,-1));

        vBuffer->write<PositionAttribute>(3, Vec3(0,1,0));
        vBuffer->write<TexCoordAttribute>(3, Vec2(0,1));
        vBuffer->write<NormalAttribute>(3, Vec3(0,0,-1));

        iBuffer->write(0, 0);
        iBuffer->write(1, 1);
        iBuffer->write(2, 2);
        iBuffer->write(3, 2);
        iBuffer->write(4, 3);
        iBuffer->write(5, 0);

        iBuffer->syncToGPU();
        vBuffer->syncToGPU();

        ShaderVariablesLayout shaderVarLayout = {};
        shaderVarLayout.define(ShaderVarType::Real, "t");
        shaderVarLayout.define(ShaderVarType::Texture, "texture");

        this->shaderVars = ctx.createShaderVariables(shaderVarLayout);

        // Create a simple pixmap.
        auto spritePixmap = std::make_shared<brew::Pixmap>(32, 32);
        spritePixmap->applyFilter([&] (SizeT x, SizeT y, Color& color)  {
            color.set(0, 32.0f / x, 32.0f / y, 1.0f);
        });

        auto texture = ctx.createTexture(spritePixmap);
        this->shaderVars->set("texture", texture);

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

        auto vertexShader = ctx.createShader(ShaderType::Vertex, vertexShaderSrc);
        auto fragmentShader = ctx.createShader(ShaderType::Fragment, fragmentShaderSrc);
        this->shaderProgram = ctx.createShaderProgram({vertexShader, fragmentShader});

        this->mesh = ctx.createMesh(vBuffer, iBuffer);

        viewport.getCamera().setPosition(3,3,3);
        viewport.getCamera().lookAt(0,0,0);
    }

    void onBeginFrame(const RenderEvent& evt) override {
        RenderTarget& target = evt.renderTarget;

        this->shaderVars->set<Real>("t", std::sin(t));
        t+= 0.1f;

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

    inline Viewport& getViewport() {
        return viewport;
    }

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
    auto& viewport = myListener->getViewport();

    canvas.addRenderListener(myListener);

    while(canvas.isInitialized()) {
        viewport.update(canvas.getWidth(), canvas.getHeight());

        canvas.pumpMessages();
        canvas.renderFrame();
    }
}