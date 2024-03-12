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

    void Initialize(Camera* camera);

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

};
