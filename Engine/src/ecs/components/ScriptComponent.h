#pragma once

//#include <vector>
//#include <iostream>

#include "../entities/GameObject.hpp"

class Renderer;
class GameObject;
class Transform;

class Script {
public:

    virtual void Initialize(std::string name, GameObject* gameObject) = 0;
    virtual void Update() = 0;

    inline std::string GetName() {
        return m_name;
    }
protected:
    std::string m_name;
    StateMachine* m_pStateMachine;
    GameObject* m_pGameObject;
};



class ScriptComponent : public Component {
public:
    ScriptComponent(std::string name, GameObject* gameObject);

    void Update(Renderer* renderer) override;

    void RemoveScript(Script* script);

    void AddScript(Script* script);

    Script* GetScriptByName(const std::string& scriptName);


private:
    GameObject* m_pGameObject;
    std::vector<Script*> m_pScripts;
};
