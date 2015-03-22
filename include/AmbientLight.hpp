#pragma once
#include <glm/glm.hpp>


class AmbientLight {
private:
	float m_Intensity;
	glm::vec3 m_Color;
	
public:
    AmbientLight(){}
	

    glm::vec3 & getColor() {
		return m_Color;
	}

    float & getIntensity(){
		return m_Intensity;
	}

    void init(glm::vec3 color, float intensity){
		m_Color = color;
		m_Intensity = intensity;
	}
    ~AmbientLight(){}
};


