#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



class DirectionalLight {
private:
	glm::vec3 m_Direction;
	glm::vec3 m_Color;
	float m_Intensity;

    glm::mat4 m_worldToLight;
    glm::mat4 m_ligthToShadowMap;
    float m_shadowSamples;
    float m_shadowSampleSpread;
    glm::mat4 m_worldToShadowMap;
    float m_shadowBias;

public:
    DirectionalLight(){}
	
    void init(glm::vec3 direction, glm::vec3 color, float intensity, float shadowBias, float shadowSamples, float shadowSampleSpread){
        m_Direction = direction;
		m_Color = color;
		m_Intensity = intensity;
        m_shadowBias = shadowBias;
        m_shadowSamples = shadowSamples;
        m_shadowSampleSpread = shadowSampleSpread;
        setShadowMatrices();
	}

    void setShadowMatrices(){
        glm::vec3 lightUp(0.f, 1.f, 0.f);
        m_worldToLight = glm::lookAt(-m_Direction, glm::vec3(0.f), lightUp);
        m_ligthToShadowMap = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50.0f);
      
        glm::mat4 ToLightSpace(
          0.5f, 0.f, 0.f, 0.f,
          0.f, 0.5f, 0.f, 0.f,
          0.f, 0.f, 0.5f, 0.f,
          0.5f, 0.5f, 0.5f, 1.f
        );
        m_worldToShadowMap =  ToLightSpace * m_ligthToShadowMap * m_worldToLight;
    }

    glm::vec3 & getDirection(){
		return m_Direction;
	}

    glm::vec3 & getColor(){
		return m_Color;
	}

    float & getIntensity(){
		return m_Intensity;
	}

    glm::mat4 getWorldToLight() const{
        return m_worldToLight;
    }
    glm::mat4 getLightToShadowMap() const{
        return m_ligthToShadowMap;
    }
    glm::mat4 getWorldToShadowMap() const{
        return m_worldToShadowMap;
    }

    float & getShadowBias(){
        return m_shadowBias;
    }
    float & getShadowSamples(){
        return m_shadowSamples;
    }
    float & getShadowSampleSpread(){
        return m_shadowSampleSpread;
    }

	~DirectionalLight(){}
};

