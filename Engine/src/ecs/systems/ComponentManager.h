#pragma once

#include "../components/Component.h"
#include "../entities/GameObject.hpp"

class GameObjectManager;
class GameObject;
class Renderer;
class TextureComponent;
class Mesh;
class MeshRenderer;


class ComponentManager
{
public:
    ComponentManager(std::shared_ptr<GameObjectManager>& gameObjectManager, Renderer* renderer);
    void AddCamera(Camera* camera);

    // Actions to add, remove, ... on a game object
    ComponentType GetComponentPriority(Component* component);
    void SortComponentsMap(GameObject& gameObject);
    void AddComponent(GameObject& gameObject, Component* component);


    void UpdateComponents(GameObject* gameObject);




    Component* GetGameObjectComponentByType(GameObject& gameObject, ComponentType componentType);

private:
    Camera* m_pCamera;

    std::shared_ptr<GameObjectManager> m_pGameObjectManager;
    Renderer* m_pRenderer;
};
