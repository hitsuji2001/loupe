#include "../../header/Camera/OrthographicCamera.hpp"

namespace oglt {
  OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) {
    this->SetViewMatrix(glm::mat4(1.0f));
    this->SetProjectionMatrix(glm::ortho(left, right, bottom, top, far, near));
    this->SetTransformationMatrix(glm::mat4(1.0f));

    this->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    this->SetFrontVector(glm::vec3(1.0f, 0.0f, 0.0f));
    this->SetUpVector(glm::vec3(0.0f, 1.0f, 0.0f));

    this->SetYaw(0.0f);
    this->SetPitch(0.0f);
    this->SetFOV(0.0f);
    
    this->SetSpeed(5.0f);
    this->SetScale(1.0f);

    this->SetUpShaders();
  }

  OrthographicCamera::~OrthographicCamera() {
  }

  void OrthographicCamera::SetUpShaders() {
    this->SetShader(std::make_shared<Shader>("./OGLT/shader/ortho.vert", "./OGLT/shader/ortho.frag"));
  }

  void OrthographicCamera::CalculatePositition() {
    this->SetViewMatrix(glm::lookAt(this->GetPosition(),
				    glm::vec3(0,0,0), // look at the origin
				    this->GetUpVector()));

  }

  void OrthographicCamera::SubmitPosition() {
    this->GetShader()->SetMat4("projection", this->GetProjectionMatrix());
    this->GetShader()->SetMat4("view", this->GetViewMatrix());
    this->GetShader()->SetMat4("model", this->GetTransformationMatrix());
    this->GetShader()->Bind();
  }

  void OrthographicCamera::MoveUp(float dt) {
    this->SetPosition(this->GetPosition() + this->GetUpVector() * this->GetSpeed() * dt);
  }

  void OrthographicCamera::MoveDown(float dt) {
    this->SetPosition(this->GetPosition() - this->GetUpVector() * this->GetSpeed() * dt);
  }

  void OrthographicCamera::MoveLeft(float dt) {
    this->SetPosition(this->GetPosition() - glm::normalize(glm::cross(this->GetFrontVector(), this->GetUpVector())) * this->GetSpeed() * dt);
  }

  void OrthographicCamera::MoveRight(float dt) {
    this->SetPosition(this->GetPosition() + glm::normalize(glm::cross(this->GetFrontVector(), this->GetUpVector())) * this->GetSpeed() * dt);
  }
}
