#include "pch.h"

#include "Particle.h"
#include "../../Atom.h"
#include "Component.h"

ParticleComponent::ParticleComponent(std::string name, Renderer* renderer) : Component(name, ComponentType::ParticleComponent), m_pRenderer(renderer) {

}

float RandomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

XMFLOAT3 CalculateCirclePosition(float radius, float angle) {
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    return XMFLOAT3(x, y, 0.0f);
}




void ParticleComponent::Initialize(Camera* camera, ComponentManager* componentManager, ResourceManager* ressourceManager, std::shared_ptr<GameObjectManager> gameObjectManager, GameObject* gameObject) {

    m_pResourceManager = ressourceManager;
    m_pGameObjectManager = gameObjectManager;
    m_pComponentManager = componentManager;
    m_pGameObject = gameObject;

    ConstantBufferData* cbData = new ConstantBufferData();
    XMStoreFloat4x4(&cbData->model, XMMatrixIdentity()); ;
    cbData->view = camera->GetViewMatrix();
    cbData->projection = camera->GetProjectionMatrix();

    Transform* transformComponent = gameObject->GetComponent<Transform>(ComponentType::Transform);










    // Définition de la forme de la particule (un quad)
    Vertex particleVertices[] = {
        // Bas gauche
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
        // Bas droit
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        // Haut gauche
        { { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        // Haut droit
        { { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } }
    };

    // Nombre de sommets pour une particule
    const int numParticleVertices = 4;

    // Nombre de particules
    const int numParticles = 15;

    // Allocation dynamique d'un tableau pour les sommets
    Vertex* vertices = new Vertex[numParticles * numParticleVertices];

    // Position initiale de chaque particule dans le monde
    XMFLOAT3 particlePositions[numParticles];
    for (int i = 0; i < numParticles; ++i) {
        particlePositions[i] = XMFLOAT3(RandomFloat(-0.5f, 3.5f), RandomFloat(-0.5f, 0.5f), RandomFloat(-0.5f, 3.5f));
    }

    // Remplissage des sommets pour chaque particule
    for (int i = 0; i < numParticles; ++i) {
        // Calcul de l'offset pour les sommets de la particule actuelle
        int offset = i * numParticleVertices;

        // Appliquer la position locale à l'ensemble des sommets de la particule
        for (int j = 0; j < numParticleVertices; ++j) {
            vertices[offset + j].Pos.x = particleVertices[j].Pos.x + particlePositions[i].x;
            vertices[offset + j].Pos.y = particleVertices[j].Pos.y + particlePositions[i].y;
            vertices[offset + j].Pos.z = particleVertices[j].Pos.z + particlePositions[i].z;

            // Copie des autres attributs des sommets (normale, couleur, coordonnées de texture, etc.)
            vertices[offset + j].Color = particleVertices[j].Color;
            vertices[offset + j].Uv = particleVertices[j].Uv;
        }
    }


    // Allocation dynamique d'un tableau pour les indices
    UINT* indices = new UINT[numParticles * 6];

    // Remplissage des indices pour dessiner les particules
    for (int i = 0; i < numParticles; ++i) {
        int offset = i * 6;
        int vertexOffset = i * 4;

        // Définition des indices pour la particule actuelle
        indices[offset] = 0 + vertexOffset;
        indices[offset + 1] = 1 + vertexOffset;
        indices[offset + 2] = 2 + vertexOffset;
        indices[offset + 3] = 2 + vertexOffset;
        indices[offset + 4] = 1 + vertexOffset;
        indices[offset + 5] = 3 + vertexOffset;
    }

    Mesh* generateMesh = new Mesh("meshParticle");
    generateMesh->Initialize(cbData, m_pRenderer, vertices, numParticles*4, indices, numParticles * 6);



    GameObject* Particles = new GameObject(componentManager, "Player");
    Particles->Initialize(m_pRenderer, camera, transformComponent->GetPosition(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), generateMesh, cbData, true);
    m_pComponentManager->AddComponent(*Particles, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*Particles, m_pResourceManager->FindShaderComponentByName("shader1").component);
    m_pGameObjectManager->AddObject("Particles", Particles);




}

void ParticleComponent::Update(Renderer* renderer) {
    //PRINT("Update Particle Component");

    //m_pBaseShader->Update(m_pRenderer);
    //m_pBaseMeshRenderer->Update(m_pRenderer);
}


//void ParticleComponent::GenerateRandomAtoms(int numAtoms) {
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<float> distribution(-10.0f, 10.0f); // Ajustez la plage selon vos besoins
//
//    for (int i = 0; i < numAtoms; ++i) {
//        float x = distribution(gen);
//        float y = distribution(gen);
//        float z = distribution(gen);
//
//        Atom* atom = new Atom(XMFLOAT3(x, y, z)); // Supposons que votre classe Atom prend un XMFLOAT3 comme position
//        // Faites quelque chose avec l'atome généré, par exemple, ajoutez-le à une liste d'atomes.
//    }
//}