#pragma once

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio/Music.hpp>

#include <Cube.hpp>
#include <Plane.hpp>
#include <AmbientLight.hpp>
#include <PointLight.hpp>
#include <DirectionalLight.hpp>
#include <SpotLight.hpp>
#include <GLProgram.hpp>
#include <FreeFlyCamera.hpp>
#include <CubemapTexture.hpp>
#include <GLTexture.hpp>
#include <GBuffer.hpp>
#include <ShadowMap.hpp>
#include <Mesh.hpp>
#include <FXFbo.hpp>
#include <Shaders.hpp>


class Screen {
private:
	sf::Window m_window;

    Cube m_cube; // for the skybox
	Plane m_blitPlane; //to render the blit
    MeshRenderer m_terrain;
    MeshRenderer m_star;

    FreeFlyCamera m_camera;

    GBuffer m_gbuffer;
    ShadowMap m_shadowMapSpotLight;
    ShadowMap m_shadowMapDirectionnalLight;
    FXFbo m_fxfbo;
    SkyboxShader m_skyboxShader;
    GBufferShader m_gbufferShader;
    GBufferShader m_texturedMeshShader;
	BlitShader m_blitShader; 
    AmbientLightShader m_AmbientLightShader;
    PointLightShader m_pointLightShader;
    DirectionalLightShader m_directionalLightShader;
    SpotLightShader m_spotLightShader;
    BlurShader m_blurShader;
    CocShader m_cocShader;
    DofShader m_dofShader;
    ShadowShader m_shadowShader;

    CubemapTexture m_skyboxTexture;
	GLTexture m_diffuseTexture;
	GLTexture m_specularTexture;

    glm::vec3 m_starPosition;
    glm::vec3 m_starRotationAxe;
    float m_starRotation;
    glm::vec3 m_dispersionRadius;
    float m_speed;
    float m_speed2;
    glm::mat4 m_terrainMatrix;
    glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_screenToView;
    glm::vec3 m_focus;
    float m_sampleCount;

    
	sf::Vector2i m_mousePosition;
	sf::Vector2i m_prevMousePosition;
    float m_fps;

    bool m_showdeferred;
    bool m_endSequence;
    sf::Music m_music;
    unsigned char m_animationSequence;
    unsigned char m_newSequence;
    bool m_isInitiated;
    bool running; 
    glm::vec3 trajectory[15];
    int index = 0; 
    float timer; 
	
	AmbientLight m_AmbientLight;
    DirectionalLight m_directionalLight;
    SpotLight m_starSpotLight;
    PointLight m_cameraPointLight;
    PointLight m_starPointLight;

    void end(); 
    void clearBuffers();
    void gBufferPass();
    void DrawSkybox();

    void animation(const float elapsedTime);
    void setAllDisplay(bool b);
    void outoftube(const float elapsedTime);
    void Travelling1(const float elapsedTime);
    void starcross(const float elapsedTime);
    void lookingup(const float elapsedTime);
    void downtube(const float elapsedTime);
    void upstar(const float elapsedTime);
  

public:
	Screen(unsigned int width, unsigned int height, const std::string& windowtitle):
        m_window(sf::VideoMode(width, height), windowtitle, sf::Style::Default, sf::ContextSettings(32)),
        m_showdeferred(false){}
	void init();
	void run();
    void playNewSequence();
};


