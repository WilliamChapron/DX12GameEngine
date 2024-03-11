#pragma once

#include <vector>
#include <iostream>

class Renderer;
class GameObject;
class StateMachine;

class Script {
public:
    virtual void Initialize(GameObject* gameObject) = 0;
    virtual void Update(Renderer* renderer) = 0;
    virtual ~Script() = default;
private:
    std::string m_name;
};


class ScriptComponent : public Component {
public:
    ScriptComponent(std::string name);

    //void Initialize(GameObject* gameObject);

    //void Update(Renderer* renderer) override;

    void LinkOneScriptToStateMachine();

    inline void RemoveScript(Script* script) {
        auto it = std::find(m_pScripts.begin(), m_pScripts.end(), script);
        if (it != m_pScripts.end()) {
            m_pScripts.erase(it);
            delete script;
        }
    }

    inline void AddScript(Script* script) {
        m_pScripts.push_back(script);
    }


    void GetScriptByName() {

    }

    //void UpdateStateMachine();

private:
    GameObject* m_pGameObject;
    StateMachine* m_pStateMachine;

    std::vector<Script*> m_pScripts;
};

