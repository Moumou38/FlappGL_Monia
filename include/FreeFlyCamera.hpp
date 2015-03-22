#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#ifndef M_PI
#define M_PI 3.141592f
#endif

class FreeFlyCamera {
    private:
        float m_fPhi;
        float m_fTheta;
        glm::vec3 m_Position; 
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector; 
        glm::vec3 m_Up;

    public:
        FreeFlyCamera(){
            m_Position = glm::vec3(0,0,5);
            m_fPhi = glm::degrees(M_PI);
            m_fTheta = 0;
            AngleToSphere();
        }

        FreeFlyCamera(glm::vec3 position){
            m_Position = position;
            m_fPhi = glm::degrees(M_PI);
            m_fTheta = 0;
            AngleToSphere();
        }

        inline void moveLeft(float t){
            m_Position += t*m_LeftVector;
        }

        inline void moveFront(float t){
            m_Position += t*m_FrontVector;
        }

        inline void moveUp(float t){
            m_Position += t*m_Up;
        }

        inline void rotatePhi(float degrees){
            m_fPhi += degrees;
        }

        inline void rotateTheta(float degrees){
            m_fTheta += degrees;
            if((m_fTheta>glm::degrees(M_PI/2))||(m_fTheta<glm::degrees(-M_PI/2))){
                m_fTheta -= degrees;
            }
        }

        inline glm::mat4 getViewMatrix() const{
            return glm::lookAt(m_Position, m_Position + m_FrontVector, m_Up);
        }

        inline glm::vec3& getPosition(){
			return m_Position;
        }

        inline float& getPhi(){
            return m_fPhi;
        }

        inline float& getTheta(){
            return m_fTheta;
        }

        inline void setPosition(glm::vec3 newPosition){
            m_Position = newPosition;
        }

        inline void setPhi(float newPhi){
            m_fPhi = newPhi;
        }

        inline void setTheta(float newTheta){
            m_fTheta = newTheta;
        }


        void AngleToSphere(){
            m_LeftVector = glm::vec3(
                                sin(glm::radians(m_fPhi)+(M_PI/2)),
                                0,
                                cos(glm::radians(m_fPhi)+(M_PI/2))
                            );

            m_FrontVector = glm::vec3(
                cos(glm::radians(m_fTheta))*sin(glm::radians(m_fPhi)),
                sin(glm::radians(m_fTheta)),
                cos(glm::radians(m_fTheta))*cos(glm::radians(m_fPhi))
            );
            m_Up = glm::cross(m_FrontVector, m_LeftVector);
        }

};

