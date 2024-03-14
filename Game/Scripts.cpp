#include "stdafx.h"
#include "Scripts.h"

MovableScript::MovableScript(XMFLOAT3 direction) {
    m_direction = direction;
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
    PRINT("Update Movable Script");
    m_pStateMachine->Update();
}

ZigzagMoveScript::ZigzagMoveScript() {

}

void ZigzagMoveScript::Initialize(std::string name, GameObject* gameObject) {
    m_name = name;
    m_pGameObject = gameObject;
    m_zigzagSpeed = 0.01f;
    m_zigzagAmplitude = 1.2f;
    m_goingRight = true;
    m_currentAmplitude = 0.0f;
    m_currentTime = 0.0f;
    m_curvature = 0.1f; // Ajout du paramètre de courbure
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



    transformComponent->Translate(xOffset, 0.0f, -0.01f);


    transformComponent->Rotate(0.0f, 0.01, 0.0f);

    //PRINT("Current Amplitude");
    //PRINT(m_currentAmplitude);
    //PRINT("Curvature");
    //PRINT(curvature);
    //PRINT("X Offset");
    //PRINT(xOffset);

    // Inverser la direction du zigzag si nécessaire
    if (abs(m_currentAmplitude) >= m_zigzagAmplitude) {
        m_currentAmplitude = 0.0f;
        m_goingRight = !m_goingRight;
    }
}

LifeScript::LifeScript(std::string name, GameObject* gameObject, std::shared_ptr<GameObjectManager> gameObjectManager) {
    m_name = name;
    m_pGameObject = gameObject;
    m_pGameObjectManager = gameObjectManager;
    m_health = 100;
}

void LifeScript::Initialize(std::string name, GameObject* gameObject) {

}

void LifeScript::Update() {
    ColliderComponent* colliderComponent = m_pGameObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);


    if (colliderComponent->m_collideState) {
        std::cout << "DAMAGE" << std::endl;
        std::cout << m_name << std::endl;


        m_pGameObjectManager->RemoveObject(m_pGameObject);
    }
}




