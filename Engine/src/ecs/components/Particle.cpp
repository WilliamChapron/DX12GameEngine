#include "pch.h"
//
//#include "Particle.h"
//#include "../../Atom.h"
//
//ParticleComponent::ParticleComponent(Renderer* renderer) : m_pRenderer(renderer) {
//
//}
//
//void ParticleComponent::Initialize(Camera* camera) {
//
//    ConstantBufferData* cbData = new ConstantBufferData(); 
//    XMStoreFloat4x4(&cbData->model, XMMatrixIdentity()); ;
//    cbData->view = camera->GetViewMatrix();
//    cbData->projection = camera->GetProjectionMatrix();
//
//    cubeVertices
//
//    cubeIndices
//
//    numElementsV
//    numElementsI
//
//    m_pBaseMesh = new Mesh("meshParticle");
//    m_pBaseMesh->Initialize(cbData, m_pRenderer, cubeVertices, numElementsV, cubeIndices, numElementsI);
//
//
//    m_pBaseMeshRenderer = new MeshRenderer("MeshRenderer", cbData, m_pBaseMesh); // Component
//    m_pBaseMeshRenderer->Initialize(m_pRenderer, cbData);
//
//
//
//    m_pBaseShader = new ShaderComponent("shaderParticule", m_pRenderer);
//    m_pBaseShader->InitializeRootSignature();
//    m_pBaseShader->InitializePSO();
//
//
//}
//
//void ParticleComponent::Update() {
//    m_pRenderer->m_pCommandList->SetGraphicsRootSignature(m_pBaseShader->GetRootSignature());
//    m_pRenderer->m_pCommandList->SetPipelineState(m_pBaseShader->GetPipelineState());
//
//    //m_pBaseMeshRenderer->UpdateConstantBuffer();
//    m_pBaseMeshRenderer->Update(m_pRenderer);
//}
//
//
////void ParticleComponent::GenerateRandomAtoms(int numAtoms) {
////    std::random_device rd;
////    std::mt19937 gen(rd());
////    std::uniform_real_distribution<float> distribution(-10.0f, 10.0f); // Ajustez la plage selon vos besoins
////
////    for (int i = 0; i < numAtoms; ++i) {
////        float x = distribution(gen);
////        float y = distribution(gen);
////        float z = distribution(gen);
////
////        Atom* atom = new Atom(XMFLOAT3(x, y, z)); // Supposons que votre classe Atom prend un XMFLOAT3 comme position
////        // Faites quelque chose avec l'atome généré, par exemple, ajoutez-le à une liste d'atomes.
////    }
////}