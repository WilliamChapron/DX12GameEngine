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

class Renderer;
class Camera;

class GameObjectManager {
public:
    GameObjectManager(Camera* camera);

    void AddObject(const std::string& name, GameObject* object);
    void RemoveObject(const std::string& name);
    void Update(Renderer* renderer);

    inline const std::unordered_map<std::string, GameObject*>& GetAliveObjects() const {
        return objectMap;
    }

private:
    Camera* m_pCamera;

    std::unordered_map<std::string, GameObject*> objectMap;
};