#include "mandelbrot_renderer.h"
#include "utils/file_loader.h"
#include <GL/glew.h>
#include <GL/gl.h>

MandelbrotRenderer::MandelbrotRenderer()
{
    createShaderProgram();

    // TODO:
    glGenBuffers(1, &mVertexBuffer);
    glGenVertexArrays(1, &mVertexArray);
    //createVertexBufferAndVertexArray();

    // glBindVertexArray(mVertexArray);
    //     GLint positionAttrib = glGetAttribLocation(mShaderProgram, "iPosition");
    //     glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    //     glEnableVertexAttribArray(positionAttrib);
    //
    //     GLint coordsAttrib = glGetAttribLocation(mShaderProgram, "iCoords");
    //     glVertexAttribPointer(coordsAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    //     glEnableVertexAttribArray(coordsAttrib);
    // glBindVertexArray(0);
}

MandelbrotRenderer::~MandelbrotRenderer()
{
}

void MandelbrotRenderer::init()
{
}

void MandelbrotRenderer::onInputArgsChanged(InputArgs &args)
{
    fillVertexBufferAndVertexArray(args);
}

void MandelbrotRenderer::resize(int width, int height)
{
    mWidth = width;
    mHeight = height;
    glViewport(0, 0, width, height);
}

void MandelbrotRenderer::render()
{
    glUseProgram(mShaderProgram);
    glBindVertexArray(mVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);
}

unsigned int MandelbrotRenderer::loadAndCompileShader(std::string filename, ShaderType shaderType)
{
    unsigned int shader = glCreateShader(shaderType == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    std::string shaderCode = FileLoader::loadFile(filename);
    const char *code = shaderCode.c_str();

    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, shaderType);

    return shader;
}

void MandelbrotRenderer::createShaderProgram()
{
    GLuint vertexShader = loadAndCompileShader("shaders/mandelbrot.vert", VERTEX);
    GLuint fragmentShader = loadAndCompileShader("shaders/mandelbrot.frag", FRAGMENT);

    mShaderProgram = glCreateProgram();

    glAttachShader(mShaderProgram, vertexShader);
    glAttachShader(mShaderProgram, fragmentShader);

    glLinkProgram(mShaderProgram);
    checkShaderError(mShaderProgram, GL_LINK_STATUS, PROGRAM);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void MandelbrotRenderer::fillVertexBufferAndVertexArray(InputArgs &args)
{
    float vertices[] = {
        -1.0f,  1.0f, 0.0f,  args.left, args.top,
        -1.0f, -1.0f, 0.0f,  args.left, args.bottom,
         1.0f, -1.0f, 0.0f, args.right, args.bottom,
        -1.0f,  1.0f, 0.0f,  args.left, args.top,
         1.0f, -1.0f, 0.0f, args.right, args.bottom,
         1.0f,  1.0f, 0.0f, args.right, args.top
    };

    glBindVertexArray(mVertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        GLint positionAttrib = glGetAttribLocation(mShaderProgram, "iPosition");
        glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(positionAttrib);

        GLint coordsAttrib = glGetAttribLocation(mShaderProgram, "iCoords");
        glVertexAttribPointer(coordsAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(coordsAttrib);
    glBindVertexArray(0);
}

void MandelbrotRenderer::checkShaderError(unsigned int shader, int thingToCheck, ShaderType shaderType)
{
    GLint success;
    glGetProgramiv(shader, thingToCheck, &success);
    if (!success)
    {
        GLchar infoLog[512] = { 0 };
        std::string shaderTypeString;
        switch (shaderType)
        {
            case VERTEX:
                shaderTypeString = "vertex";
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                break;

            case FRAGMENT:
                shaderTypeString = "fragment";
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                break;

            case PROGRAM:
                shaderTypeString = "program";
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                break;
        }

        printf("%s error: %s\n", shaderTypeString.c_str(), infoLog);
        throw success;
    }
}
