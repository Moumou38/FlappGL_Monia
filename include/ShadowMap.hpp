#pragma once

#include <GL/glew.h>

class ShadowMap {
private:
	GLuint m_framebuffer;
    GLuint m_texture;

public:
    ShadowMap(){}
	void init(unsigned int width, unsigned int height);
	void bindFramebuffer() const;
    const GLuint& getTexture() const;
    ~ShadowMap();
};

