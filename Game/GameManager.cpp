#include "stdafx.h"
#include "GameManager.h"
#include "Scripts.h"

GameManager::GameManager() /*: m_hInstance(nullptr), m_nShowCmd(0), m_pConsole(nullptr), m_pInput(nullptr), m_pCamera(nullptr), m_pGameObjectManager(nullptr) */
{

}

void GameManager::Init(HINSTANCE hInstance, int nShowCmd) {

    SphereMesh cubeMesh; // Common Mesh
    Skydome cubeMesh2; // Common Mesh

    m_hInstance = hInstance;

    AllocConsole();

    if (freopen_s(&m_pConsole, "CONOUT$", "w", stdout) != 0) {
        MessageBox(0, L"Failed to redirect console output", L"Error", MB_OK);
        Cleanup();
        PostQuitMessage(1);
    }

    m_pWindow = new Window(hInstance, nShowCmd);
    m_pRenderer = new Renderer(m_pWindow);
    m_pRenderer->InitializeDirectX12Instances();
    m_pRenderer->m_pCommandList->Close();

    m_pInput = new Input(m_pWindow->getWndProps());
    m_pInput->ResetMousePosition();


    m_pCamera = new Camera(); // #TODO Shared ptr camera to each object

    m_pGameObjectManager = std::make_shared<GameObjectManager>(m_pCamera);
    m_pComponentManager = new ComponentManager(m_pGameObjectManager, m_pRenderer, m_pCamera);
    m_pResourceManager = new ResourceManager();

    // INITIALIZE UNIQUE COMPONENT

    ConstantBufferData* cbData = new ConstantBufferData(); // Alloue de la mémoire pour m_cbData
    XMStoreFloat4x4(&cbData->model, XMMatrixIdentity()); ;
    cbData->view = m_pCamera->GetViewMatrix();
    cbData->projection = m_pCamera->GetProjectionMatrix();

    TextureComponent* texture = new TextureComponent("texture");
    TextureComponent* texture2 = new TextureComponent("texture2");

    Mesh* baseMesh = new Mesh("mesh1");
    Mesh* baseMesh2 = new Mesh("mesh2");

    ShaderComponent* baseShader = new ShaderComponent("shader1", m_pRenderer);

    m_pResourceManager->AddTextureToResources(texture);
    m_pResourceManager->AddTextureToResources(texture2);
    m_pResourceManager->AddMeshToResources(baseMesh);
    m_pResourceManager->AddMeshToResources(baseMesh2);

    m_pResourceManager->AddShaderToResources(baseShader);




    // Any order
    baseMesh->Initialize(cbData, m_pRenderer, cubeMesh.cubeVertices, cubeMesh.numElementsV, cubeMesh.cubeIndices, cubeMesh.numElementsI);
    baseMesh2->Initialize(cbData, m_pRenderer, cubeMesh2.cubeVertices, cubeMesh2.numElementsV, cubeMesh2.cubeIndices, cubeMesh2.numElementsI);

    texture->Initialize(m_pRenderer, m_pResourceManager->FindTextureComponentByName("texture").key);
    texture2->Initialize(m_pRenderer, m_pResourceManager->FindTextureComponentByName("texture2").key);

    baseShader->InitializeRootSignature();
    baseShader->InitializePSO();


    // #TODO CREATE FONCTION | CREATE OBJECT | CREATE TEXTURE | CREATE MESH | CREATE SHADER
    m_pCube = new GameObject(m_pComponentManager, "Cube1");
    m_pCube2 = new GameObject(m_pComponentManager, "Cube2");
    m_pCube3 = new GameObject(m_pComponentManager, "Cube3");
    m_pCube4 = new GameObject(m_pComponentManager, "Cube4");



    m_pCube->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(-1.5f, 100.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, cubeMesh.cubeVertices, cubeMesh.numElementsV);
    m_pCube2->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("mesh2").component, cbData, cubeMesh2.cubeVertices, cubeMesh2.numElementsV);
    m_pCube3->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(1.5f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, cubeMesh.cubeVertices, cubeMesh.numElementsV);
    m_pCube4->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(3.5f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(10.0f, 10.0f, 10.0f), m_pResourceManager->FindMeshComponentByName("mesh2").component, cbData, cubeMesh2.cubeVertices, cubeMesh2.numElementsV);

    m_pComponentManager->AddComponent(*m_pCube, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*m_pCube2, m_pResourceManager->FindTextureComponentByName("texture2").component);
    m_pComponentManager->AddComponent(*m_pCube3, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*m_pCube4, m_pResourceManager->FindTextureComponentByName("texture2").component);

    m_pComponentManager->AddComponent(*m_pCube, m_pResourceManager->FindShaderComponentByName("shader1").component);
    m_pComponentManager->AddComponent(*m_pCube2, m_pResourceManager->FindShaderComponentByName("shader1").component);
    m_pComponentManager->AddComponent(*m_pCube3, m_pResourceManager->FindShaderComponentByName("shader1").component);
    m_pComponentManager->AddComponent(*m_pCube4, m_pResourceManager->FindShaderComponentByName("shader1").component);

    m_pGameObjectManager->AddObject("Cube", m_pCube);
    m_pGameObjectManager->AddObject("Cube2", m_pCube2);
    m_pGameObjectManager->AddObject("Cube3", m_pCube3);
    m_pGameObjectManager->AddObject("Cube4", m_pCube4);

    ScriptComponent* scriptComponent = m_pCube->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
    ScriptComponent* scriptComponent2 = m_pCube2->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
    ScriptComponent* scriptComponent3 = m_pCube3->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
    ScriptComponent* scriptComponent4 = m_pCube4->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);

    ZigzagMoveScript* movableScript = new ZigzagMoveScript();
    movableScript->Initialize("ZigZagScript", m_pCube);
    scriptComponent->AddScript(movableScript);

    LifeScript* lifeScript = new LifeScript("LifeScript1", m_pCube, m_pGameObjectManager);
    scriptComponent->AddScript(lifeScript);

    LifeScript* lifeScript2 = new LifeScript("LifeScript2", m_pCube2, m_pGameObjectManager);
    scriptComponent2->AddScript(lifeScript2);

    LifeScript* lifeScript3 = new LifeScript("LifeScript3", m_pCube3, m_pGameObjectManager);
    scriptComponent->AddScript(lifeScript3);

    LifeScript* lifeScript4 = new LifeScript("LifeScript4", m_pCube4, m_pGameObjectManager);
    scriptComponent2->AddScript(lifeScript4);

    // Drawing
    m_isRenderable = true;
    Run();

}



