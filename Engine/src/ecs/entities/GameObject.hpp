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

    inline ~GameObject()
    {
        for (Component* component : componentsList)
        {
            delete component;
        }
        componentsList.clear();
    }

    virtual void Initialize(Renderer* renderer, Camera* camera, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale, Mesh* mesh, ConstantBufferData* cbData, bool needCollide);
    virtual void Initialize(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale) {};

    void Update(Renderer* renderer, Camera* camera);
    void Render();

    std::list<Component*> componentsList;

    bool m_needRender;
    bool m_needCollide;

    std::string m_name;

protected:
    
private:



    ComponentManager* m_pComponentManager;
public:
    template <typename T>
    T* GetComponent(ComponentType type) {
        Component* component = m_pComponentManager->GetGameObjectComponentByType(*this, type);
        return dynamic_cast<T*>(component);
    }
};

