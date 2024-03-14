#pragma once


class MovableScript : public Script {
public:
    MovableScript(XMFLOAT3 direction);
    void Initialize(std::string name, GameObject* gameObject) override;
    void Update() override;

    inline void IdleMove() {
        std::cout << "IdleMove" << std::endl;
    }

    inline void NormalMove() {
        std::cout << "NormalMove" << std::endl;
        Transform* transformComponent = m_pGameObject->GetComponent<Transform>(ComponentType::Transform);
        if (transformComponent != nullptr) {
            transformComponent->Translate(m_direction.x * time.GetDeltaTime() * 2.5f, m_direction.y * time.GetDeltaTime() * 2.5f, m_direction.z * time.GetDeltaTime() * 2.5f);
        }

    }
private:
    XMFLOAT3 m_direction;
    Time time;
};

class ZigzagMoveScript : public Script {
public:
    ZigzagMoveScript();
    void Initialize(std::string name, GameObject* gameObject) override;
    void Update() override;

private:
    float m_zigzagSpeed;
    float m_zigzagAmplitude;
    bool m_goingRight;
    float m_currentAmplitude;
    float m_currentTime;
    float m_curvature; // Ajout du paramètre de courbure
};


class LifeScript : public Script {
public:
    LifeScript(std::shared_ptr<GameObjectManager> gameObjectManager);
    void Initialize(std::string name, GameObject* gameObject) override;
    void Update() override;

private:
    int m_health;
    std::shared_ptr<GameObjectManager> m_pGameObjectManager;
};


class LifeTimeScript : public Script
{
public: 
    LifeTimeScript(Time _time, std::shared_ptr<GameObjectManager> goManager);
    void Initialize(std::string name, GameObject* gameObject) override;
    void Update() override;

private:
    Time time;
    double lifeTime; 
    std::shared_ptr<GameObjectManager> pGameObjectManager;
};