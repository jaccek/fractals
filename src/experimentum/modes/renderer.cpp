#include "renderer.h"
#include "utils/file_loader.h"
#include <GL/glew.h>
#include <GL/gl.h>

Renderer::Renderer()
{
    glGenBuffers(1, &mVertexBuffer);
    int error = glGetError();
    printf("Renderer: constructor: error=%u, buf=%u\n", error, mVertexBuffer);
}

Renderer::~Renderer()
{
    printf("Renderer: destructor\n");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &mVertexBuffer);
    glUseProgram(0);
    glDeleteProgram(mShaderProgram);
}

void Renderer::init()
{
    printf("Renderer: init\n");
}

void Renderer::onInputArgsChanged(InputArgs &args)
{
    mLastInputArgs = args;
    fillVertexBufferAndVertexArray();
}

void Renderer::resize(int width, int height)
{
    printf("resize(%d, %d)\n", width, height);
    glViewport(0, 0, width, height);
}

void Renderer::render()
{
    glUseProgram(mShaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

    bindShaderUniforms();
    bindShaderAttributes();

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glUseProgram(0);
}

void Renderer::onShadersLoaded()
{
    mUniformZ0Location = glGetUniformLocation(getShaderProgram(), "inZ0");

    mAttributePositionLocation = glGetAttribLocation(mShaderProgram, "iPosition");
    mAttributeCoordinatesLocation = glGetAttribLocation(mShaderProgram, "iCoords");
}

void Renderer::fillVertexBufferAndVertexArray()
{
    float vertices[] = {
        -1.0f,  1.0f, 0.0f, mLastInputArgs.left,  mLastInputArgs.top,
        -1.0f, -1.0f, 0.0f, mLastInputArgs.left,  mLastInputArgs.bottom,
         1.0f, -1.0f, 0.0f, mLastInputArgs.right, mLastInputArgs.bottom,
         1.0f,  1.0f, 0.0f, mLastInputArgs.right, mLastInputArgs.top
    };

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    bindShaderAttributes();
}

void Renderer::bindShaderAttributes()
{
    glEnableVertexAttribArray(mAttributePositionLocation);
    glVertexAttribPointer(mAttributePositionLocation, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);

    glEnableVertexAttribArray(mAttributeCoordinatesLocation);
    glVertexAttribPointer(mAttributeCoordinatesLocation, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
}

void Renderer::bindShaderUniforms()
{
    glUniform2f(mUniformZ0Location, mLastInputArgs.startX, mLastInputArgs.startY);
}

unsigned int Renderer::getShaderProgram()
{
    return mShaderProgram;
}

unsigned int Renderer::getVertexArray()
{
    return 0;
}

void Renderer::createShaderProgram(std::string vertexShaderFile, std::string fragmentShaderFile)
{
    printf("Renderer: createShaderProgram(%s, %s)\n", vertexShaderFile.c_str(), fragmentShaderFile.c_str());
    GLuint vertexShader = loadAndCompileShader(vertexShaderFile, VERTEX);
    GLuint fragmentShader = loadAndCompileShader(fragmentShaderFile, FRAGMENT);

    mShaderProgram = glCreateProgram();

    glAttachShader(mShaderProgram, vertexShader);
    glAttachShader(mShaderProgram, fragmentShader);

    glLinkProgram(mShaderProgram);
    checkShaderProgramError(mShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    onShadersLoaded();
}

unsigned int Renderer::loadAndCompileShader(std::string &filename, ShaderType shaderType)
{
    unsigned int shader = glCreateShader(shaderType == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    std::string shaderCode = FileLoader::loadFile(filename);
    const char *code = shaderCode.c_str();

    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, shaderType);

    return shader;
}

void Renderer::checkShaderError(unsigned int shader, int thingToCheck, ShaderType shaderType)
{
    GLint success;
    glGetShaderiv(shader, thingToCheck, &success);
    if (!success)
    {
        GLchar infoLog[512] = { 0 };
        std::string shaderTypeString;
        switch (shaderType)
        {
            case VERTEX:
                shaderTypeString = "vertex";
                break;

            case FRAGMENT:
                shaderTypeString = "fragment";
                break;

            case PROGRAM:
                throw "Program not acceptable in checkShaderError";
        }

        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("%s error: %s\n", shaderTypeString.c_str(), infoLog);
        throw success;
    }
}

void Renderer::checkShaderProgramError(unsigned int program)
{
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512] = { 0 };
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("program error: %s\n", infoLog);
        throw success;
    }
}

InputArgs& Renderer::getLastInputArgs()
{
    return mLastInputArgs;
}
