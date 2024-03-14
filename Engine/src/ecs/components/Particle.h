#pragma once

class Atom;
class Renderer;
class ShaderComponent;
class Camera;
class Mesh;
class MeshRenderer;


class ParticleComponent : public Component {
public:
    ParticleComponent(std::string name, Renderer* renderer);

    void Initialize(Camera* camera, ComponentManager* componentManager, ResourceManager* ressourceManager, std::shared_ptr<GameObjectManager> gameObjectManager, GameObject* gameObject);

    void InitializeAtomsVertex();
    void InitializeShader();
    void InitializeTexture();

    void Update(Renderer* renderer) override;

    void PrintAtomPositions();
private:
    Renderer* m_pRenderer;

    ShaderComponent* m_pBaseShader;

    Mesh* m_pBaseMesh;
    MeshRenderer* m_pBaseMeshRenderer;

    std::vector<Atom> atoms;

    // instances

    ResourceManager* m_pResourceManager;
    std::shared_ptr<GameObjectManager> m_pGameObjectManager;
    ComponentManager* m_pComponentManager;
    GameObject* m_pGameObject;

};
