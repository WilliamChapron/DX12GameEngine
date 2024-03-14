#include "pch.h"

//#include "GameObject.hpp"
//
//#include "../../renderer/Graphics.h"
//
//#include "../components/Component.h"  
//#include "../systems/ComponentManager.h"  
//
//#include "../../core/Engine.h"  
//#include "../components/Camera.h"
//
//#include "../components/Texture.h"
//#include "../components/Transform.h"
//#include "../components/Mesh.h"
//#include "../components/MeshRenderer.h"
//#include "../components/Collider.h"
//
//#include "../../renderer/Resources.h"





GameObject::GameObject(ComponentManager* componentManager, std::string name) : m_pComponentManager(componentManager), m_needRender(true), m_needCollide(false), m_name(name)
{
}

void GameObject::Initialize(Renderer* renderer, Camera* camera, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale, Mesh* mesh, ConstantBufferData* cbData, bool needCollide) {

    m_needCollide = needCollide;

    // Specific to each object
    Transform* baseTransform = new Transform(position, rotation, scale);
    m_pComponentManager->AddComponent(*this, baseTransform);  



    MeshRenderer* baseMeshRenderer = new MeshRenderer("MeshRenderer", cbData, mesh); // Component
    baseMeshRenderer->Initialize(renderer, cbData);
    m_pComponentManager->AddComponent(*this, baseMeshRenderer);

    ColliderComponent* baseCollider = new ColliderComponent("ColliderComponent");
    baseCollider->InitializeBoundingBox(this, mesh->GetVertices(), mesh->GetNumVertices());
    m_pComponentManager->AddComponent(*this, baseCollider);

    ScriptComponent* scriptComponent = new ScriptComponent("ScriptComponent", this);
    m_pComponentManager->AddComponent(*this, scriptComponent);
}






void GameObject::Update(Renderer* renderer, Camera* camera)
{
    Transform* transformComponent = GetComponent<Transform>(ComponentType::Transform);
    MeshRenderer* meshComponent = GetComponent<MeshRenderer>(ComponentType::MeshRenderer);




    ConstantBufferData sendToMeshCbData;
    sendToMeshCbData.view = camera->GetViewMatrix();
    XMStoreFloat4x4(&sendToMeshCbData.view, XMMatrixTranspose(XMMatrixInverse(nullptr, XMMatrixTranspose(XMLoadFloat4x4(&sendToMeshCbData.view)))));

    sendToMeshCbData.projection = camera->GetProjectionMatrix();


    sendToMeshCbData.model = transformComponent->GetTransformMatrix();



    meshComponent->UpdateConstantBuffer(&sendToMeshCbData);
    m_pComponentManager->UpdateComponents(this);
}