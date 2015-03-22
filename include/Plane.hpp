#pragma once
#include <vector>
#include <GL/glew.h>
#include <Vertex.hpp>

class Plane {
private:
	unsigned int m_verticesCount;

	GLuint m_VAO;
	GLuint m_VBO[2];

	std::vector<Vertex> m_vertices;
    Plane(const Plane&);
    Plane& operator=(const Plane&);
	void initVertices();

public:
	Plane(){}
	void init(float textureRepeat);
    void render() const;
	~Plane();
};
