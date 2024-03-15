#include "pch.h"

#include "ScriptComponent.h"
#include "../systems/StateMachine.h"
#include "../entities/GameObject.hpp"

ScriptComponent::ScriptComponent(std::string name, GameObject* gameObject) : Component(name, ComponentType::ScriptComponent)
{
    m_pGameObject = gameObject;
}



void ScriptComponent::Update(Renderer* renderer) {
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


