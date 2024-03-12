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

    inline XMFLOAT4X4 GetViewMatrix() const { return f_viewMatrix; };
    inline XMFLOAT4X4 GetProjectionMatrix() const { return f_projectionMatrix; };

    void Rotate(float _pitch, float _yaw);
    void RotateAroundTarget(float pitch, float yaw, float roll);

    //Transform* transform;

private:
    float pitch, yaw;

    XMFLOAT3 m_defaultForward;

    Transform* transform;

    XMVECTOR currentRotation;

    XMFLOAT3 m_rotation;

    // Direction vector 
    XMVECTOR forward;
    XMVECTOR up;
    XMVECTOR right;

    XMFLOAT3 m_position;
    XMFLOAT3 m_target;
    XMFLOAT3 m_up;

    XMMATRIX m_viewMatrix;
    XMMATRIX m_projectionMatrix;
    XMMATRIX m_transposedViewMatrix;
    XMMATRIX m_transposedProjectionMatrix;

    XMFLOAT4X4 f_viewMatrix;
    XMFLOAT4X4 f_projectionMatrix;
};