void GameManager::Run() {
    std::cout << "Main Loop Started" << std::endl;

    Time time;

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));


    std::vector<GameObject> Cubes;

    float speed = 15.f;

    ShowCursor(FALSE);

    m_pCamera->UpdateTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));

    while (true) {

        Transform* transformComponent = m_pCube->GetComponent<Transform>(ComponentType::Transform);
        Transform* transformComponent2 = m_pCube2->GetComponent<Transform>(ComponentType::Transform);


        time.UpdateTime();


        m_pCamera->Update(time.GetDeltaTime());

        m_pWindow->UpdateTitleWithFPS(time.GetFramePerSecond());



        m_pInput->Update();

        //------ Camera Movement
        for (const auto& pair : m_pInput->GetKeyStates()) {
            switch (pair.first) {
            case 'Z':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, speed * time.GetDeltaTime(), 0.0f);
                break;
            case 'S':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, -speed * time.GetDeltaTime(), 0.0f);
                break;
            case 'Q':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(-speed * time.GetDeltaTime(), 0.0f, 0.0f);
                break;
            case 'D':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(speed * time.GetDeltaTime(), 0.0f, 0.0f);
                break;
            case 'R':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held) {
                    std::cout << "dsds" << std::endl;
                    transformComponent->Rotate(0.03, 0.03, 0.03);
                }
                break;
            case 'T':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held) {
                    //DirectX::XMFLOAT3 direction = transformComponent->GetPosition() - m_pCamera->m_position;
                    transformComponent->Translate(0.03, 0.0, 0);
                    transformComponent2->Translate(0.03, 0.0, 0);
                }
                break;
            case VK_SPACE:
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, 0.0f, -speed * time.GetDeltaTime());
                break;
            case VK_SHIFT:
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, 0.0f, speed * time.GetDeltaTime());
                break;
                /*case VK_LBUTTON:
                    if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    {

                    }*/
            }
        }
        m_pCamera->Rotate(m_pInput->GetMousePosition().y * 0.2f, 0.0f, -m_pInput->GetMousePosition().x * 0.2f);

        m_pInput->ResetMousePosition();

        




        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // Appelez la fonction Render de la classe Renderer et passez-lui la liste de Cubes
        m_pGameObjectManager->Update(m_pRenderer);
    }
}



void GameManager::Cleanup() {
    if (m_pConsole) {
        fclose(m_pConsole);
        FreeConsole();
    }
}