#pragma once

#include <vector>
#include <GL/glew.h>
#include <Vertex.hpp>


class Cube {
private:
	unsigned int m_verticesCount;
	GLuint m_VAO;
	std::vector<Vertex> m_vertices;
    Cube(const Cube& cube);
	GLuint m_VBO[2];
    Cube& operator=(const Cube& cube);


public:
    Cube(){

	}

	void initVertices(){
		// Bottom face
		m_vertices.emplace_back(Vertex(-0.5f, -0.5f, 0.5f, 0.f, -1.f, 0.f, 0.f, 0.f)); 
		m_vertices.emplace_back(Vertex(-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, -0.5f, 0.5f, 0.f, -1.f, 0.f, 1.f, 0.f));

		// Upper face
		m_vertices.emplace_back(Vertex(-0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 0.f));
		m_vertices.emplace_back(Vertex(-0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f));

		// Left face
		m_vertices.emplace_back(Vertex(-0.5f, 0.5f, -0.5f, -1.f, 0.f, 0.f, 0.f, 0.f));
		m_vertices.emplace_back(Vertex(-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.f, 1.f));
		m_vertices.emplace_back(Vertex(-0.5f, -0.5f, 0.5f, -1.f, 0.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(-0.5f, -0.5f, 0.5f, -1.f, 0.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(-0.5f, 0.5f, 0.5f, -1.f, 0.f, 0.f, 1.f, 0.f));

		// Right face
		m_vertices.emplace_back(Vertex(0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f, 0.f, 0.f));
		m_vertices.emplace_back(Vertex(0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 0.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 1.f));
		m_vertices.emplace_back(Vertex(0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f, 0.f));

		// Front face
		m_vertices.push_back(Vertex(-0.5f, 0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 0.f));
		m_vertices.push_back(Vertex(-0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f));
		m_vertices.push_back(Vertex(0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f, 1.f, 1.f));
		m_vertices.push_back(Vertex(0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f, 1.f, 1.f));
		m_vertices.push_back(Vertex(0.5f, 0.5f, 0.5f, 0.f, 0.f, 1.f, 1.f, 0.f));

		// Back face
		m_vertices.push_back(Vertex(0.5f, 0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f));
		m_vertices.push_back(Vertex(0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 1.f));
		m_vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 1.f));
		m_vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 1.f));
		m_vertices.push_back(Vertex(-0.5f, 0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 0.f));
	}

	void init(){
		
		/*   // Load geometry
    int cube_triangleCount = 12;
    int cube_triangleList[] = {0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11, 12, 13, 14, 14, 13, 15, 16, 17, 18, 19, 17, 20, 21, 22, 23, 24, 25, 26, };
    float cube_uvs[] = {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f,  1.f, 0.f,  1.f, 1.f,  0.f, 1.f,  1.f, 1.f,  0.f, 0.f, 0.f, 0.f, 1.f, 1.f,  1.f, 0.f,  };
    float cube_vertices[] = {-0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5 };
    float cube_normals[] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, };
 */
		initVertices();
		unsigned int index[] = {
			0, 1, 2, 3, 4, 0,
			5, 6, 7, 8, 9, 5,
			10, 11, 12, 13, 14, 10,
			15, 16, 17, 18, 19, 15,
			20, 21, 22, 23, 24, 20,
			25, 26, 27, 28, 29, 25
		};

		m_verticesCount = sizeof(index)/sizeof(unsigned int);
		glGenBuffers(2, m_VBO);
		glGenVertexArrays(1, &m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(m_VAO);

			
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal_coords));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex_coords));

	
			glBindBuffer(GL_ARRAY_BUFFER, 0);


		glBindVertexArray(0);
	}

	void render() const{
		glBindVertexArray(m_VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[0]);

				glDrawElements(GL_TRIANGLES, m_verticesCount, GL_UNSIGNED_INT, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	~Cube(){
		glDeleteBuffers(2, m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

};


