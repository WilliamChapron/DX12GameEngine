#include "pch.h"


// Pass Instance of GameObjectManager to Work with alive entity
ComponentManager::ComponentManager(std::shared_ptr<GameObjectManager>& gameObjectManager, Renderer* renderer) : m_pGameObjectManager(gameObjectManager), m_pRenderer(renderer)
{
}

void ComponentManager::AddCamera(Camera* camera)
{
    m_pCamera = camera;
}



bool CompareByPriority(const Component* leftValue, const Component* rightValue) {
    ComponentType leftType = leftValue->GetType();
    ComponentType rightType = rightValue->GetType();
    return static_cast<int>(leftType) < static_cast<int>(rightType); // Get value associate at an enum
}

void ComponentManager::SortComponentsMap(GameObject& gameObject) {
    std::vector<Component*> componentsVector(gameObject.componentsList.begin(), gameObject.componentsList.end());

    // Sort by priority
    std::stable_sort(componentsVector.begin(), componentsVector.end(), CompareByPriority);

    gameObject.componentsList.assign(componentsVector.begin(), componentsVector.end());
}


void ComponentManager::AddComponent(GameObject& gameObject, Component* addComponent) {

    // Check if the component is already in the object
    for (const Component* component : gameObject.componentsList) {
        if (component->GetName() == addComponent->GetName()) {
            return;
        }
    }
    gameObject.componentsList.push_back(addComponent);
    SortComponentsMap(gameObject);
}

void ComponentManager::UpdateComponents(GameObject* gameObject) {
    for (const auto& pair : gameObject->componentsList)
    {
        pair->Update(m_pRenderer);
    }
}

Component* ComponentManager::GetGameObjectComponentByType(GameObject& gameObject, ComponentType componentType) {
    for (Component* component : gameObject.componentsList) {
        if (component->GetType() == componentType) {
            return component;
        }
    }
    return nullptr;
}

