#include "pch.h"



Mesh::Mesh(std::string name) : m_name(name)
{
}


void Mesh::Initialize(ConstantBufferData* cbData, Renderer* renderer, Vertex* vertices, int numVertices, UINT* indices, int numIndices)
{
    const UINT vertexBufferSize = sizeof(Vertex) * numVertices;
    const UINT indexBufferSize = sizeof(UINT) * numIndices;
    const UINT stride = sizeof(Vertex);


    m_vertices = vertices;
    m_indices = indices;
    m_numVertices = numVertices;
    m_numIndices = numIndices;

    CreateIndexBuffer(indexBufferSize, indices, m_indexBuffer, m_indexBufferView, renderer);
    CreateVertexBuffer(vertexBufferSize, vertices, m_vertexBuffer, m_vertexBufferView, stride, renderer);

    
}

