#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum camMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float SPEED       = 100.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

class Camera
{
public:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Pitch;

    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;

    Camera() = default;
    Camera(glm::vec3 Position, glm::vec3 Up, glm::vec3 Front);
    ~Camera();

    glm::mat4 GetViewMatrix();
    glm::vec3 GetPos();
    void ProcessKeyboard(camMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void updateCameraVectors();
};