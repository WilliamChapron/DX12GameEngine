#include "pch.h"

//#include "Transform.h"
//#include "./Component.h"


Transform::Transform(const XMFLOAT3& pos, const XMFLOAT3& rot, const XMFLOAT3& scl) : Component("Transform", ComponentType::Transform), vPosition(0.0f, 0.0f, 0.0f), vRotation(0.0f, 0.0f, 1.0f), qRotation(0.0f, 0.0f, 0.0f, 1.0f), vScale(1.0f, 1.0f, 1.0f)
{
    Init();
    SetPosition(pos.x, pos.y, pos.z);
    SetRotation(rot.x, rot.y, rot.z);
    SetScale(scl.x, scl.y, scl.z);
}

void Transform::Update() {
    //PRINT("Update Texture");
}

void Transform::IdentityRotation()
{
    qRotation.x = 0.0f;
    qRotation.y = 0.0f;
    qRotation.z = 0.0f;
    qRotation.w = 1.0f;

    XMMATRIX rotationMatrix = XMMatrixIdentity();
    XMStoreFloat4x4(&mRotation, rotationMatrix);

    vForward = XMFLOAT3(0.0f, 0.0f, 1.0f);
    vRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
    vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
}

void Transform::Init() {
    XMMATRIX positionMatrix = XMMatrixIdentity();
    XMStoreFloat4x4(&mPosition, positionMatrix);

    IdentityRotation();
        
    XMMATRIX scaleMatrix = XMMatrixIdentity();
    XMStoreFloat4x4(&mScale, scaleMatrix);

    XMMATRIX worldMatrix = XMMatrixIdentity();
    XMStoreFloat4x4(&mWorld, worldMatrix);

}



XMFLOAT4X4 Transform::GetTransformMatrix() const
{
    return mWorld;
}

XMFLOAT3 Transform::GetPosition() const
{
    return vPosition;
}

XMFLOAT3 Transform::GetScale() const {
    return vScale;
}

XMFLOAT3 Transform::GetRotation() const {
    return vRotation;
}

XMFLOAT3 Transform::GetDirVectorForward() const
{
    return vForward;
}

XMFLOAT3 Transform::GetDirVectorRight() const
{
    return vRight;
}

XMFLOAT3 Transform::GetDirVectorUp() const
{
    return vUp;
}


void Transform::UpdateTransformMatrix()
{
    XMMATRIX transformMatrix = XMLoadFloat4x4(&mScale) * XMLoadFloat4x4(&mRotation) * XMLoadFloat4x4(&mPosition);

    transformMatrix = XMMatrixTranspose(transformMatrix);

    XMStoreFloat4x4(&mWorld, transformMatrix);
}

void Transform::SetRotation(float pitch, float roll, float yaw) {

    XMMATRIX rotationMatrix = XMMatrixIdentity();
    XMStoreFloat4x4(&mRotation, rotationMatrix);

    vForward = XMFLOAT3(0.0f, 0.0f, 1.0f);
    vRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
    vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);

    vRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
    qRotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

    Rotate(pitch, roll, yaw);
    UpdateTransformMatrix();
}


void Transform::Rotate(float pitch, float roll, float yaw)
{
    XMVECTOR forwardVector = XMLoadFloat3(&vForward);
    XMVECTOR rightVector = XMLoadFloat3(&vRight);
    XMVECTOR upVector = XMLoadFloat3(&vUp);


    XMVECTOR qRoll = XMQuaternionRotationAxis(forwardVector, roll);
    XMVECTOR qPitch = XMQuaternionRotationAxis(rightVector, pitch);
    XMVECTOR qYaw = XMQuaternionRotationAxis(upVector, yaw);
    XMVECTOR q = XMQuaternionMultiply(qRoll, qPitch);
    q = XMQuaternionMultiply(q, qYaw);

    XMVECTOR rotationQuaternion = XMLoadFloat4(&qRotation);
    rotationQuaternion = XMQuaternionMultiply(rotationQuaternion, q);
    XMStoreFloat4(&qRotation, rotationQuaternion);

    XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotationQuaternion);
    XMStoreFloat4x4(&mRotation, rotationMatrix);

    vRight.x = mRotation._11;
    vRight.y = mRotation._12;
    vRight.z = mRotation._13;

    vUp.x = mRotation._21;
    vUp.y = mRotation._22;
    vUp.z = mRotation._23;

    vForward.x = mRotation._31;
    vForward.y = mRotation._32;
    vForward.z = mRotation._33;


    //XMFLOAT3 euler = QuaternionToEulerAngles(qRotation);
    //vRotation.x = euler.x;
    //vRotation.y = euler.y;
    //vRotation.z = euler.z;


    UpdateTransformMatrix();
}

// #TODO add function SET ROTATIO / GET CURRENT ROTATION 

void Transform::SetPosition(float offsetX, float offsetY, float offsetZ)
{
    vPosition.x = offsetX;
    vPosition.y = offsetY;
    vPosition.z = offsetZ;

    // SET , no matter the old position
    XMMATRIX translationMatrix = XMMatrixTranslation(offsetX, offsetY, offsetZ);
    XMStoreFloat4x4(&mPosition, translationMatrix);

    UpdateTransformMatrix();
}

void Transform::Translate(float offsetX, float offsetY, float offsetZ)
{
    vPosition.x += offsetX;
    vPosition.y += offsetY;
    vPosition.z += offsetZ;

    // Old pos + Offset
    XMMATRIX translationMatrix = XMMatrixTranslation(vPosition.x + offsetX, vPosition.y + offsetY, vPosition.z + offsetZ);
    XMStoreFloat4x4(&mPosition, translationMatrix);

    UpdateTransformMatrix();
}

void Transform::SetScale(float scaleX, float scaleY, float scaleZ) {

    vScale.x = scaleX;
    vScale.y = scaleY;
    vScale.z = scaleZ;

    XMMATRIX scalingMatrix = XMMatrixScaling(scaleX, scaleY, scaleZ);

    XMStoreFloat4x4(&mScale, scalingMatrix);
    UpdateTransformMatrix();
}