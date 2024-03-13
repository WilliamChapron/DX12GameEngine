#pragma once
//#include "pch.h"
#include "../entities/GameObject.hpp"
using namespace DirectX;

class Transform;

class Camera : public GameObject
{
public:
    Camera(ComponentManager* componentManager, float fov = XM_PIDIV4, float aspectRatio = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
    void UpdateTransform();
    //Camera(float fov = XM_PIDIV4, float aspectRatio = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
    ~Camera() {};

    void Update(float deltaTime);
    void UpdatePosition(XMFLOAT3 displacement);
    void UpdatePosition(float x, float y, float z);


    void UpdateTarget(XMFLOAT3 m_newTarget);

    XMFLOAT4X4 GetViewMatrix() const;
    XMFLOAT4X4 GetProjectionMatrix() const { return f_projectionMatrix; };

    void Rotate(float x, float y);
    void RotateAroundTarget(float pitch, float yaw, float roll);

    //Transform* transform;

    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_target;
    DirectX::XMFLOAT3 m_up;

private:
    float pitch, yaw;

    XMFLOAT3 m_defaultForward;

    Transform* transform;

    XMVECTOR currentRotation;

    XMFLOAT3 m_rotation;

    XMMATRIX m_viewMatrix;
    XMMATRIX m_projectionMatrix;
    XMMATRIX m_transposedViewMatrix;
    XMMATRIX m_transposedProjectionMatrix;

    XMFLOAT4X4 f_viewMatrix;
    XMFLOAT4X4 f_projectionMatrix;
};