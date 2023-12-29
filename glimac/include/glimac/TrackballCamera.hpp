#pragma once

#include <cmath>
#include "common.hpp"

namespace glimac {

class TrackballCamera {
public:
  TrackballCamera()
  {}

  void moveFront(const float delta)
  {
    m_fDistance = std::fmax(0.f, m_fDistance + delta);
  }

  void rotateLeft(const float degrees)
  {
    m_fAngleY = fmod(m_fAngleY + degrees, 360.f);
  }

  void rotateUp(const float degrees)
  {
    m_fAngleX = fmod(m_fAngleX + degrees, 360.f);
  }

  glm::mat4 getViewMatrix() const
  {
    glm::mat4 vmat = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance));
    vmat = glm::rotate(vmat, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    vmat = glm::rotate(vmat, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    return vmat;
  }

private:
  float m_fDistance = 5.f;  /**< Distance from the scene center. */
  float m_fAngleX = 0.f;    /**< Camera X angle in degrees. */
  float m_fAngleY = 0.f;    /**< Camera Y angle in degrees. */
};

}