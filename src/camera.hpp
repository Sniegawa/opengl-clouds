#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class Camera
{
public:
    Camera();
    ~Camera();

    void Move(const glm::vec3& offset);
    void Rotate(float yawOffset, float pitchOffset);

    void SetPosition(const glm::vec3& position);
    void SetRotation(float yaw, float pitch);
    void SetFov(float fov);
    void SetAspectRatio(float aspectRatio);

    const glm::vec3& GetPosition() const;
    const glm::vec3& GetForward() const;
    const glm::vec3& GetUp() const;
    const glm::vec3& GetRight() const;

    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;
    const glm::mat4& GetInverseViewProjection() const;

    float GetYaw() const;
    float GetPitch() const;
    float GetFov() const;
    float GetAspectRatio() const;

    void ProcessInputs(GLFWwindow* window, float dt);

private:
    void UpdateMatrices();
    void UpdateProjectionMatrix();
    void UpdateVectors();

private:
    glm::vec3 m_CameraPos{0.0f, 0.0f, 3.0f};

    glm::vec3 m_Forward{0.0f, 0.0f, -1.0f};
    glm::vec3 m_Up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_Right{1.0f, 0.0f, 0.0f};

    float m_Yaw = -90.0f;
    float m_Pitch = 0.0f;

    float m_Fov = 60.0f;
    float m_AspectRatio = 16.0f / 9.0f;

    float m_NearPlane = 0.1f;
    float m_FarPlane = 100000.0f;

    float m_Speed = 10.0f;
    float m_Sensitivity = 0.1f;

    glm::mat4 m_ViewMatrix{1.0f};
    glm::mat4 m_ProjectionMatrix{1.0f};
    glm::mat4 m_InverseViewProjMatrix{1.0f};
};
