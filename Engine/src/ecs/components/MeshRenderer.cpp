#include "pch.h"

//#include "Mesh.h"
#include "MeshRenderer.h"
//#include "Component.h"
//
//#include "../../renderer/Graphics.h"

MeshRenderer::MeshRenderer(std::string name, ConstantBufferData* cbData, Mesh* mesh) : Component(name, ComponentType::MeshRenderer)
{

    m_cbData = cbData;
    m_pMesh = mesh;
}

void MeshRenderer::Initialize(Renderer* renderer, ConstantBufferData* cbData) {
    m_pRenderer = renderer;

    HRESULT hr;
    CD3DX12_HEAP_PROPERTIES cbHeapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC cbDesc = CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstantBufferData) + 255) & ~255);

    hr = renderer->m_pDevice->CreateCommittedResource(
        &cbHeapProps,
        D3D12_HEAP_FLAG_NONE,
        &cbDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_constantBuffer)
    );
    ASSERT_FAILED(hr);

    hr = m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedConstantBuffer));
    ASSERT_FAILED(hr);
    // Copie des données des constantes
    memcpy(m_mappedConstantBuffer, cbData, sizeof(ConstantBufferData));
    m_constantBuffer->Unmap(0, nullptr);
}

void MeshRenderer::UpdateConstantBuffer(ConstantBufferData* cbData)
{
    HRESULT hr;
    hr = m_constantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedConstantBuffer));
    ASSERT_FAILED(hr);
    // Copie des données des constantes
    memcpy(m_mappedConstantBuffer, cbData, sizeof(ConstantBufferData));
    m_constantBuffer->Unmap(0, nullptr);
}


void MeshRenderer::Update(Renderer* renderer) {

    if (m_customRenderer) {
        return;
    }
  
    HRESULT hr;

    D3D12_GPU_VIRTUAL_ADDRESS cbvAddress = m_constantBuffer->GetGPUVirtualAddress();
    renderer->m_pCommandList->SetGraphicsRootConstantBufferView(1, cbvAddress);

    renderer->m_pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    renderer->m_pCommandList->IASetVertexBuffers(0, 1, &m_pMesh->GetVertexBufferView());
    renderer->m_pCommandList->IASetIndexBuffer(&m_pMesh->GetIndexBufferView());

    renderer->m_pCommandList->DrawIndexedInstanced(m_pMesh->GetNumIndices(), 1, 0, 0, 0);
}

void MeshRenderer::MultipleSpriteDraw(Renderer* renderer, UINT indexNumber, UINT vertexNumber, UINT numParticles, std::vector<Atom*> atoms, Camera* camera) {

    HRESULT hr;

    D3D12_GPU_VIRTUAL_ADDRESS cbvAddress = m_constantBuffer->GetGPUVirtualAddress();
    renderer->m_pCommandList->SetGraphicsRootConstantBufferView(1, cbvAddress);

    renderer->m_pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    renderer->m_pCommandList->IASetVertexBuffers(0, 1, &m_pMesh->GetVertexBufferView());
    renderer->m_pCommandList->IASetIndexBuffer(&m_pMesh->GetIndexBufferView());

    UINT startIndex = 0;
    UINT baseVertex = 0;

    for (UINT i = 0; i < numParticles; ++i) {
        ConstantBufferData* cbData = new ConstantBufferData;

        cbData->model = atoms[i]->transform.GetTransformMatrix();


        cbData->view = camera->GetViewMatrix();
        XMStoreFloat4x4(&cbData->view, XMMatrixTranspose(XMMatrixInverse(nullptr, XMMatrixTranspose(XMLoadFloat4x4(&cbData->view)))));
        cbData->projection = camera->GetProjectionMatrix();


        UpdateConstantBuffer(cbData);
        renderer->m_pCommandList->DrawIndexedInstanced(6, 1, startIndex, baseVertex, 0);

        
        startIndex += indexNumber;
        baseVertex += vertexNumber;
    }
}