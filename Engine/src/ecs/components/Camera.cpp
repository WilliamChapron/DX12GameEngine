//#include "pch.h"
//
//using namespace DirectX;
//
//
//Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane) {
//
//    // Init View Matrix
//    m_position = XMFLOAT3(0.0f, -5.0f, -2.0f);
//    m_target = XMFLOAT3(0.0f, 0.0f, 0.0f);
//    m_up = XMFLOAT3(0.0f, 1.0f, 0.0f);
//
//    m_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&m_up));
//    m_projectionMatrix = XMMatrixTranspose(m_viewMatrix);
//    XMStoreFloat4x4(&f_viewMatrix, m_transposedViewMatrix);
//
//    m_projectionMatrix = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
//
//    m_transposedProjectionMatrix = XMMatrixTranspose(m_projectionMatrix);
//    XMStoreFloat4x4(&f_projectionMatrix, m_transposedProjectionMatrix);
//
//    // D�clarer un quaternion pour stocker l'orientation actuelle de la cam�ra
//    currentRotation = XMQuaternionIdentity();
//}
//
//void Camera::Update(float deltaTime) {
//    // Calculer la matrice de vue
//
//    m_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&m_up));
//    m_projectionMatrix = XMMatrixTranspose(m_viewMatrix);
//    XMStoreFloat4x4(&f_viewMatrix, m_projectionMatrix);
//    //std::cout << m_position.z << std::endl;
//}
//
//void Camera::UpdatePosition(XMFLOAT3 displacement)
//{
//    XMVECTOR m_displacement = XMVector3Rotate(XMLoadFloat3(&displacement), currentRotation);
//
//    // Mettre à jour la position de la caméra en tenant compte du vecteur de déplacement
//    XMVECTOR newPosition = XMLoadFloat3(&m_position) + m_displacement;
//    XMStoreFloat3(&m_position, newPosition);
//
//    // Mettre à jour la cible de la caméra en fonction de la nouvelle position
//    m_target.x = m_position.x + XMVectorGetX(forward);
//    m_target.y = m_position.y + XMVectorGetY(forward);
//    m_target.z = m_position.z + XMVectorGetZ(forward);
//}
//
//void Camera::UpdatePosition(float x, float y, float z)
//{
//    // Calculer le vecteur de translation
//    // Transformer le vecteur de déplacement par la rotation actuelle
//    XMFLOAT3 m_displacementVector(x, y, z);
//    XMVECTOR m_displacement = XMVector3Rotate(XMLoadFloat3(&m_displacementVector), currentRotation);
//
//    // Mettre à jour la position de la caméra en tenant compte du vecteur de déplacement
//    XMVECTOR newPosition = XMLoadFloat3(&m_position) + m_displacement;
//    XMStoreFloat3(&m_position, newPosition);
//
//    // Mettre à jour la cible de la caméra en fonction de la nouvelle position
//    m_target.x = m_position.x + XMVectorGetX(forward);
//    m_target.y = m_position.y + XMVectorGetY(forward);
//    m_target.z = m_position.z + XMVectorGetZ(forward);
//}
//
//void Camera::UpdateTarget(XMFLOAT3 m_newTarget)
//{
//    m_position.x += m_newTarget.x;
//    m_position.y += m_newTarget.y;
//    m_position.z += m_newTarget.z;
//}
//
//
//void Camera::Rotate(float pitch, float yaw, float roll)
//{
//    pitch = XMConvertToRadians(pitch);
//    yaw = XMConvertToRadians(yaw);
//    roll = XMConvertToRadians(roll);
//
//    XMVECTOR rotationQuaternion = XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
//
//    currentRotation = XMQuaternionMultiply(currentRotation, rotationQuaternion);
//
//    forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
//    right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
//    up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//
//    forward = XMVector3Rotate(forward, currentRotation);
//    up = XMVector3Rotate(up, currentRotation);
//    right = XMVector3Rotate(right, currentRotation);
//    
//    m_target.x = m_position.x + XMVectorGetX(forward);
//    m_target.y = m_position.y + XMVectorGetY(forward);
//    m_target.z = m_position.z + XMVectorGetZ(forward);
//
//    m_up.x = XMVectorGetX(up);
//    m_up.y = XMVectorGetY(up);
//    m_up.z = XMVectorGetZ(up);
//}
//
//
//
//
//void Camera::RotateAroundTarget(float pitch, float yaw, float roll) {
//    pitch = XMConvertToRadians(pitch);
//    yaw = XMConvertToRadians(yaw);
//    roll = XMConvertToRadians(roll);
//
//    XMVECTOR positionRelativeToTarget = XMLoadFloat3(&m_position) - XMLoadFloat3(&m_target);
//    XMVECTOR rotationQuaternion = XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
//    positionRelativeToTarget = XMVector3Rotate(positionRelativeToTarget, rotationQuaternion);
//
//    XMStoreFloat3(&m_position, positionRelativeToTarget + XMLoadFloat3(&m_target));
//}


