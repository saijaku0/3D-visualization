#pragma once
#include <glad/glad.h>

class Framebuffer {
    unsigned int fbo;
    unsigned int textureID;
    unsigned int rbo;

    int m_width, m_height;
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void Bind();   
    void Unbind(); 

    void Rescale(int width, int height);

    unsigned int GetTextureID() const { return textureID; }
};