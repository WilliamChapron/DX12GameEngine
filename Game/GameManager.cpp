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

    m_pComponentManager = new ComponentManager(m_pGameObjectManager, m_pRenderer);
    m_pResourceManager = new ResourceManager();

    m_pCamera = new Camera(m_pComponentManager); // #TODO Shared ptr camera to each object
    //m_pCamera->Initialize(XMFLOAT3(0.0f, -5.0f, -2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.f, 1.f, 1.f));
    m_pCamera->Initialize(XMFLOAT3(0.0f, 0.0f, -10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.f, 1.f, 1.f));
    m_pCamera->UpdateTransform();
    m_pComponentManager->AddCamera(m_pCamera);


    m_pGameObjectManager = std::make_shared<GameObjectManager>(m_pCamera);

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



    GameObject* skyBox = new GameObject(m_pComponentManager, "SkyBox");
    GameObject* earthPlanet = new GameObject(m_pComponentManager, "EarthPlanet");


    skyBox->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(40.0f, 40.0f, 40.0f), m_pResourceManager->FindMeshComponentByName("mesh2").component, cbData, cubeMesh2.cubeVertices, cubeMesh2.numElementsV, false);
    earthPlanet->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, cubeMesh.cubeVertices, cubeMesh.numElementsV, true);
    

    m_pComponentManager->AddComponent(*earthPlanet, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*skyBox, m_pResourceManager->FindTextureComponentByName("texture2").component);

    m_pComponentManager->AddComponent(*earthPlanet, m_pResourceManager->FindShaderComponentByName("shader1").component);
    m_pComponentManager->AddComponent(*skyBox, m_pResourceManager->FindShaderComponentByName("shader1").component);

    m_pGameObjectManager->AddObject("SkyBox", skyBox);
    m_pGameObjectManager->AddObject("EarthPlanet", earthPlanet);


    // Add an object camera to allow collision
    GameObject* cameraObject = new GameObject(m_pComponentManager, "Camera");
    cameraObject->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(10.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, cubeMesh.cubeVertices, cubeMesh.numElementsV, true);
    m_pComponentManager->AddComponent(*cameraObject, m_pResourceManager->FindShaderComponentByName("shader1").component);
    m_pGameObjectManager->AddObject("Camera", cameraObject);

    //GameObject* additionalPlanet1 = new GameObject(m_pComponentManager, "AdditionalPlanet1");
    //additionalPlanet1->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(10.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, cubeMesh.cubeVertices, cubeMesh.numElementsV, true);
    //m_pComponentManager->AddComponent(*additionalPlanet1, m_pResourceManager->FindTextureComponentByName("texture").component);
    //m_pComponentManager->AddComponent(*additionalPlanet1, m_pResourceManager->FindShaderComponentByName("shader1").component);
    //m_pGameObjectManager->AddObject("AdditionalPlanet1", additionalPlanet1);

    //GameObject* additionalPlanet2 = new GameObject(m_pComponentManager, "AdditionalPlanet2");
    //additionalPlanet2->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(20.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.7f, 0.7f, 0.7f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, cubeMesh.cubeVertices, cubeMesh.numElementsV, true);
    //m_pComponentManager->AddComponent(*additionalPlanet2, m_pResourceManager->FindTextureComponentByName("texture").component);
    //m_pComponentManager->AddComponent(*additionalPlanet2, m_pResourceManager->FindShaderComponentByName("shader1").component);
    //m_pGameObjectManager->AddObject("AdditionalPlanet2", additionalPlanet2);


    ScriptComponent* scriptComponent = earthPlanet->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
    ScriptComponent* scriptComponent2 = skyBox->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);

    ZigzagMoveScript* movableScript = new ZigzagMoveScript();
    movableScript->Initialize("ZigZagScript", earthPlanet);
    scriptComponent->AddScript(movableScript);

    LifeScript* lifeScript = new LifeScript("LifeScript1", earthPlanet, m_pGameObjectManager);
    scriptComponent->AddScript(lifeScript);

    // #TODO le problème d'erase venait peut etre du fait que les objets sont toujorus dispo dans game manager.h

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

    //Cubes.push_back(*m_pCube1);
    //Cubes.push_back(*m_pCube2);
    // Ajoutez d'autres Cubes au besoin



    while (true) {

        //Transform* transformComponent = m_pCube->GetComponent<Transform>(ComponentType::Transform);


        time.UpdateTime();

        m_pCamera->Update(time.GetDeltaTime());

        m_pWindow->UpdateTitleWithFPS(time.GetFramePerSecond());

        m_pInput->Update();

        //------ Camera Movement
        for (const auto& pair : m_pInput->GetKeyStates()) {
            switch (pair.first) {
            case 'Z':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, 0.0f, speed * time.GetDeltaTime());
                break;
            case 'S':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, 0.0f, -speed * time.GetDeltaTime());
                break;
            case 'Q':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(-speed * time.GetDeltaTime(), 0.0f, 0.0f);
                break;
            case 'D':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(speed * time.GetDeltaTime(), 0.0f, 0.0f);
                break;
            case VK_SPACE:
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, speed * time.GetDeltaTime(), 0.0f);
                break;
            case VK_SHIFT:
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, -speed * time.GetDeltaTime(), 0.0f);
                break;
            }
        }
        XMFLOAT2 cameraVect;

        /*if (m_pInput->GetMousePosition().x != 0 || m_pInput->GetMousePosition().y)
            cameraVect = NormalizeVector(XMFLOAT2(m_pInput->GetMousePosition().x, -m_pInput->GetMousePosition().y));
        else*/
        cameraVect = XMFLOAT2(m_pInput->GetMousePosition().x, -m_pInput->GetMousePosition().y);

        m_pCamera->Rotate(cameraVect.x, -cameraVect.y);

        m_pInput->ResetMousePosition();


        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        m_pGameObjectManager->Update(m_pRenderer);
    }
}

void GameManager::Cleanup() {
    if (m_pConsole) {
        fclose(m_pConsole);
        FreeConsole();
    }
}