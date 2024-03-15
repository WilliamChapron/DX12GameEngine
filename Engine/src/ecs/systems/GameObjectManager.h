#pragma once

#include "../../include.h"
#include "../../core/Defines.h"
#include "../entities/GameObject.hpp"
#include <vector>
#include <unordered_map>
#include <string>

struct TestedPair {
    std::string first;
    std::string second;

    bool operator == (const TestedPair& other) const {
        return (first == other.second);
    }
};

struct ObjectPosZPair {
    GameObject* object;
    float positionZ;

    bool operator<(const ObjectPosZPair& other) const {
        return positionZ < other.positionZ;
    }
};

class Renderer;
class Camera;

class GameObjectManager {
public:
    GameObjectManager(Camera* camera);

    void AddObject(const std::string& name, GameObject* object);
    void RemoveObject(GameObject* object);
    void Update(Renderer* renderer);
    void UpdateCustomGameObject(GameObject* go, Renderer* renderer);
    
    inline const std::unordered_map<std::string, std::vector<GameObject*>>& GetAliveObjects() const {
        return objectMap;
    }

private:
    Camera* m_pCamera;

    std::unordered_map<std::string, std::vector<GameObject*>> objectMap;
};