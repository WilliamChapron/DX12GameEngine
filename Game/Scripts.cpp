#include "stdafx.h"
#include "Scripts.h"


MovableScript::MovableScript(XMFLOAT3 direction, float speed) {
    m_direction = direction;
    m_speed = speed;
}

void MovableScript::Initialize(std::string name, GameObject* gameObject) {
    m_pGameObject = gameObject;
    m_pStateMachine = new StateMachine();

    m_pStateMachine->SetState("Idle", 0);
    m_pStateMachine->SetState("Moving", 1);
    m_pStateMachine->SetStateEvent(0, [this]() { IdleMove(); });
    m_pStateMachine->SetStateEvent(1, [this]() { NormalMove(); });

    m_pStateMachine->ChangeState("Moving");
}

void MovableScript::Update() {
    time.UpdateTime();
    m_pStateMachine->Update();
}

ZigzagMoveScript::ZigzagMoveScript() {

}

void ZigzagMoveScript::Initialize(std::string name, GameObject* gameObject) {
    m_name = name;
    m_pGameObject = gameObject;
    m_zigzagSpeed = 0.01f;
    m_zigzagAmplitude = 3.0f;
    m_goingRight = true;
    m_currentAmplitude = 0.0f;
    m_currentTime = 0.0f;
    m_curvature = 0.1f; 
}

void ZigzagMoveScript::Update() {
    Transform* transformComponent = m_pGameObject->GetComponent<Transform>(ComponentType::Transform);

    if (m_goingRight) {
        m_currentAmplitude += m_zigzagSpeed;
    }
    else {
        m_currentAmplitude -= m_zigzagSpeed;
    }

    float curvature = m_curvature * m_currentTime * 0.1f; 
    float xOffset = m_currentAmplitude * curvature;

    m_currentTime += m_zigzagSpeed;



    transformComponent->Translate(xOffset, 0.0f, -0.001f);
    transformComponent->Rotate(0.0f, 0.01, 0.0f);

    if (abs(m_currentAmplitude) >= m_zigzagAmplitude) {
        m_currentAmplitude = 0.0f;
        m_goingRight = !m_goingRight;
    }
}

LifeScript::LifeScript(std::shared_ptr<GameObjectManager> gameObjectManager) {
    m_pGameObjectManager = gameObjectManager;
    m_health = 100;
}

void LifeScript::Initialize(std::string name, GameObject* gameObject) {
    m_name = name;
    m_pGameObject = gameObject;

}

void LifeScript::Update() {
    ColliderComponent* colliderComponent = m_pGameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);


    if (colliderComponent->m_collideState) {
        std::cout << m_name << std::endl;


        m_pGameObjectManager->RemoveObject(m_pGameObject);
    }
}

LifeTimeScript::LifeTimeScript(Time _time, std::shared_ptr<GameObjectManager> goManager, double _lifeTimeMax)
{
    lifeTime = 0.0f;
    lifeTimeMax = _lifeTimeMax;
    pGameObjectManager = goManager;
    time = _time;
}

void LifeTimeScript::Initialize(std::string name, GameObject* gameObject)
{
    m_name = name;
    m_pGameObject = gameObject;
}

void LifeTimeScript::Update()
{
    lifeTime += time.GetDeltaTime();
    if (lifeTime >= lifeTimeMax)
        pGameObjectManager->RemoveObject(m_pGameObject);
}

ObstacleGenerationScript::ObstacleGenerationScript(Time _time, std::shared_ptr<GameObjectManager> goManager, ComponentManager* componentManager, Renderer* renderer, Camera* camera, Mesh* mesh, ConstantBufferData* cbData, ResourceManager* rManager)
{
    time = _time;
    pGameObjectManager = goManager;
    pComponentManager = componentManager;
    pRenderer = renderer;
    pCamera = camera;
    pMesh = mesh;
    pCbData = cbData;
    m_pResourceManager = rManager;
}

void ObstacleGenerationScript::Initialize(std::string name, GameObject* gameObject)
{
    m_name = name;
    m_pGameObject = gameObject;
    delayOfSpawn = static_cast<float>(GetRandomNum(1, 3));
}

void ObstacleGenerationScript::Update()
{
    time.UpdateTime();
    if (delayOfSpawn <= 0)
    {
        GameObject* obstacle = new GameObject(pComponentManager, "obstacle1");
        float x = static_cast<float>(GetRandomNum(-30, 32));
        if (x < 10 && x > -10)
            x += 20.f;
        float y = static_cast<float>(GetRandomNum(-25, 31));
        if (y < 10 && y > -10)
            y += 20.f;
        float z = static_cast<float>(GetRandomNum(-32, 28));
        if (z < 10 && z > -10)
            z += 20.f;

        int scale = GetRandomNum(10, 100);
        float _scale = scale / 50;
        obstacle->Initialize(pRenderer, pCamera, XMFLOAT3(x, y, z), XMFLOAT3(0.f, 0.f, 0.f), XMFLOAT3(_scale, _scale, _scale), pMesh, pCbData, true);
           
        pGameObjectManager->AddObject("obstacle", obstacle);

        pComponentManager->AddComponent(*obstacle, m_pResourceManager->FindTextureComponentByName("texture3").component);
        pComponentManager->AddComponent(*obstacle, m_pResourceManager->FindShaderComponentByName("shader1").component);

        ScriptComponent* scriptComponent= obstacle->GetComponent<ScriptComponent>(ComponentType::ScriptComponent);
        ZigzagMoveScript* move = new ZigzagMoveScript();
        move->Initialize("move", obstacle);
        scriptComponent->AddScript(move);
        LifeScript* life = new LifeScript(pGameObjectManager);
        life->Initialize("life", obstacle);
        scriptComponent->AddScript(life);
        LifeTimeScript* lifetime = new LifeTimeScript(time, pGameObjectManager, 15.f);
        lifetime->Initialize("lifetime", obstacle);
        scriptComponent->AddScript(lifetime);

        
        Transform* transform = obstacle->GetComponent<Transform>(ComponentType::Transform);
        XMFLOAT3 dir = XMFLOAT3(pCamera->GetPosition().x - transform->GetPosition().x, pCamera->GetPosition().y - transform->GetPosition().y, pCamera->GetPosition().z - transform->GetPosition().z);
        
        float length = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        
        if (length != 0.0f) {
            dir.x /= length * 0.5f;
            dir.y /= length * 0.5f;
            dir.z /= length * 0.5f;
        } else dir = XMFLOAT3(0.0f, 0.0f, 0.0f); 

        MovableScript* movement = new MovableScript(dir, 2.f);
        movement->Initialize("movement", obstacle);
        scriptComponent->AddScript(movement);


        delayOfSpawn = GetRandomNum(1, 2);

    }
    delayOfSpawn -= time.GetDeltaTime();
}
