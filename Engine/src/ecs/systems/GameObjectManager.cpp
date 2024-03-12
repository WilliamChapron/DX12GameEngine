#include "pch.h"

//#include "GameObjectManager.h"
//
//#include "../../renderer/Graphics.h" 
//
//#include "../components/Component.h" 
//#include "../components/Collider.h" 
//
//#include "../entities/GameObject.hpp"


GameObjectManager::GameObjectManager(Camera* camera) : m_pCamera(camera) {}


void GameObjectManager::AddObject(const std::string& name, GameObject* object) {
    objectMap[name] = object;
    PRINT("Object added: " << name);
}


void GameObjectManager::RemoveObject(GameObject* object) {
    auto it = std::find_if(objectMap.begin(), objectMap.end(), [object](const auto& pair) {
        return pair.second == object;
    });

    if (it != objectMap.end()) {
        PRINT("Removing object: " << it->first);
        object->deadState = 1;
       // objectMap.erase(it);
    }
    else {
        PRINT("Object not found for removal.");
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

        ColliderComponent* colliderComponent = gameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);
        colliderComponent->m_collideState = 0;

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


            ColliderComponent* colliderComponentTryCollide = tryCollide.second->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);


            //std::cout << "Check Collide Object : " << pair.first << " With : " << tryCollide.first << std::endl;

            // If collision detect, Game object have collide
            if (colliderComponent->CheckCollision(tryCollide.second)) {
                break;
            };

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


    //for (auto& item : objectMap) {
    //    if (item.second->deadState) {
    //        PRINT("Removing dead object: ");

    //        delete item.second;
    //        objectMap.erase(item.first);
    //    }
    //}


};