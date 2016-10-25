#include "mandelbrot_renderer.h"
#include "utils/file_loader.h"
#include <GL/glew.h>
#include <GL/gl.h>

MandelbrotRenderer::MandelbrotRenderer()
{
    float vertices[] = {
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };


    glGenBuffers(1, &mVertexBuffer);
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderCode = FileLoader::loadFile("shaders/base.vert");
    const char *code = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &code, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("error vert: %s\n", infoLog);
        throw success;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderCode = FileLoader::loadFile("shaders/base.frag");
    code = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &code, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("error frag: %s\n", infoLog);
        throw success;
    }

    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, vertexShader);
    glAttachShader(mShaderProgram, fragmentShader);
    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
        printf("error: %s\n", infoLog);
        throw success;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

MandelbrotRenderer::~MandelbrotRenderer()
{
}

void MandelbrotRenderer::init()
{
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
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);

    // glColor3f(1.0f, 0.0f, 0.0f);
    // glBegin(GL_TRIANGLES);
    // glVertex3f(1.0f, 1.0f, 1.0f);
    // glVertex3f(1.0f, -1.0f, 1.0f);
    // glVertex3f(-1.0f, 1.0f, 1.0f);
    // glEnd();
}
