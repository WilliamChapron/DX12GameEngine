#pragma once


class MovableScript : public Script {
public:
    void Initialize(std::string name, GameObject* gameObject) override;
    void Update() override;

    inline void IdleMove() {
        std::cout << "IdleMove" << std::endl;
    }

    inline void NormalMove() {
        std::cout << "NormalMove" << std::endl;
        Transform* transformComponent = m_pGameObject->GetComponent<Transform>(ComponentType::Transform);
        if (transformComponent != nullptr) {
            transformComponent->Translate(0, 0, 0.01);
        }

    }
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
    float m_curvature; // Ajout du param�tre de courbure
};


class LifeScript : public Script {
public:
    LifeScript(std::string name, GameObject* gameObject, std::shared_ptr<GameObjectManager> gameObjectManager);
    void Initialize(std::string name, GameObject* gameObject) override;
    void Update() override;

private:
    int m_health;
    std::shared_ptr<GameObjectManager> m_pGameObjectManager;
};

