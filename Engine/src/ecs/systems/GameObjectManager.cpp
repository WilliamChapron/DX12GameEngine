#include "pch.h"



GameObjectManager::GameObjectManager(Camera* camera) : m_pCamera(camera) {}


void GameObjectManager::AddObject(const std::string& name, GameObject* object) {
    objectMap[name].push_back(object);
    PRINT("Object added: " << name);
}


void GameObjectManager::RemoveObject(GameObject* object) {
    for (auto& pair : objectMap) {
        auto& objectVector = pair.second;
        auto it = std::find(objectVector.begin(), objectVector.end(), object);
        if (it != objectVector.end()) {
            /*PRINT("Removing object: " << pair.first);*/
            (*it)->m_needRender = false;
            objectVector.erase(it);
            return;
        }
    }
    PRINT("Object not found for removal.");
}

void GameObjectManager::Update(Renderer* renderer) {
    HRESULT hr;
    PRINT("Frame");


    renderer->Precommandlist();


    std::vector<TestedPair> testedPairs;

    


    for (auto& pair : objectMap) {
        for (int i = 0; i < pair.second.size(); i++)
        {
            GameObject* gameObject = pair.second[i];
            ColliderComponent* colliderComponent = gameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);

            if (!gameObject->m_needRender) {
                continue;

            }


            // COLLIDE PART *

            // tryCollide = object on which we test collision

            if (gameObject->m_needCollide) {
                for (auto& tryCollide : objectMap) {
                    for (int i = 0; i < tryCollide.second.size(); i++)
                    {
                        GameObject* tryCollideObject = tryCollide.second[i];


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
            }
            // * COLLIDE PART

            // Update after test collide
            gameObject->Update(renderer, m_pCamera);
        }
    }


    renderer->Postcommandlist();

    ID3D12CommandList* ppCommandLists[] = { renderer->m_pCommandList.Get() };
    renderer->m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    hr = renderer->m_pSwapChain->Present(1, 0);
    renderer->m_frameIndex = (renderer->m_frameIndex + 1) % renderer->m_FRAME_COUNT;
    ASSERT_FAILED(hr);

    renderer->WaitForPreviousFrame();


    for (auto& pair : objectMap) {
        for (int i = 0; i < pair.second.size(); i++)
        {
            GameObject* gameObject = pair.second[i];
            if (!gameObject->m_needCollide) {
                continue;
            }
            ColliderComponent* colliderComponent = gameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);
            colliderComponent->m_collideState = 0;
            colliderComponent->m_colliderObject = nullptr;
        }
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