#include "camera.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cmath>


Camera::Camera()
{
    UpdateVectors();
    UpdateMatrices();
    UpdateProjectionMatrix();
}

Camera::~Camera() = default;



void Camera::Move(const glm::vec3& offset)
{
    m_CameraPos += offset;

    UpdateMatrices();
}



void Camera::Rotate(float yawOffset, float pitchOffset)
{
    m_Yaw += yawOffset;

    m_Pitch = std::clamp(
        m_Pitch + pitchOffset,
        -89.0f,
        89.0f
    );

    UpdateVectors();
    UpdateMatrices();
}



void Camera::SetPosition(const glm::vec3& position)
{
    m_CameraPos = position;

    UpdateMatrices();
}

void Camera::SetRotation(float yaw, float pitch)
{
    m_Yaw = yaw;
    m_Pitch = std::clamp(pitch, -89.0f, 89.0f);

    UpdateVectors();
    UpdateMatrices();
}

void Camera::SetFov(float fov)
{
    m_Fov = fov;

    UpdateProjectionMatrix();
}

void Camera::SetAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;

    UpdateProjectionMatrix();
}



const glm::vec3& Camera::GetPosition() const
{
    return m_CameraPos;
}

const glm::vec3& Camera::GetForward() const
{
    return m_Forward;
}

const glm::vec3& Camera::GetUp() const
{
    return m_Up;
}

const glm::vec3& Camera::GetRight() const
{
    return m_Right;
}

const glm::mat4& Camera::GetViewMatrix() const
{
    return m_ViewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
    return m_ProjectionMatrix;
}

const glm::mat4& Camera::GetInverseViewProjection() const
{
    return m_InverseViewProjMatrix;
}

float Camera::GetYaw() const
{
    return m_Yaw;
}

float Camera::GetPitch() const
{
    return m_Pitch;
}

float Camera::GetFov() const
{
    return m_Fov;
}

float Camera::GetAspectRatio() const
{
    return m_AspectRatio;
}



void Camera::ProcessInputs(GLFWwindow* window, float dt)
{
    float speed = m_Speed;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        speed *= 3.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Move(m_Forward * speed * dt);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Move(-m_Forward * speed * dt);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Move(-m_Right * speed * dt);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Move(m_Right * speed * dt);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        Move(m_Up * speed * dt);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        Move(-m_Up * speed * dt);


    // Mouse rotation

    static float lastX = 0.0f;
    static float lastY = 0.0f;
    static bool firstMouse = true;

    double mouseX;
    double mouseY;

    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (firstMouse)
    {
        lastX = static_cast<float>(mouseX);
        lastY = static_cast<float>(mouseY);
        firstMouse = false;
    }

    float deltaX =
        (static_cast<float>(mouseX) - lastX) *
        m_Sensitivity;

    float deltaY =
        (lastY - static_cast<float>(mouseY)) *
        m_Sensitivity;

    lastX = static_cast<float>(mouseX);
    lastY = static_cast<float>(mouseY);

    Rotate(deltaX, deltaY);
}



void Camera::UpdateVectors()
{
    glm::vec3 direction;

    direction.x =
        std::cos(glm::radians(m_Yaw)) *
        std::cos(glm::radians(m_Pitch));

    direction.y =
        std::sin(glm::radians(m_Pitch));

    direction.z =
        std::sin(glm::radians(m_Yaw)) *
        std::cos(glm::radians(m_Pitch));

    m_Forward = glm::normalize(direction);

    m_Right = glm::normalize(
        glm::cross(
            m_Forward,
            glm::vec3(0.0f, 1.0f, 0.0f)
        )
    );

    m_Up = glm::normalize(
        glm::cross(m_Right, m_Forward)
    );
}

void Camera::UpdateMatrices()
{
    m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_Forward, m_Up);

    m_InverseViewProjMatrix = glm::inverse(m_ProjectionMatrix * m_ViewMatrix);
}

void Camera::UpdateProjectionMatrix()
{
    m_ProjectionMatrix = glm::perspective(
        glm::radians(m_Fov),
        m_AspectRatio,
        m_NearPlane,
        m_FarPlane
    );
}
