#pragma once

#include "stdafx.h"

class Renderer;
class GameObject;
class Window;

class GameObjectManager;
class ComponentManager;
class ResourceManager;

class Camera;
class TextureComponent;
class Input;
class StateMachine;

class GameManager {
public:
    GameManager();

    void Init(HINSTANCE hInstance, int nShowCmd);
    void Cleanup();

    void Run();

    static GameManager& GetInstance() {
        static GameManager instance;
        //instance.m_isRenderable = false;
        return instance;
    }


    Renderer* m_pRenderer;


    std::shared_ptr<GameObjectManager> m_pGameObjectManager;
    ComponentManager* m_pComponentManager;
    ResourceManager* m_pResourceManager;


    Camera* m_pCamera;
    GameObject* m_playerObject;
    Input* m_pInput;

    GameObject* additionalPlanet1;

    //std::vector<TextureComponent*> compiledTexture;

    inline void SetEngineRenderable(bool isRenderable) {
        m_isRenderable = isRenderable;
    }

    inline bool GetIsRenderable() {
        return m_isRenderable;
    }

    bool m_isRenderable;

private:
    ConstantBufferData* cbData;
    StateMachine* stateMachine;

    Window* m_pWindow = nullptr;
    HINSTANCE m_hInstance;
    int m_nShowCmd;
    FILE* m_pConsole;
};
