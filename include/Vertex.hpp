#pragma once

#include <glm/glm.hpp>


struct Vertex{

    glm::vec3 position;
    glm::vec3 normal_coords;
    glm::vec2 tex_coords;

    Vertex(){
        for (unsigned int i = 0; i < 3 ; ++i) {
			position[i] = 0.f;
			normal_coords[i] = 0.f;
            if (i < 2) tex_coords[i] = 0.f;
		}
    }

    Vertex(GLfloat pX,GLfloat pY,GLfloat pZ,GLfloat nX,GLfloat nY,GLfloat nZ,GLfloat tX,GLfloat tY) {
		position.x=pX;
		position.y=pY;
		position.z=pZ;
		normal_coords.x=nX;
		normal_coords.y=nY;
		normal_coords.z=nZ;
		tex_coords.x=tX;
		tex_coords.y=tY;
    }

    /*

    struct Vertex3D {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		sf::Color color;

		Vertex3D(const glm::vec3& p) :
			Vertex3D(p ,glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(255,255,255,255))
		{}

		Vertex3D(const glm::vec3& p, const glm::vec3& n, const glm::vec2& u, const sf::Color& c) :
			position(p), normal(n), uv(u), color(c)
		{}
	};

	class VertexBuffer {
	public:
		VertexBuffer() = default;

		void clear() {
			m_vertices.clear();
			m_indices.clear();
		}
		void addVertex(const Vertex3D& v) { 
			m_vertices.push_back(v); 
		}

		void addTriangle(const sf::Vector3i& i) {
			m_indices.push_back(i);
		}

		Vertex3D& getVertex(size_t i) {
			return m_vertices.at(i);
		}

		std::size_t getVerticesCount() const {
			return m_vertices.size();
		}

		std::size_t getIndicesCount() const {
			return m_indices.size();
		}

		const Vertex3D* getVerticesData() const {
			return m_vertices.data();
		}

		const sf::Vector3i* getIndicesData() const {
			return m_indices.data();
		}

		const std::vector<Vertex3D>& getVerticesArray() const {
			return m_vertices;
		}

		const std::vector<sf::Vector3i>& getIndicesArray() const {
			return m_indices;
		}

	private:
		std::vector<Vertex3D> m_vertices;
		std::vector<sf::Vector3i> m_indices;
	};

	*/

};

