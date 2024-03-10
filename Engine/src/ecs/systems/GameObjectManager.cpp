#include "../../../pch.h"

#include "GameObjectManager.h"

#include "../../renderer/Graphics.h" 

#include "../components/Component.h" 
#include "../components/Collider.h" 

#include "../entities/GameObject.hpp"


GameObjectManager::GameObjectManager(Camera* camera) : m_pCamera(camera) {}

// Ajouter un objet au gestionnaire
void GameObjectManager::AddObject(const std::string& name, GameObject* object) {
    objectMap[name] = object;
    PRINT("Object added: " << name);
}

// Supprimer un objet du gestionnaire
void GameObjectManager::RemoveObject(const std::string& name) {
    auto it = objectMap.find(name);
    if (it != objectMap.end()) {
        objectMap.erase(it);
        PRINT("Object erased: " << name);
    }


}

void GameObjectManager::Update(Renderer* renderer) {
    HRESULT hr;

    renderer->Precommandlist();



    PRINT("Frame");
    std::vector<TestedPair> testedPairs;

    for (auto& pair : objectMap) {
        GameObject* gameObject = pair.second;

        gameObject->Update(renderer, m_pCamera);

        // tryCollide = object on which we test collision
        for (auto& tryCollide : objectMap) {
            if (tryCollide.first == pair.first) {
                continue;
            }

            TestedPair objectPair{ pair.first, tryCollide.first };

            auto it = std::find(testedPairs.begin(), testedPairs.end(), objectPair);
            if (it != testedPairs.end()) {
                continue;
            }

            ColliderComponent* colliderComponent = gameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);


            std::cout << "Check Collide Object : " << pair.first << " With : " << tryCollide.first << std::endl;
            PRINT(colliderComponent->CheckCollision(tryCollide.second));

            testedPairs.push_back(objectPair);
        }
    }


    renderer->Postcommandlist();

    ID3D12CommandList* ppCommandLists[] = { renderer->m_pCommandList.Get() };
    renderer->m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    hr = renderer->m_pSwapChain->Present(1, 0);
    renderer->m_frameIndex = (renderer->m_frameIndex + 1) % renderer->m_FRAME_COUNT;
    ASSERT_FAILED(hr);

    renderer->WaitForPreviousFrame();
};