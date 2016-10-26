#pragma once

#include "renderers/renderer.h"
#include <string>

class MandelbrotRenderer : public Renderer
{
public:
    MandelbrotRenderer();
    virtual ~MandelbrotRenderer();

    virtual void init();
    virtual void onInputArgsChanged(InputArgs &args);
    virtual void resize(int width, int height);
    virtual void render();

private:
    enum ShaderType
    {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };

    unsigned int loadAndCompileShader(std::string filename, ShaderType shaderType);
    void createShaderProgram();
    void fillVertexBufferAndVertexArray(InputArgs &args);
    void checkShaderError(unsigned int shader, int thingToCheck, ShaderType shaderType);

    unsigned int mVertexBuffer;
    unsigned int mVertexArray;
    unsigned int mShaderProgram;

    int mWidth;
    int mHeight;
};
