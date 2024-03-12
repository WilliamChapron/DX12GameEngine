#include "pch.h"

#include "Particle.h"
#include "../../Atom.h"
#include "Component.h"

ParticleComponent::ParticleComponent(std::string name, Renderer* renderer) : Component(name, ComponentType::ParticleComponent), m_pRenderer(renderer) {

}

void ParticleComponent::Initialize(Camera* camera) {

    ConstantBufferData* cbData = new ConstantBufferData(); 
    XMStoreFloat4x4(&cbData->model, XMMatrixIdentity()); ;
    cbData->view = camera->GetViewMatrix();
    cbData->projection = camera->GetProjectionMatrix();

    Transform* baseTransform = new Transform(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
    cbData->model = baseTransform->GetTransformMatrix();



    //std::vector<Vertex> cubeVertices; 
    //std::vector<UINT> cubeIndices;

    //// Cube 1
    //cubeVertices.push_back({ {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} });
    //cubeVertices.push_back({ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} });
    //cubeVertices.push_back({ {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f} });
    //cubeVertices.push_back({ {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f} });
    //cubeVertices.push_back({ { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} });
    //cubeVertices.push_back({ { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} });
    //cubeVertices.push_back({ { 0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f} });
    //cubeVertices.push_back({ { 0.5f,  0.5f,  0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f} });


    //cubeIndices.push_back(0); cubeIndices.push_back(1); cubeIndices.push_back(2);
    //cubeIndices.push_back(2); cubeIndices.push_back(1); cubeIndices.push_back(3);
    //cubeIndices.push_back(4); cubeIndices.push_back(6); cubeIndices.push_back(5);
    //cubeIndices.push_back(6); cubeIndices.push_back(7); cubeIndices.push_back(5);
    //cubeIndices.push_back(0); cubeIndices.push_back(2); cubeIndices.push_back(4);
    //cubeIndices.push_back(2); cubeIndices.push_back(6); cubeIndices.push_back(4);
    //cubeIndices.push_back(1); cubeIndices.push_back(5); cubeIndices.push_back(3);
    //cubeIndices.push_back(3); cubeIndices.push_back(5); cubeIndices.push_back(7);
    //cubeIndices.push_back(2); cubeIndices.push_back(3); cubeIndices.push_back(6);
    //cubeIndices.push_back(3); cubeIndices.push_back(7); cubeIndices.push_back(6);
    //cubeIndices.push_back(0); cubeIndices.push_back(4); cubeIndices.push_back(1);
    //cubeIndices.push_back(1); cubeIndices.push_back(4); cubeIndices.push_back(5);

    //// Cube 2
    //cubeVertices.push_back({ {-2.0f, -2.0f, -2.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} });
    //cubeVertices.push_back({ {-2.0f, -2.0f,  2.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} });
    //cubeVertices.push_back({ {-2.0f,  2.0f, -2.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} });
    //cubeVertices.push_back({ {-2.0f,  2.0f,  2.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} });
    //cubeVertices.push_back({ { 2.0f, -2.0f, -2.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f} });
    //cubeVertices.push_back({ { 2.0f, -2.0f,  2.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f} });
    //cubeVertices.push_back({ { 2.0f,  2.0f, -2.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f} });
    //cubeVertices.push_back({ { 2.0f,  2.0f,  2.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f} });

    //// Ajouter les indices pour le deuxième cube
    //int offset = static_cast<int>(cubeVertices.size()) - 8; // 8 vertices pour le premier cube
    //cubeIndices.push_back(0 + offset); cubeIndices.push_back(1 + offset); cubeIndices.push_back(2 + offset);
    //cubeIndices.push_back(2 + offset); cubeIndices.push_back(1 + offset); cubeIndices.push_back(3 + offset);
    //cubeIndices.push_back(4 + offset); cubeIndices.push_back(6 + offset); cubeIndices.push_back(5 + offset);
    //cubeIndices.push_back(6 + offset); cubeIndices.push_back(7 + offset); cubeIndices.push_back(5 + offset);
    //cubeIndices.push_back(0 + offset); cubeIndices.push_back(2 + offset); cubeIndices.push_back(4 + offset);
    //cubeIndices.push_back(2 + offset); cubeIndices.push_back(6 + offset); cubeIndices.push_back(4 + offset);
    //cubeIndices.push_back(1 + offset); cubeIndices.push_back(5 + offset); cubeIndices.push_back(3 + offset);
    //cubeIndices.push_back(3 + offset); cubeIndices.push_back(5 + offset); cubeIndices.push_back(7 + offset);
    //cubeIndices.push_back(2 + offset); cubeIndices.push_back(3 + offset); cubeIndices.push_back(6 + offset);
    //cubeIndices.push_back(3 + offset); cubeIndices.push_back(7 + offset); cubeIndices.push_back(6 + offset);
    //cubeIndices.push_back(0 + offset); cubeIndices.push_back(4 + offset); cubeIndices.push_back(1 + offset);
    //cubeIndices.push_back(1 + offset); cubeIndices.push_back(4 + offset); cubeIndices.push_back(5 + offset);



    //int numElementsV = cubeVertices.size();
    //int numElementsI = cubeIndices.size();

    Vertex* cubeVertices = new Vertex[8]{
    { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
    { {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
    { {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },
    { {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
    { { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
    { { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
    { { 0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f} },
    { { 0.5f,  0.5f,  0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f} }
    };

    UINT* cubeIndices = new UINT[36]{
        0, 1, 2,
        2, 1, 3,
        4, 6, 5,
        6, 7, 5,
        0, 2, 4,
        2, 6, 4,
        1, 5, 3,
        3, 5, 7,
        2, 3, 6,
        3, 7, 6,
        0, 4, 1,
        1, 4, 5
    };

    int numElementsV = 8;
    int numElementsI = 36;





    m_pBaseShader = new ShaderComponent("shaderParticule", m_pRenderer);
    m_pBaseShader->InitializeRootSignature();
    m_pBaseShader->InitializePSO();

    m_pBaseMesh = new Mesh("meshParticle");
    //m_pBaseMesh->Initialize(cbData, m_pRenderer, cubeVertices.data(), numElementsV, cubeIndices.data(), numElementsI);
    m_pBaseMesh->Initialize(cbData, m_pRenderer, cubeVertices, numElementsV, cubeIndices, numElementsI);



    m_pBaseMeshRenderer = new MeshRenderer("MeshRenderer", cbData, m_pBaseMesh); // Component
    m_pBaseMeshRenderer->Initialize(m_pRenderer, cbData);


}

void ParticleComponent::Update(Renderer* renderer) {
    PRINT("Update Particle Component");

    m_pBaseShader->Update(m_pRenderer);
    m_pBaseMeshRenderer->Update(m_pRenderer);
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