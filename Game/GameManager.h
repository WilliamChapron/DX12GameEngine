#pragma once

#include "stdafx.h"


//class Input;


class GameManager {
public:
    GameManager();

    void Initialize();
    void Update();

    std::shared_ptr<GameObjectManager> m_pGameObjectManager;


private:
    HINSTANCE m_hInstance;
    int m_nShowCmd;
    FILE* m_pConsole;

    CubeMesh* m_pTriangle;
    CubeMesh* m_pTriangle2;


    Input* m_pInput;
    Camera* m_pCamera;

    ComponentManager* m_pComponentManager;
};

class CubeMesh : public GameObject {
public: 
    CubeMesh(); //Builder
    ~CubeMesh(); //Destroyer
    void Initialize(Renderer* renderer, Camera* camera, ComponentManager* componentManager, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale);


};


