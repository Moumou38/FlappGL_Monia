#include <Mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cassert>

void MeshRenderer::Mesh::init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices){
    //Generate VB, IB and VAO
    glGenBuffers(1, &m_VB);
    glGenBuffers(1, &m_IB);
    glGenVertexArrays(1, &m_VAO);

    m_numIndices = Indices.size();

    // Lock the VAO
    glBindVertexArray(m_VAO);

    // Lock the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal_coords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex_coords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_numIndices, &Indices[0], GL_STATIC_DRAW);

    // Unlock the VAO & current buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

MeshRenderer::Mesh::~Mesh(){
    // Free memory
    if (glIsBuffer(m_VB) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_VB);
    }

    if (glIsBuffer(m_IB) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_IB);
    }

    if(glIsVertexArray(m_VAO) == GL_TRUE){
        glDeleteVertexArrays(1, &m_VAO);
    }
}

void MeshRenderer::load(const std::string& filename){
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (pScene) {
        initFromScene(pScene, filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", filename.c_str(), Importer.GetErrorString());
    }

}

void MeshRenderer::initFromScene(const aiScene* pScene, const std::string &filename){
    m_Entries.resize(pScene->mNumMeshes);
    m_Textures.resize(pScene->mNumMaterials);

    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        initMesh(i, paiMesh);
    }

    initMaterials(pScene, filename);
}

void MeshRenderer::initMesh(unsigned int Index, const aiMesh* paiMesh){

    m_Entries[Index].m_materialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Vertex v;
        v.position=glm::vec3(pPos->x, pPos->y, pPos->z);
        v.tex_coords=glm::vec2(pTexCoord->x, pTexCoord->y);
        v.normal_coords=glm::vec3(pNormal->x, pNormal->y, pNormal->z);

        Vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }

    m_Entries[Index].init(Vertices, Indices);
}

void MeshRenderer::initMaterials(const aiScene *pScene, const std::string &filename){
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = filename.substr(0, SlashIndex);
    }

    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        m_Textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
           aiString Path;

           if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
               std::string FullPath = Dir + "/" + Path.data;
               m_Textures[i] = new GLTexture;

               m_Textures[i]->load(FullPath.c_str());
           }
        }

        if (!m_Textures[i]) {
            m_Textures[i] = new GLTexture;
            m_Textures[i]->load("../../assets/textures/none.png");
        }
    }
}

void MeshRenderer::render() const{
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        const unsigned int MaterialIndex = m_Entries[i].m_materialIndex;

        if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
            m_Textures[MaterialIndex]->bind(GL_TEXTURE0);
        }

        glBindVertexArray(m_Entries[i].m_VAO);
        glDrawElements(GL_TRIANGLES, m_Entries[i].m_numIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
