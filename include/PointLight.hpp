#pragma once

#include <glm/glm.hpp>

class PointLight {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	float m_Intensity;
	
public:
	PointLight(){}
	PointLight(glm::vec3 position, glm::vec3 color, float intensity):
		m_Position(position), m_Color(color), m_Intensity(intensity) {}
	
	void init(glm::vec3 position, glm::vec3 color, float intensity){
		m_Position = position;
		m_Color = color;
		m_Intensity = intensity;
	}

    glm::vec3 & getPosition(){
		return m_Position;
	}

    glm::vec3 & getColor(){
		return m_Color;
	}

    float & getIntensity(){
		return m_Intensity;
	}

    void setIntensity(const float intensity){
        m_Intensity = intensity;
    }

    void setPosition(glm::vec3 newPosition){
        m_Position = newPosition;
    }

	~PointLight(){}
};

