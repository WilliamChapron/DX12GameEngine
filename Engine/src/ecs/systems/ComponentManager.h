#pragma once


//#include "../entities/GameObject.h"  
#include "../components/Component.h"  


class GameObjectManager;
class GameObject;
class Renderer;

class ComponentManager
{
public:
    ComponentManager(std::shared_ptr<GameObjectManager>& gameObjectManager, Renderer* renderer);

    // Actions to add, remove, ... on a game object
    void AddComponent(GameObject& gameObject, Component* component);
    //void RemoveComponent(GameObject gameObject, Component& component);
    //void RemoveAllComponents(GameObject& gameObject);
    void UpdateComponents(GameObject& gameObject);

    Component* GetComponentByType(GameObject& gameObject, ComponentType componentType);


private:
    //std::map<GameObject*, std::list<Component*>> componentsByGameObject;
    std::shared_ptr<GameObjectManager> m_pGameObjectManager;
    Renderer* m_pRenderer;
};
