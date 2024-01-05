#pragma once

#include <cmath>
#include "common.hpp"

namespace glimac {

class FreeflyCamera {
public:
  FreeflyCamera()
  {
    computeDirectionVectors();
  }

  void moveFront(float t)
  {
    m_Position += t * m_FrontVector;
    computeDirectionVectors();
  }

  void moveLeft(float t)
  {
    m_Position += t * m_LeftVector;
    computeDirectionVectors();
  }

  void rotateLeft(float degrees)
  {
    m_fPhi   = fmod(m_fPhi   + glm::radians(degrees), 2*PI);
    computeDirectionVectors();
  }

  void rotateUp(float degrees)
  {
    m_fTheta = fmod(m_fTheta + glm::radians(degrees), 2*PI);
    computeDirectionVectors();
  }

  glm::mat4 getViewMatrix() const
  {
    glm::vec3 point = m_Position - m_FrontVector;
    return glm::lookAt(m_Position, point, m_UpVector);
  }

private:
  const float PI = glm::pi<float>();

  glm::vec3 m_Position = glm::vec3(0.f, 0.f, -50.f);  /**< Camera position */
  float m_fPhi         = PI;   /**< Phi in radians */
  float m_fTheta       = 0.f;  /**< Theta in radians */

  glm::vec3 m_FrontVector; // F vector
  glm::vec3 m_LeftVector;  // L vector
  glm::vec3 m_UpVector;    // U vector

  void computeDirectionVectors()
  {
    const float phi   = m_fPhi;
    const float theta = m_fTheta; 
    m_FrontVector = glm::vec3(
      glm::cos(theta) * glm::sin(phi),
      glm::sin(theta),
      glm::cos(theta) * glm::cos(phi)
    );
    m_LeftVector  = glm::vec3(
      glm::sin(phi + PI / 2),
      0.f,
      glm::cos(phi + PI / 2)
    );
    m_UpVector    = glm::cross(
      m_FrontVector,
      m_LeftVector
    );
  }
};

}