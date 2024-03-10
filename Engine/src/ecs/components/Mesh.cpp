#include "../../../pch.h"

#include "Mesh.h"
#include "Component.h"

#include "../../renderer/Graphics.h"

#include "../entities/GameObject.hpp"




Mesh::Mesh(std::string name) : m_name(name)
{
}


void Mesh::Initialize(ConstantBufferData* cbData, Renderer* renderer, Vertex* vertices, int numVertices, UINT* indices, int numIndices)
{
    //PRINT("INITIALIZE MESH");
    // Calcul des tailles des tampons de sommets et d'indices
    const UINT vertexBufferSize = sizeof(Vertex) * numVertices;
    const UINT indexBufferSize = sizeof(UINT) * numIndices;
    const UINT stride = sizeof(Vertex);

    m_numVertices = numVertices;
    m_numIndices = numIndices;


    //PRINT("NUMelement");
    //PRINT(numElementsI);

    // Création des tampons de sommets et d'indices
    CreateIndexBuffer(indexBufferSize, indices, m_indexBuffer, m_indexBufferView, renderer);
    CreateVertexBuffer(vertexBufferSize, vertices, m_vertexBuffer, m_vertexBufferView, stride, renderer);

    
}

