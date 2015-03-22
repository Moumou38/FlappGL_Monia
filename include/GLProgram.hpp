#pragma once
#include <GL/glew.h>

class GLProgram {
private:
    GLuint m_programID;

public:
	GLProgram();
	~GLProgram();
	
	GLuint load(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile = nullptr);
	
	inline GLuint getProgramID() const {
        return m_programID;
    }

	inline void use() const {
        glUseProgram(m_programID);
    }

	inline GLint getUniformLocation(const char* uniform) const {
        return glGetUniformLocation(m_programID, uniform);
    }
};

