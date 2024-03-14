#pragma once
//#include "pch.h"
#include "../entities/GameObject.hpp"
using namespace DirectX;

class Transform;

class Camera : public GameObject
{
public:
    Camera(ComponentManager* componentManager, float fov = XM_PIDIV4, float aspectRatio = 16.0f / 9.0f, float nearPlane = 0.1f, float farPlane = 100.0f);
    void Initialize(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);
    ~Camera() {};

    void Update(float deltaTime);
    void UpdatePosition(XMFLOAT3 displacement);
    void UpdatePosition(float x, float y, float z);


    void UpdateTarget(XMFLOAT3 m_newTarget);


    // William 

    XMFLOAT3 GetPosition();
    XMFLOAT3 GetDirection();

    //
    XMFLOAT4X4 GetViewMatrix() const;
    XMFLOAT4X4 GetProjectionMatrix() const { return f_projectionMatrix; };

    void Rotate(float x, float y);
    void RotateAroundTarget(float pitch, float yaw, float roll);


private:
    ComponentManager* m_pComponentManager;
    float fov, aspectRatio, nearPlane, farPlane;
    float pitch, yaw;

    Transform* transform;

    XMFLOAT3 m_position;
    XMFLOAT3 m_target;
    XMFLOAT3 m_up;

    XMMATRIX m_projectionMatrix;
    XMMATRIX m_transposedViewMatrix;
    XMMATRIX m_transposedProjectionMatrix;

    XMFLOAT4X4 f_projectionMatrix;
};