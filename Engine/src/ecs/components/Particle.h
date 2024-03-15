#pragma once

#include "../../Utils.h"

class Renderer;
class ShaderComponent;
class Camera;
class Mesh;
class MeshRenderer;

struct Atom {
    Transform transform;

    Atom(const XMFLOAT3& position) : transform(position, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f)) {
        // Imprime les coordonnées de la position lorsque le constructeur est appelé
        //PrintMatrix(transform.GetTransformMatrix());


    }
};

class ParticleComponent : public Component {
public:
    ParticleComponent(std::string name, Renderer* renderer);

    void Initialize(Camera* camera, ComponentManager* componentManager, ResourceManager* ressourceManager, std::shared_ptr<GameObjectManager> gameObjectManager, GameObject* gameObject);

    void Update(Renderer* renderer) override;


private:
    Renderer* m_pRenderer;

    ShaderComponent* m_pBaseShader;

    Mesh* m_pBaseMesh;
    MeshRenderer* m_pBaseMeshRenderer;

    const int numParticles = 15;
    std::vector<Atom*> atoms;

    // instances

    ResourceManager* m_pResourceManager;
    std::shared_ptr<GameObjectManager> m_pGameObjectManager;
    ComponentManager* m_pComponentManager;
    GameObject* m_pGameObject;
    Camera* m_pCamera;

};
