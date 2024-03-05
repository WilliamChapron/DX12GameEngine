
#include "pch.h"

#include "Engine.h"
#include "../ecs/entities/CubeMesh.h"

#include "pch.h"

#include "../renderer/Graphics.h"   
#include "Defines.h"   
#include "Window.h"  

// System
#include "../ecs/systems/GameObjectManager.h"  
#include "../ecs/systems/ComponentManager.h"  



// Component
#include "../ecs/components/Transform.h"
#include "../ecs/components/Texture.h"
#include "../ecs/components/Camera.h"


// Miscellaneous
#include "../ecs/systems/Time.h"
#include "../Utils.h"
#include "../ecs/systems/Input.h"




using namespace DirectX;


void Engine::Init(HINSTANCE hInstance, int nShowCmd) {
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

    m_pInput = new Input();

    m_pCamera = new Camera(); // #TODO Shared ptr camera to each object



    m_pGameObjectManager = std::make_shared<GameObjectManager>(m_pCamera);
    m_pComponentManager = new ComponentManager(m_pGameObjectManager, m_pRenderer);



    //compiledTexture.push_back(new TextureComponent("texture"));
    //compiledTexture[0]->Initialize(m_pRenderer);

    //compiledTexture.push_back(new Texture("texture2"));
    //compiledTexture[1]->Initialize(m_pRenderer);

    //compiledTexture.push_back(new Texture("2"));
    //compiledTexture[1]->Initialize(m_pRenderer);

    // Create Objects
    m_pTriangle = new CubeMesh;
    m_pTriangle2 = new CubeMesh;

    m_pTriangle->Initialize(m_pRenderer, m_pCamera, m_pComponentManager, XMFLOAT3(0.5f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
    m_pTriangle2->Initialize(m_pRenderer, m_pCamera, m_pComponentManager, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));



    //m_pTriangle3 = new Triangle;
    //m_pTriangle3->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.7f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pGameObjectManager->AddObject("Triangle", m_pTriangle);
    m_pGameObjectManager->AddObject("Triangle2", m_pTriangle2);

    // Add component after object

    //m_pComponentManager->AddComponent(m_pTriangle2, compiledTexture[0]);
    //m_pGameObjectManager->AddObject("Triangle3", *m_pTriangle3);



    // Drawing
    isRenderable = true;
    Run();
}

void Engine::Cleanup() {
    if (m_pConsole) {
        fclose(m_pConsole);
        FreeConsole();
    }
}

void Engine::Run() {
    std::cout << "Main Loop Started" << std::endl;
    
    Time time;

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));


    std::vector<GameObject> triangles;


    //triangles.push_back(*m_pTriangle1);
    //triangles.push_back(*m_pTriangle2);
    // Ajoutez d'autres triangles au besoin

    while (true) {

        time.UpdateTime();

        //CAMERA DEBUG
        //m_pCamera->UpdatePosition(0.0f, 0.0f, 0.2f);
        //m_pCamera->Rotate(0.0f, 0.0f, 0.25f);
        m_pCamera->RotateAroundTarget(0.f, .0f, 0.f);
        m_pCamera->UpdateTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));

        m_pCamera->Update(time.GetDeltaTime());

        m_pWindow->UpdateTitleWithFPS(time.GetFramePerSecond());

        //------ TEST INPUT
        m_pInput->Update();
        // Affichez la liste des touches et leur �tat
        std::cout << "Touches pressees : " << std::endl;
        for (const auto& pair : m_pInput->GetKeyStates()) {
            std::cout << "Touche : " << pair.first << ", Etat : ";
            // Utilisez un switch pour g�rer les diff�rents �tats de la touche
            switch (pair.second) {
            case KeyState::Pressed:
                std::cout << "Pressed";
                break;
            case KeyState::Held:
                std::cout << "Held";
                break;
            case KeyState::Released:
                std::cout << "Released";
                break;
            case KeyState::Inactive:
                std::cout << "Inactive";
                break;
            }
            std::cout << std::endl;
        }


        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (isRenderable) {
            // Appelez la fonction Render de la classe Renderer et passez-lui la liste de triangles
            m_pGameObjectManager->Update(m_pRenderer);
        }
    }
}

void Engine::Update() {
    // static instance

}
