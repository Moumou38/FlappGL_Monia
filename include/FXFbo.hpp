#pragma once

#include <GL/glew.h>

class FXFbo{
private :
    GLuint m_framebuffer;
    GLuint m_textures[4];

public :
    FXFbo(){}
    void init(const unsigned int width, const unsigned int height);
    void bindFramebufferWith(unsigned int textureNumber);
    const GLuint& getTexture(unsigned int index);
    ~FXFbo();
};
