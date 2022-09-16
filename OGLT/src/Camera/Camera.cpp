#include "../../header/Camera/Camera.hpp"

namespace oglt {
  Camera::Camera() {
  }

  Camera::~Camera() {
  }

  const glm::vec3& Camera::GetPosition() const {
    return this->m_Position;
  }

  const glm::vec3& Camera::GetFrontVector() const {
    return this->m_Front;
  }

  const glm::vec3& Camera::GetUpVector() const {
    return this->m_UpVector;
  }

  float Camera::GetSpeed() const {
    return this->a_Speed;
  }

  float Camera::GetFOV() const {
    return this->a_FOV;
  }

  float Camera::GetYaw() const {
    return this->a_Yaw;
  }

  float Camera::GetPitch() const {
    return this->a_Pitch;
  }

  float Camera::GetScale() const {
    return this->a_Scale;
  }

  const CameraType& Camera::GetCameraType() const {
    return this->a_Type;
  }

  const glm::mat4& Camera::GetViewMatrix() const {
    return this->m_ViewMatrix;
  }

  const glm::mat4& Camera::GetProjectionMatrix() const {
    return this->m_ProjectionMatrix;
  }

  const glm::mat4& Camera::GetTransformationMatrix() const {
    return this->m_TransformationMatrix;
  }

  const std::shared_ptr<Shader>& Camera::GetShader() {
    return this->m_Shader;
  }

  float Camera::GetAspectRatio() const {
    return this->a_AspectRatio;
  }

  void Camera::SetAspectRatio(float value) {
    this->a_AspectRatio = value;
  }

  void Camera::SetUpVector(const glm::vec3& value) {
    this->m_UpVector = value;
  }

  void Camera::SetFrontVector(const glm::vec3& value) {
    this->m_Front = value;
    this->RecalculateViewMatrix();
  }

  void Camera::SetViewMatrix(const glm::mat4& value) {
    this->m_ViewMatrix = value;
  }

  void Camera::SetProjectionMatrix(const glm::mat4& value) {
    this->m_ProjectionMatrix = value;
  }

  void Camera::SetTransformationMatrix(const glm::mat4& value) {
    this->m_TransformationMatrix = value;
  }

  void Camera::RecalculateViewMatrix() {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(this->a_Rotation), glm::vec3(0, 0, 1));

    this->m_ViewMatrix = glm::inverse(transform);
  }

  void Camera::SetPosition(const glm::vec3& value) {
    this->m_Position = value;
  }

  void Camera::SetShader(const std::shared_ptr<Shader>& shader) {
    this->m_Shader = shader;
  }

  void Camera::SetSpeed(float value) {
    this->a_Speed = value;
  }

  void Camera::SetFOV(float value) {
    this->a_FOV = value;
  }

  void Camera::SetYaw(float value) {
    this->a_Yaw = value;
  }

  void Camera::SetPitch(float value) {
    this->a_Pitch = value;
  }

  void Camera::SetCameraType(const CameraType& type) {
    this->a_Type = type;
  }

  void Camera::SetScale(float value) {
    this->a_Scale = value;
  }
}
