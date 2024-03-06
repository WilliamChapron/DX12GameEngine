#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager() : m_hInstance(nullptr), m_nShowCmd(0), m_pConsole(nullptr), m_pInput(nullptr), m_pCamera(nullptr), m_pGameObjectManager(nullptr) {}

void GameManager::Initialize() {

    ////m_hInstance = hInstance;
    ////m_nShowCmd = nShowCmd;

    //m_pInput = new Input();
    //m_pCamera = new Camera(); // #TODO Shared ptr camera to each object



    //m_pGameObjectManager = std::make_shared<GameObjectManager>(m_pCamera);
    //m_pComponentManager = new ComponentManager(m_pGameObjectManager, m_pRenderer);


    //// Create Objects
    //m_pTriangle = new CubeMesh;
    //m_pTriangle2 = new CubeMesh;

    //m_pTriangle->Initialize(m_pRenderer, m_pCamera, m_pComponentManager, XMFLOAT3(0.5f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
    ////m_pTriangle2->Initialize(m_pRenderer, m_pCamera, m_pComponentManager, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));



    ////m_pTriangle3 = new Triangle;
    ////m_pTriangle3->Initialize(m_pRenderer, m_pCamera, XMFLOAT3(0.7f, -2.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));

    ////m_pGameObjectManager->AddObject("Triangle", m_pTriangle);
    //m_pGameObjectManager->AddObject("Triangle2", m_pTriangle2);

    //// Add component after object

    ////m_pComponentManager->AddComponent(m_pTriangle2, compiledTexture[0]);
    ////m_pGameObjectManager->AddObject("Triangle3", *m_pTriangle3);
    


}

void GameManager::Update() {
    //// Mettez à jour ici les membres de GameManager
    //// Par exemple:
    //m_pInput->Update(); // Mettez à jour l'Input
    //m_pGameObjectManager->Update(m_pRenderer); // Mettez à jour le GameObjectManager
}

void CubeMesh::Initialize(Renderer* renderer, Camera* camera, ComponentManager* componentManager, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale) {
//    //m_transform = Transform(position, rotation, scale);
//    //m_cbData.model = m_transform.GetTransformMatrix();
//
//
//
//    Transform* defaultTransform = new Transform(position, rotation, scale);
//    TextureComponent* defaultTexture = new TextureComponent("texture");
//    defaultTexture->Initialize(renderer);
//
//    componentManager->AddComponent(*this, defaultTransform);
//    componentManager->AddComponent(*this, defaultTexture);
//
//    //defaultTransform->Update();
//
//
//    m_cbData.model = defaultTransform->GetTransformMatrix();
//
//    // ** MATRIX
//
//    m_cbData.view = camera->GetViewMatrix();
//    m_cbData.projection = camera->GetProjectionMatrix();
//
//    // MATRIX **
//    HRESULT hr;
//
//    Vertex cubeVertices[] = {
//        { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
//        { {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
//        { {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },
//        { {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
//        { { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
//        { { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
//        { { 0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f} },
//        { { 0.5f,  0.5f,  0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f} }
//    };
//
//    UINT cubeIndices[] = {
//        0, 1, 2,
//        2, 1, 3,
//        4, 6, 5,
//        6, 7, 5,
//        0, 2, 4,
//        2, 6, 4,
//        1, 5, 3,
//        3, 5, 7,
//        2, 3, 6,
//        3, 7, 6,
//        0, 4, 1,
//        1, 4, 5
//    };
//
//    const UINT vertexBufferSize = sizeof(cubeVertices);// *sizeof(Vertex);
//    const UINT indexBufferSize = sizeof(cubeIndices);// *sizeof(UINT);
//    const UINT stride = sizeof(Vertex);
//
//
//    CreateIndexBuffer(indexBufferSize, cubeIndices, m_indexBuffer, m_indexBufferView, renderer);
//    CreateVertexBuffer(vertexBufferSize, cubeVertices, m_vertexBuffer, m_vertexBufferView, stride, renderer);
//
//    // * Constant Buffer
//    CD3DX12_HEAP_PROPERTIES cbHeapProps(D3D12_HEAP_TYPE_UPLOAD);
//    CD3DX12_RESOURCE_DESC cbDesc = CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstantBufferData) + 255) & ~255);
//
//    hr = renderer->m_pDevice->CreateCommittedResource(
//        &cbHeapProps,
//        D3D12_HEAP_FLAG_NONE,
//        &cbDesc,
//        D3D12_RESOURCE_STATE_GENERIC_READ,
//        nullptr,
//        IID_PPV_ARGS(&m_constantBuffer)
//    );
//    ASSERT_FAILED(hr);
//
//    hr = m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedConstantBuffer));
//    ASSERT_FAILED(hr);
//
//    memcpy(m_mappedConstantBuffer, &m_cbData, sizeof(ConstantBufferData));
//    m_constantBuffer->Unmap(0, nullptr);
//
//
//    //D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
//    //cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
//    //cbvDesc.SizeInBytes = (sizeof(ConstantBufferData) + 255) & ~255; // Alignement sur 256 octets
//   // renderer->m_pDevice->CreateConstantBufferView(&cbvDesc, renderer->m_pCbvSrvHeap->GetCPUDescriptorHandleForHeapStart());
//    // Constant Buffer *
//}
