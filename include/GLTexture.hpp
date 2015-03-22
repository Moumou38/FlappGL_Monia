#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>


class GLTexture {
private:
	GLuint m_textureID;

public:

	GLTexture();
    ~GLTexture();
    void load(const std::string& imagepath);
    void bind(const GLenum textureUnit) const;
};

