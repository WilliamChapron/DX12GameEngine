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
        /*PRINT("Removing object: " << it->first);*/
        object->m_needRender = false;
    }
    else {
        PRINT("Object not found for removal.");
    }
}

void GameObjectManager::Update(Renderer* renderer) {
    HRESULT hr;
    PRINT("Frame");


    renderer->Precommandlist();


    //// Sort object according to their z position, z depth sorting
    //std::vector<ObjectPosZPair> objectPosZPairs;
    //for (auto& pair : objectMap) {
    //    GameObject* gameObject = pair.second;
    //    Transform* transform = gameObject->GetComponent<Transform>(ComponentType::Transform);
    //    float globalZPosition = transform->GetPosition().z;
    //    objectPosZPairs.push_back({ gameObject, globalZPosition });
    //}
    //std::sort(objectPosZPairs.begin(), objectPosZPairs.end());

    std::vector<TestedPair> testedPairs;

    


    for (auto& pair : objectMap) {
        GameObject* gameObject = pair.second;
        ColliderComponent* colliderComponent = gameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);

        if (!gameObject->m_needRender) {
            continue;

        }


        // COLLIDE PART *

        // tryCollide = object on which we test collision

        if (gameObject->m_needCollide) {
            for (auto& tryCollide : objectMap) {
                GameObject* tryCollideObject = tryCollide.second;


                if (!tryCollideObject->m_needCollide) {
                    /*PRINT(tryCollideObject->m_name);*/
                    continue;
                }

                // object is himself
                if (tryCollide.first == pair.first) {
                    continue;
                }
                // if the object with which we are testing the collide does not accept it 

                TestedPair objectPair{ pair.first, tryCollide.first };
                // if already tested, don't try collide
                auto it = std::find(testedPairs.begin(), testedPairs.end(), objectPair);
                if (it != testedPairs.end()) {
                    continue;
                }

                ColliderComponent* colliderComponentTryCollide = tryCollideObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);
                // If collision detect, Game object have collide
                if (colliderComponent->CheckCollision(tryCollideObject)) {
                    break;
                };
                //std::cout << "test collide between: " << pair.first << " and " << tryCollide.first << std::endl;
                testedPairs.push_back(objectPair);
            }
        }
        // * COLLIDE PART

        // Update after test collide
        gameObject->Update(renderer, m_pCamera);
    }


    renderer->Postcommandlist();

    ID3D12CommandList* ppCommandLists[] = { renderer->m_pCommandList.Get() };
    renderer->m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    hr = renderer->m_pSwapChain->Present(1, 0);
    renderer->m_frameIndex = (renderer->m_frameIndex + 1) % renderer->m_FRAME_COUNT;
    ASSERT_FAILED(hr);

    renderer->WaitForPreviousFrame();


    for (auto& pair : objectMap) {
        GameObject* gameObject = pair.second;
        ColliderComponent* colliderComponent = gameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);
        colliderComponent->m_collideState = 0;
        colliderComponent->m_colliderObject = nullptr;
    }

    for (auto& pair : objectMap) {
        PRINT("Name");
        PRINT(pair.first);
    }

    //for (auto it = objectMap.begin(); it != objectMap.end();) {
    //    GameObject* gameObject = it->second;
    //    if (!gameObject->m_needRender) {
    //        objectMap.erase(0);
    //        /*PRINT("Removing dead object: " << it->first);
    //        delete gameObject;
    //        it = objectMap.erase(it); */

    //    }
    //    else {
    //        ++it;
    //    }
    //}


};