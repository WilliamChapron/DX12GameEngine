#include "pch.h"
#include "../entities/GameObject.hpp"
#include "Camera.h"

using namespace DirectX;


Camera::Camera(ComponentManager* componentManager, float _fov, float _aspectRatio, float _nearPlane, float _farPlane) : GameObject(componentManager, "Camera"), m_pComponentManager(componentManager), fov(_fov), aspectRatio(_aspectRatio), nearPlane(_nearPlane), farPlane(_farPlane) {
    
}

void Camera::Initialize(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
    Transform* baseTransform = new Transform(position, rotation, scale);
    m_pComponentManager->AddComponent(*this, baseTransform);

    m_projectionMatrix = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
    m_transposedProjectionMatrix = XMMatrixTranspose(m_projectionMatrix);
    XMStoreFloat4x4(&f_projectionMatrix, m_transposedProjectionMatrix);


    pitch = 0.0f;
    yaw = 0.0f;

    transform = GetComponent<Transform>(ComponentType::Transform);
}


void Camera::Update(float deltaTime) {
}

void Camera::UpdatePosition(XMFLOAT3 displacement) {
    transform->Translate(displacement.x * transform->GetDirVectorForward().x, displacement.y * transform->GetDirVectorUp().y, displacement.z * transform->GetDirVectorRight().z);
}

void Camera::UpdatePosition(float x, float y, float z) {

    XMFLOAT3 _pos = transform->GetPosition();

    XMFLOAT3 _dir = XMFLOAT3(0.0f, 0.0f, 0.0f);
    if (x != 0)
    {
        _dir = transform->GetDirVectorRight();
        _dir.x *= x;
        _dir.y *= x;
        _dir.z *= x;
    }

    else if (y != 0)
    {
        _dir = transform->GetDirVectorUp();
        _dir.x *= y;
        _dir.y *= y;
        _dir.z *= y;
    }
    else if (z != 0)
    {
        _dir = transform->GetDirVectorForward();
        _dir.x *= z;
        _dir.y *= z;
        _dir.z *= z;
    }


    XMVECTOR dir = XMVector3Normalize(XMLoadFloat3(&_dir));


    XMVECTOR translation = XMVectorScale(dir, 0.01f);

    XMVECTOR newPosition = XMLoadFloat3(&_pos) + translation;

    XMFLOAT3 newPos;
    XMStoreFloat3(&newPos, newPosition);
    transform->SetPosition(newPos.x, newPos.y, newPos.z);
}


void Camera::Rotate(float x, float y) {

    float dyaw = x * 0.01f;
    float dpitch = y * 0.01f;

    yaw += dyaw;
    pitch += dpitch;

    // gère la limite des rotations
    pitch = Clamp(pitch, -XM_PI * 0.5f, XM_PI * 0.5f);

    transform->IdentityRotation();
    transform->Rotate(pitch, 0.0f, yaw);

    
}

XMFLOAT3 Camera::GetPosition() {
    return XMFLOAT3(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z);
}

XMFLOAT3 Camera::GetDirection() {
    XMFLOAT4X4 rMatrix = transform->GetRotationMatrix();
    XMMATRIX rotation = XMLoadFloat4x4(&rMatrix);
    XMVECTOR directionVector = rotation.r[2];  
    directionVector = XMVector3Normalize(directionVector);

    XMFLOAT3 direction;
    XMStoreFloat3(&direction, directionVector);

    return direction;
}


void Camera::UpdateTarget(XMFLOAT3 m_newTarget)
{
    m_position.x += m_newTarget.x;
    m_position.y += m_newTarget.y;
    m_position.z += m_newTarget.z;
}


XMFLOAT4X4 Camera::GetViewMatrix() const {
    return transform->GetTransformMatrix();
}



// -----------------------------------
void Camera::RotateAroundTarget(float pitch, float yaw, float roll) {
    /*pitch = XMConvertToRadians(pitch);
    yaw = XMConvertToRadians(yaw);
    roll = XMConvertToRadians(roll);

    XMVECTOR positionRelativeToTarget = XMLoadFloat3(&m_position) - XMLoadFloat3(&m_target);
    XMVECTOR rotationQuaternion = XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
    positionRelativeToTarget = XMVector3Rotate(positionRelativeToTarget, rotationQuaternion);

    XMStoreFloat3(&m_position, positionRelativeToTarget + XMLoadFloat3(&m_target));*/
}