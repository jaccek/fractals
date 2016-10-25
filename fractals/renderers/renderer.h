#pragma once

class Renderer
{
public:
    virtual ~Renderer() {}

    virtual void init() = 0;
    virtual void resize(int width, int height) = 0;
    virtual void render() = 0;
};
