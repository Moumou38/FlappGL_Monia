#pragma once

#include <GL/glew.h>
#include <Vertex.hpp>
#include <vector>
#include <string>
#include <GLTexture.hpp>

class aiScene;
class aiMesh;

class MeshRenderer {
private:
    struct Mesh {
        Mesh():m_numIndices(0){}

        ~Mesh();

        void init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        GLuint m_VB;
        GLuint m_IB;
        GLuint m_VAO;
        unsigned int m_numIndices;
        unsigned int m_materialIndex;
    };

    std::vector<Mesh> m_Entries;
    std::vector<GLTexture*> m_Textures;

    void initFromScene(const aiScene* pScene, const std::string& filename);
    void initMesh(unsigned int Index, const aiMesh* paiMesh);
    void initMaterials(const aiScene* pScene, const std::string& filename);

public:
    MeshRenderer(){}
    void load(const std::string& filepath);

    void render() const;
};

/*

typedef enum {
        Point,
        Wireframe,
        Full
    } DrawMode;
    typedef enum {
        Solid,
        AlphaBlending
    } RenderMode;
    
    class MeshBuffer : public Util::Resource {
    public:

        MeshBuffer();
        bool loadFromMemory(const VertexBuffer& buffer);

        void draw();
        void setDrawMode(DrawMode m);
        void setRenderMode(RenderMode m);

        bool hasAlphaBlending() const;

        const VertexBuffer& getVertexBuffer() const;

    private:
        RenderMode m_renderMode;
        DrawMode m_drawMode;
        VertexBuffer m_buffer;
        VBO m_vbo;
        VBO m_ibo;
        VAO m_vao;
    };

    */
