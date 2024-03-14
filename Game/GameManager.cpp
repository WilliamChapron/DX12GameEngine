#include "stdafx.h"
#include "GameManager.h"
#include "Scripts.h"

GameManager::GameManager() /*: m_hInstance(nullptr), m_nShowCmd(0), m_pConsole(nullptr), m_pInput(nullptr), m_pCamera(nullptr), m_pGameObjectManager(nullptr) */
{

}

void GameManager::Init(HINSTANCE hInstance, int nShowCmd) {

    SphereMesh cubeMesh; // Common Mesh
    Skydome cubeMesh2; // Common Mesh
    CubeMeshInvisible invisibleMesh;

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
    m_pCamera->Initialize(XMFLOAT3(0.0f, 0.0f, -10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.f, 1.f, 1.f));
    m_pComponentManager->AddCamera(m_pCamera);


    m_pGameObjectManager = std::make_shared<GameObjectManager>(m_pCamera);

    // INITIALIZE UNIQUE COMPONENT

    ConstantBufferData* cbData = new ConstantBufferData(); 
    XMStoreFloat4x4(&cbData->model, XMMatrixIdentity()); ;
    cbData->view = m_pCamera->GetViewMatrix();
    cbData->projection = m_pCamera->GetProjectionMatrix();

    TextureComponent* texture = new TextureComponent("texture");
    TextureComponent* texture2 = new TextureComponent("texture2");

    Mesh* baseMesh = new Mesh("mesh1");
    Mesh* baseMesh2 = new Mesh("mesh2");
    Mesh* baseInvisibleMesh = new Mesh("invisibleMesh");


    ShaderComponent* baseShader = new ShaderComponent("shader1", m_pRenderer);

    m_pResourceManager->AddTextureToResources(texture);
    m_pResourceManager->AddTextureToResources(texture2);

    m_pResourceManager->AddMeshToResources(baseMesh);
    m_pResourceManager->AddMeshToResources(baseMesh2);
    m_pResourceManager->AddMeshToResources(baseInvisibleMesh);


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


    skyBox->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(40.0f, 40.0f, 40.0f), m_pResourceManager->FindMeshComponentByName("mesh2").component, cbData, false);
    earthPlanet->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, true);
    

    m_pComponentManager->AddComponent(*earthPlanet, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*skyBox, m_pResourceManager->FindTextureComponentByName("texture2").component);

    m_pComponentManager->AddComponent(*earthPlanet, m_pResourceManager->FindShaderComponentByName("shader1").component);
    m_pComponentManager->AddComponent(*skyBox, m_pResourceManager->FindShaderComponentByName("shader1").component);

    m_pGameObjectManager->AddObject("EarthPlanet", earthPlanet);

    ParticleComponent* particleComponent = new ParticleComponent("ParticleComponent", m_pRenderer);
    particleComponent->Initialize(m_pCamera, m_pComponentManager, m_pResourceManager, m_pGameObjectManager, earthPlanet);
    m_pComponentManager->AddComponent(*earthPlanet, particleComponent);



    m_pGameObjectManager->AddObject("SkyBox", skyBox);





    // Add an object camera to allow collision
    m_playerObject = new GameObject(m_pComponentManager, "Player");
    m_playerObject->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("invisibleMesh").component, cbData,  true);
    m_pComponentManager->AddComponent(*m_playerObject, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*m_playerObject, m_pResourceManager->FindShaderComponentByName("shader1").component);
    //m_pGameObjectManager->AddObject("Player", m_playerObject);

    GameObject* additionalPlanet2 = new GameObject(m_pComponentManager, "AdditionalPlanet2");
    additionalPlanet2->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, true);
    m_pComponentManager->AddComponent(*additionalPlanet2, m_pResourceManager->FindTextureComponentByName("texture2").component);
    m_pComponentManager->AddComponent(*additionalPlanet2, m_pResourceManager->FindShaderComponentByName("shader1").component);
    //m_pGameObjectManager->AddObject("AdditionalPlanet2", additionalPlanet2);

    additionalPlanet1 = new GameObject(m_pComponentManager, "AdditionalPlanet1");
    additionalPlanet1->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(1.0f, 0.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbData, true);
    m_pComponentManager->AddComponent(*additionalPlanet1, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*additionalPlanet1, m_pResourceManager->FindShaderComponentByName("shader1").component);
    //m_pGameObjectManager->AddObject("AdditionalPlanet1", additionalPlanet1);





    ScriptComponent* scriptComponentEarthPlanet = earthPlanet->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
    ScriptComponent* scriptComponentPlayerObject = m_playerObject->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);

    ScriptComponent* scriptComponentAddPlanet1 = additionalPlanet1->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
    ScriptComponent* scriptComponentAddPlanet2 = additionalPlanet2->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);

     //Utilisation de scriptComponentEarthPlanet au lieu de scriptComponent
    //ZigzagMoveScript* movableScriptEarthPlanet = new ZigzagMoveScript();
    //movableScriptEarthPlanet->Initialize("ZigZagScript", earthPlanet);
    //scriptComponentEarthPlanet->AddScript(movableScriptEarthPlanet);

    LifeScript* lifeScriptEarthPlanet = new LifeScript(m_pGameObjectManager);
    lifeScriptEarthPlanet->Initialize("EarthPlanetScriptLife", earthPlanet);
    scriptComponentEarthPlanet->AddScript(lifeScriptEarthPlanet);

    LifeScript* lifeScriptPlayerObject = new LifeScript(m_pGameObjectManager);
    lifeScriptPlayerObject->Initialize("PlayerObjectScriptLife", m_playerObject);
    scriptComponentPlayerObject->AddScript(lifeScriptPlayerObject);

    LifeScript* lifeScriptAddPlanet1 = new LifeScript(m_pGameObjectManager);
    lifeScriptAddPlanet1->Initialize("AddPlanet1ScriptLife", additionalPlanet1);
    scriptComponentAddPlanet1->AddScript(lifeScriptAddPlanet1);

    LifeScript* lifeScriptAddPlanet2 = new LifeScript(m_pGameObjectManager);
    lifeScriptAddPlanet2->Initialize("AddPlanet2ScriptLife", additionalPlanet2);
    scriptComponentAddPlanet2->AddScript(lifeScriptAddPlanet2);




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

    std::vector<GameObject> projectiles;


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
            case 'T':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    additionalPlanet1->GetComponent<Transform>(ComponentType::Transform)->Translate(0.01f, 0.0f, 0.0f);
                break;
            case 'R':
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    additionalPlanet1->GetComponent<Transform>(ComponentType::Transform)->Rotate(0.01f, 0.01f, 0.01f);
                break;
            case VK_SPACE:
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, speed * time.GetDeltaTime(), 0.0f);
                break;
            case VK_LBUTTON:
                if (pair.second == KeyState::Pressed) {
                    

                    XMFLOAT3 direction = m_pCamera->GetDirection();
                    
                    ConstantBufferData* cbDataBall = new ConstantBufferData();
                    XMStoreFloat4x4(&cbDataBall->model, XMMatrixIdentity()); ;
                    cbDataBall->view = m_pCamera->GetViewMatrix();
                    cbDataBall->projection = m_pCamera->GetProjectionMatrix();


                    GameObject* ball = new GameObject(m_pComponentManager, "ball");
                    XMFLOAT3 ballPosition = m_playerObject->GetComponent<Transform>(ComponentType::Transform)->GetPosition();
                    ball->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(ballPosition.x, ballPosition.y - 0.25f, ballPosition.z + 0.25f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.1f, 0.1f, 0.1f), m_pResourceManager->FindMeshComponentByName("mesh1").component, cbDataBall, true);

                    m_pComponentManager->AddComponent(*ball, m_pResourceManager->FindTextureComponentByName("texture2").component);
                    m_pComponentManager->AddComponent(*ball, m_pResourceManager->FindShaderComponentByName("shader1").component);
                      
                    m_pGameObjectManager->AddObject("Ball", ball);

                    MovableScript* moveScriptBall = new MovableScript(direction);
                    moveScriptBall->Initialize("BallMovableScript", ball);
                    LifeScript* lifeScriptBall = new LifeScript(m_pGameObjectManager);
                    lifeScriptBall->Initialize("ProjectileScriptLife", ball);
                    LifeTimeScript* lifeTimeScript = new LifeTimeScript(time, m_pGameObjectManager);
                    lifeTimeScript->Initialize("LifeTimeScript", ball);

                    ScriptComponent* scriptComponentBall = ball->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
                    scriptComponentBall->AddScript(moveScriptBall);
                    scriptComponentBall->AddScript(lifeScriptBall);
                    scriptComponentBall->AddScript(lifeTimeScript);
                }       
                break;
            case VK_SHIFT:
                if (pair.second == KeyState::Pressed || pair.second == KeyState::Held)
                    m_pCamera->UpdatePosition(0.0f, -speed * time.GetDeltaTime(), 0.0f);
                break;
            }
        }
        XMFLOAT2 cameraVect;

        XMFLOAT3 direction = m_pCamera->GetDirection();

        cameraVect = XMFLOAT2(m_pInput->GetMousePosition().x, -m_pInput->GetMousePosition().y);

        m_pCamera->Rotate(cameraVect.x, -cameraVect.y);

        m_pInput->ResetMousePosition();


        // #TODO replace by player
        XMFLOAT3 cameraPosition = m_pCamera->GetPosition();
        m_playerObject->GetComponent<Transform>(ComponentType::Transform)->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);


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