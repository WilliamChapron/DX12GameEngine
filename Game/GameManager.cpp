#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager() : m_hInstance(nullptr), m_nShowCmd(0), m_pConsole(nullptr), m_pInput(nullptr), m_pCamera(nullptr), m_pGameObjectManager(nullptr) {}

void GameManager::Initialize() {

    ////m_hInstance = hInstance;
    ////m_nShowCmd = nShowCmd;

    //m_pInput = new Input();
    //m_pCamera = new Camera(); // #TODO Shared ptr camera to each object



    //m_pGameObjectManager = std::make_shared<GameObjectManager>(m_pCamera);
    //m_pComponentManager = new ComponentManager(m_pGameObjectManager, m_pRenderer);


    //// Create Objects
    //m_pTriangle = new CubeMesh;
    //m_pTriangle2 = new CubeMesh;

    //m_pTriangle->Initialize(m_pRenderer, m_pCamera, m_pComponentManager, XMFLOAT3(0.5f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
    ////m_pTriangle2->Initialize(m_pRenderer, m_pCamera, m_pComponentManager, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));



    ////m_pTriangle3 = new Triangle;
    ////m_pTriangle3->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.7f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));

    ////m_pGameObjectManager->AddObject("Triangle", m_pTriangle);
    //m_pGameObjectManager->AddObject("Triangle2", m_pTriangle2);

    //// Add component after object

    ////m_pComponentManager->AddComponent(m_pTriangle2, compiledTexture[0]);
    ////m_pGameObjectManager->AddObject("Triangle3", *m_pTriangle3);
    


}

void GameManager::Update() {
    //// Mettez à jour ici les membres de GameManager
    //// Par exemple:
    //m_pInput->Update(); // Mettez à jour l'Input
    //m_pGameObjectManager->Update(m_pRenderer); // Mettez à jour le GameObjectManager
}