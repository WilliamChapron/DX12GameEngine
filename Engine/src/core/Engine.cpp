
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

    
}

void Engine::Cleanup() {
    if (m_pConsole) {
        fclose(m_pConsole);
        FreeConsole();
    }
}

void Engine::Run(std::shared_ptr<GameObjectManager> gameObjectManager, Renderer* renderer) {

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

        ////CAMERA DEBUG
        ////m_pCamera->UpdatePosition(0.0f, 0.0f, 0.2f);
        ////m_pCamera->Rotate(0.0f, 0.0f, 0.25f);
        //m_pCamera->RotateAroundTarget(0.f, .0f, 0.f);
        //m_pCamera->UpdateTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));

        //m_pCamera->Update(time.GetDeltaTime());

        //m_pWindow->UpdateTitleWithFPS(time.GetFramePerSecond());

        ////------ TEST INPUT
        //m_pInput->Update();
        //// Affichez la liste des touches et leur état
        //std::cout << "Touches pressees : " << std::endl;
        //for (const auto& pair : m_pInput->GetKeyStates()) {
        //    std::cout << "Touche : " << pair.first << ", Etat : ";
        //    // Utilisez un switch pour gérer les différents états de la touche
        //    switch (pair.second) {
        //    case KeyState::Pressed:
        //        std::cout << "Pressed";
        //        break;
        //    case KeyState::Held:
        //        std::cout << "Held";
        //        break;
        //    case KeyState::Released:
        //        std::cout << "Released";
        //        break;
        //    case KeyState::Inactive:
        //        std::cout << "Inactive";
        //        break;
        //    }
        //    std::cout << std::endl;
        //}


        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (isRenderable) {
            // Appelez la fonction Render de la classe Renderer et passez-lui la liste de triangles
            gameObjectManager->Update(renderer);
        }
    }
}

void Engine::Update() {
    // static instance

}
