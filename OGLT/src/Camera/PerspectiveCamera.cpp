#include "../../header/Camera/PerspectiveCamera.hpp"

namespace oglt {
  PerspectiveCamera::PerspectiveCamera() {
    this->SetViewMatrix(glm::mat4(1.0f));
    this->SetProjectionMatrix(glm::mat4(1.0f));
    this->SetTransformationMatrix(glm::mat4(1.0f));

    this->SetPosition(glm::vec3(0.0f, 0.0f, 2.4f));
    this->SetFrontVector(glm::vec3(0.0f, 0.0f, -1.0f));
    this->SetUpVector(glm::vec3(0.0f, 1.0f, 0.0f));

    this->SetYaw(-90.0f);
    this->SetPitch(0.0f);
    this->SetFOV(45.0f);
    
    this->SetSpeed(10.0f);
    this->SetScale(1.0f);

    this->SetUpShaders();
  }

  PerspectiveCamera::~PerspectiveCamera() {
  }

  void PerspectiveCamera::SetUpShaders() {
    this->SetShader(std::make_shared<Shader>("./OGLT/shader/perspec.vert", "./OGLT/shader/perspec.frag"));
  }

  void PerspectiveCamera::CalculatePositition() {
    this->SetViewMatrix(glm::lookAt(this->GetPosition(),
				    this->GetPosition() + this->GetFrontVector(),
				    this->GetUpVector()));
    this->SetProjectionMatrix(glm::perspective(glm::radians(this->GetFOV()),
					       this->GetAspectRatio(),
					       0.1f,
					       100.0f));
  }

  void PerspectiveCamera::SubmitPosition() {
    this->GetShader()->SetMat4("projection", this->GetProjectionMatrix());
    this->GetShader()->SetMat4("view", this->GetViewMatrix());
    this->GetShader()->SetMat4("model", this->GetTransformationMatrix());
    this->GetShader()->Bind();
  }

  void PerspectiveCamera::MoveUp(float dt) {
    this->SetPosition(this->GetPosition() + this->GetUpVector() * this->GetSpeed() * dt);
  }

  void PerspectiveCamera::MoveDown(float dt) {
    this->SetPosition(this->GetPosition() - this->GetUpVector() * this->GetSpeed() * dt);
  }

  void PerspectiveCamera::MoveLeft(float dt) {
    this->SetPosition(this->GetPosition() - glm::normalize(glm::cross(this->GetFrontVector(), this->GetUpVector())) * this->GetSpeed() * dt);
  }

  void PerspectiveCamera::MoveRight(float dt) {
    this->SetPosition(this->GetPosition() + glm::normalize(glm::cross(this->GetFrontVector(), this->GetUpVector())) * this->GetSpeed() * dt);
  }
}
