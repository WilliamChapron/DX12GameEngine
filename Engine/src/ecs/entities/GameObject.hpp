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
    GameObject(ComponentManager* componentManager, std::string name);

    void Initialize(Renderer* renderer, Camera* camera, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale, Mesh* mesh, ConstantBufferData* cbData, Vertex* vertices, int numVertices);
    void Initialize(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);
    void Update(Renderer* renderer, Camera* camera);
    void Render();

    std::list<Component*> componentsList;

    int deadState;
    std::string m_name;

protected:
    
private:

public:
    template <typename T>
    T* GetComponent(ComponentType type) {
        Component* component = m_pComponentManager->GetGameObjectComponentByType(*this, type);
        return dynamic_cast<T*>(component);
    }
protected:
    
    ComponentManager* m_pComponentManager;
private:

};