#include "pch.h"
#include "../entities/GameObject.hpp"
//#include "Camera.h"

using namespace DirectX;


Camera::Camera(ComponentManager* componentManager, float fov, float aspectRatio, float nearPlane, float farPlane) : GameObject(componentManager) {
    // Init View Matrix

    m_projectionMatrix = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
    m_transposedProjectionMatrix = XMMatrixTranspose(m_projectionMatrix);
    XMStoreFloat4x4(&f_projectionMatrix, m_transposedProjectionMatrix);

    // Déclarer un quaternion pour stocker l'orientation actuelle de la caméra
    currentRotation = XMQuaternionIdentity();
    m_up = XMFLOAT3(0.0f, 1.0f, 0.0f);
    m_defaultForward = XMFLOAT3(0.0f, 0.0f, 1.0f);

    pitch = 0.0f;
    yaw = 0.0f;
}

void Camera::UpdateTransform()
{
    transform = GetComponent<Transform>(ComponentType::Transform);
}

void Camera::Update(float deltaTime) {
    XMFLOAT3 position = transform->GetPosition();
    XMFLOAT3 rotation = transform->GetRotation();

    float someDistance = 2.0f;
    XMVECTOR forward;
    if (rotation.x == 0.f && rotation.y == 0.f && rotation.z == 0.f)
    {
        forward = XMLoadFloat3(&m_defaultForward);
    }
    else {
        forward = XMVector3Rotate(XMLoadFloat3(&m_defaultForward), XMLoadFloat3(&rotation));
    }
    forward = XMVector3Normalize(forward); // Normaliser le vecteur vers l'avant pour obtenir une direction
    XMFLOAT3 targetPosition;
    XMStoreFloat3(&targetPosition, XMVectorAdd(XMLoadFloat3(&position), XMVectorScale(forward, someDistance)));

    
    // Calculez la matrice de vue directement
    m_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&targetPosition), XMLoadFloat3(&m_up));

    // Transposez la matrice de vue si nécessaire
    m_viewMatrix = XMMatrixTranspose(m_viewMatrix);
    XMStoreFloat4x4(&f_viewMatrix, m_viewMatrix);
}

void Camera::UpdatePosition(XMFLOAT3 displacement) {
    transform->Translate(displacement.x, displacement.y, displacement.z);
}

void Camera::UpdatePosition(float x, float y, float z) {
    transform->Translate(x, y, z);
}

void Camera::Rotate(float _pitch, float _yaw) {
    pitch += _pitch;
    yaw += _yaw;
    
    std::cout << "ROTATION CAMERA bis x : " << pitch << " y : " << yaw << std::endl;
    
    transform->IdentityRotation();
    transform->SetRotation(pitch, yaw, 0.0f);

    std::cout << "ROTATION CAMERA x : " << transform->GetRotation().x << " y : " << transform->GetRotation().y << std::endl;
}




void Camera::UpdateTarget(XMFLOAT3 m_newTarget)
{
    m_position.x += m_newTarget.x;
    m_position.y += m_newTarget.y;
    m_position.z += m_newTarget.z;
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