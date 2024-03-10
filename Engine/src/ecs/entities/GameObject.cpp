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





GameObject::GameObject(ComponentManager* componentManager) : m_pComponentManager(componentManager)
{
}

void GameObject::Initialize(Renderer* renderer, Camera* camera, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale, Mesh* mesh, ConstantBufferData* cbData, Vertex* vertices, int numVertices) {
    // Specific to each object
    Transform* baseTransform = new Transform(position, rotation, scale);
    m_pComponentManager->AddComponent(*this, baseTransform);  

    MeshRenderer* baseMeshRenderer = new MeshRenderer("MeshRenderer", cbData, mesh); // Component
    baseMeshRenderer->Initialize(renderer, cbData);
    m_pComponentManager->AddComponent(*this, baseMeshRenderer);

    ColliderComponent* baseCollider = new ColliderComponent("ColliderComponent");
    baseCollider->InitializeBoundingBox(this, vertices, numVertices);
    m_pComponentManager->AddComponent(*this, baseCollider);
}






void GameObject::Update(Renderer* renderer, Camera* camera)
{
    Transform* transformComponent = GetComponent<Transform>(ComponentType::Transform);
    MeshRenderer* meshComponent = GetComponent<MeshRenderer>(ComponentType::MeshRenderer);




    ConstantBufferData* sendToMeshCbData = new ConstantBufferData();
    sendToMeshCbData->view = camera->GetViewMatrix();
    sendToMeshCbData->projection = camera->GetProjectionMatrix();


    sendToMeshCbData->model = transformComponent->GetTransformMatrix();



    meshComponent->UpdateConstantBuffer(sendToMeshCbData);
    m_pComponentManager->UpdateComponents(this);
}