#pragma once

#include "input_args/input_args.h"
#include <string>

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    virtual void init();
    virtual void onInputArgsChanged(InputArgs &args);
    virtual void resize(int width, int height);
    virtual void render();

protected:
    enum ShaderType
    {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };

    unsigned int getShaderProgram();
    unsigned int getVertexArray();

    void createShaderProgram(std::string vertexShaderFile, std::string fragmentShaderFile);
    unsigned int loadAndCompileShader(std::string &filename, ShaderType shaderType);
    void checkShaderError(unsigned int shader, int thingToCheck, ShaderType shaderType);
    void checkShaderProgramError(unsigned int program);
    void fillVertexBufferAndVertexArray(InputArgs &args);

private:
    unsigned int mVertexBuffer;
    unsigned int mShaderProgram;
};
