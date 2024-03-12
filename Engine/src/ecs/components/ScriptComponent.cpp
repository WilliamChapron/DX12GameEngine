#include "pch.h"

#include "ScriptComponent.h"
#include "../systems/StateMachine.h"
#include "../entities/GameObject.hpp"

ScriptComponent::ScriptComponent(std::string name, GameObject* gameObject) : Component(name, ComponentType::ScriptComponent)
{
    m_pGameObject = gameObject;
}



void ScriptComponent::Update(Renderer* renderer) {
    PRINT("Update Script Component");
    for (Script* script : m_pScripts) {
        script->Update();
    }
}

void ScriptComponent::RemoveScript(Script* script) {
    auto it = std::find(m_pScripts.begin(), m_pScripts.end(), script);
    if (it != m_pScripts.end()) {
        m_pScripts.erase(it);
        delete script;
    }
}

void ScriptComponent::AddScript(Script* script) {
    m_pScripts.push_back(script);
}

Script* ScriptComponent::GetScriptByName(const std::string& scriptName) {
    for (Script* script : m_pScripts) {
        if (script->GetName() == scriptName) {
            return script;
        }
    }
    return nullptr;
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
    PRINT("Update Movable Script");
    m_pStateMachine->Update();
}


void ZigzagMoveScript::Initialize(std::string name, GameObject* gameObject) {
    m_name = name;
    m_pGameObject = gameObject;
    m_zigzagSpeed = 0.0001f;       
    m_zigzagAmplitude = 0.5f;   
    m_goingRight = true;
    m_currentAmplitude = 0.0f;
}

void ZigzagMoveScript::Update() {
    Transform* transformComponent = m_pGameObject->GetComponent<Transform>(ComponentType::Transform);

    // Mouvement de zigzag
    //float deltaTime = 0.016f;  // Ajustez selon la fréquence de mise à jour
    //m_currentTime += deltaTime;



    //float y;
    if (m_goingRight) {
        m_currentAmplitude += m_zigzagSpeed;
    }
    else {
        m_currentAmplitude -= m_zigzagSpeed;
    }

    //float z = 0.0f;


    transformComponent->Translate(m_currentAmplitude, 0, 0);

    PRINT("Current Amplitude");
    PRINT(m_currentAmplitude);

    // Inverser la direction du zigzag si nécessaire
    //PRINT(transformComponent->GetPosition().y);
    if (abs(m_currentAmplitude) >= m_zigzagAmplitude) {
        PRINT("CHANGEMENT");
        m_currentAmplitude = 0.0f;
        m_goingRight = !m_goingRight;
    }
    //PRINT()

}