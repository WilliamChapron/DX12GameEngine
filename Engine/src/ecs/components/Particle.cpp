#include "pch.h"

#include "Particle.h"
//#include "../../Atom.h"
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
    m_pCamera = camera;

    ConstantBufferData* cbData = new ConstantBufferData();
    XMStoreFloat4x4(&cbData->model, XMMatrixIdentity()); ;
    cbData->view = camera->GetViewMatrix();
    cbData->projection = camera->GetProjectionMatrix();

    Transform* transformComponent = gameObject->GetComponent<Transform>(ComponentType::Transform);
    XMFLOAT3 parentPos = transformComponent->GetPosition();





    for (int i = 0; i < numParticles; ++i) {
        // Générer une position relative aléatoire par rapport à la position du parent
        XMFLOAT3 relativePos(
            RandomFloat(-3.0f, 3.0f), // Amplitude pour l'axe X
            RandomFloat(0.0f, 0.0f), // Amplitude pour l'axe Y
            RandomFloat(0.0f, 0.0f)  // Amplitude pour l'axe Z
        );

        // Calculer la position globale en ajoutant la position relative à la position du parent
        XMFLOAT3 gPos(
            parentPos.x + relativePos.x,
            parentPos.y + relativePos.y,
            parentPos.z + relativePos.z
        );

        // Créer un nouvel atome avec la position globale calculée
        atoms.push_back(new Atom(gPos));
    }




    Vertex particleVertices[] = {
        // Triangle de la base (face avant)
        { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },  // Bas gauche
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },   // Bas droit
        { { 0.0f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f } },      // Sommet

        // Face latérale gauche
        { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },  // Bas gauche
        { { -0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },   // Bas droit
        { { 0.0f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f } },      // Sommet

        // Face latérale droite
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },   // Bas gauche
        { { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },    // Bas droit
        { { 0.0f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f } },      // Sommet

        // Face latérale arrière
        { { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },    // Bas gauche
        { { -0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },   // Bas droit
        { { 0.0f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f } }      // Sommet
    };

    // Nombre de sommets pour une particule
    const int numParticleVertices = 4;

    // Nombre de particules


    // Allocation dynamique d'un tableau pour les sommets
    Vertex* vertices = new Vertex[numParticles * numParticleVertices];

    // Remplissage des sommets pour chaque particule
    for (int i = 0; i < numParticles; ++i) {
        // Calcul de l'offset pour les sommets de la particule actuelle
        int offset = i * numParticleVertices;

        // Définition des sommets pour la particule actuelle
        for (int j = 0; j < numParticleVertices; ++j) {
            // Copie des coordonnées des sommets de la forme de la particule
            vertices[offset + j].Pos = particleVertices[j].Pos;

            //// Ajout de la position locale de la particule pour déplacer la forme
            //vertices[offset + j].Pos.x += RandomFloat(1.5f, 1.5f); // Ajoutez votre propre plage de génération pour chaque axe
            //vertices[offset + j].Pos.y += RandomFloat(1.5f, 1.5f);
            //vertices[offset + j].Pos.z += RandomFloat(1.5f, 1.5f);

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


    GameObject* Particles = new GameObject(componentManager, "Player");

    Transform* baseTransform = new Transform(parentPos, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
    m_pComponentManager->AddComponent(*Particles, baseTransform);

    Mesh* generateMesh = new Mesh("meshParticle");
    generateMesh->Initialize(cbData, m_pRenderer, vertices, numParticles* 4, indices, numParticles*6);

    m_pBaseMeshRenderer = new MeshRenderer("MeshRenderer", cbData, generateMesh); // Component
    m_pBaseMeshRenderer->Initialize(m_pRenderer, cbData);
    // Set custom renderer 
    Particles->m_customRenderer = true;
    m_pBaseMeshRenderer->m_customRenderer = true;
    m_pComponentManager->AddComponent(*Particles, m_pBaseMeshRenderer);




    //Particles->Initialize(m_pRenderer, camera, transformComponent->GetPosition(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), generateMesh, cbData, false);
    m_pComponentManager->AddComponent(*Particles, m_pResourceManager->FindTextureComponentByName("texture").component);
    m_pComponentManager->AddComponent(*Particles, m_pResourceManager->FindShaderComponentByName("shader1").component);

    m_pGameObjectManager->AddObject("Particles", Particles);




}

void ParticleComponent::Update(Renderer* renderer) {
    PRINT("Update Particle Component");
    m_pBaseMeshRenderer->MultipleSpriteDraw(m_pRenderer, 6, 4, 15, atoms, m_pCamera);

    
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