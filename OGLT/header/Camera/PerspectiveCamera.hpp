#ifndef __PERSPECTIVE_CAMERA_HPP__
#define __PERSPECTIVE_CAMERA_HPP__

#include "./Camera.hpp"

namespace oglt {
  class PerspectiveCamera final : public Camera {
  public:
    PerspectiveCamera();
    virtual ~PerspectiveCamera();

    void CalculatePositition() override;
    void SubmitPosition() override;
    void SetUpShaders() override;
    void MoveUp(float dt) override;
    void MoveDown(float dt) override;
    void MoveLeft(float dt) override;
    void MoveRight(float dt) override;

  private:
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_TransformMatrix;
  };
}

#endif // __PERSPECTIVE_CAMERA_HPP__
