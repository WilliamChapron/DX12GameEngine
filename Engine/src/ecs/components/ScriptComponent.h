#pragma once

class Renderer;
class GameObject;

class ScriptComponent : public Component
{
public:

    ScriptComponent(std::string name);

    void Initialize(GameObject* gameObject);

    void Update(Renderer* renderer) override;

private:
    GameObject* m_pGameObject;
    StateMachine* m_pStateMachine;

};
