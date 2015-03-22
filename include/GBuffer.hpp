#pragma once
#include <GL/glew.h>


class GBuffer {
private:
	GLuint m_framebuffer;
	GLuint m_textures[3];
	GLuint m_drawbuffers[2];

public:
	GBuffer(){}
	void init(unsigned int width, unsigned int height);
	void bindFramebuffer() const;
	const GLuint& getTexture(unsigned int index) const;
	~GBuffer();
};
