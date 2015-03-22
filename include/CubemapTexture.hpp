#pragma once
#include <GL/glew.h>
#include <string>

/* 
TO DO 

GL_TEXTURE_CUBE_MAP_POSITIVE_X​
GL_TEXTURE_CUBE_MAP_NEGATIVE_X​
GL_TEXTURE_CUBE_MAP_POSITIVE_Y​
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y​
GL_TEXTURE_CUBE_MAP_POSITIVE_Z​
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z​

*/

class CubemapTexture {
private:
    GLuint m_textureID;


    CubemapTexture(const CubemapTexture& cubemap);
    CubemapTexture& operator=(const CubemapTexture& cubemap);

public:
    CubemapTexture();
    ~CubemapTexture();

    void load(const std::string& directoryPath,
              const std::string& posXPath,
              const std::string& negXPath,
              const std::string& posYPath,
              const std::string& negYPath,
              const std::string& posZPath,
              const std::string& negZPath);

    void bind(const GLenum textureUnit) const;

};

