#pragma once


using namespace DirectX;
using Microsoft::WRL::ComPtr;

#include "../systems/ComponentManager.h"

class Renderer;
class Component;
class Camera;
class Mesh;
class MeshRenderer;
struct ConstantBufferData;
struct Vertex;
class ComponentManager;


class GameObject
{
public:
    GameObject(ComponentManager* componentManager);

    void Initialize(Renderer* renderer, Camera* camera, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale, Mesh* mesh, ConstantBufferData* cbData, Vertex* vertices, int numVertices);
    void Update(Renderer* renderer, Camera* camera);


    




    std::list<Component*> componentsList;

protected:
    
private:

    //ConstantBufferData m_cbData;

    ComponentManager* m_pComponentManager;
public:
    template <typename T>
    T* GetComponent(ComponentType type) {
        Component* component = m_pComponentManager->GetGameObjectComponentByType(*this, type);
        return dynamic_cast<T*>(component);
    }
};

