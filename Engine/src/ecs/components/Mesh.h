#pragma once

using namespace DirectX;

struct ConstantBufferData;

class MeshRenderer;
class Renderer;

// Vertex
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
	XMFLOAT2 Uv;
};

class Mesh
{
public:
	Mesh(std::string name);
	void Initialize(ConstantBufferData* cbData, Renderer* renderer, Vertex* vertices, int numVertices, UINT* indices, int numIndices);

	inline std::string GetName() {
		return m_name;
	}

	ID3D12Resource* GetVertexBuffer() const { return m_vertexBuffer; }
	const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView() const { return m_vertexBufferView; }
	ID3D12Resource* GetIndexBuffer() const { return m_indexBuffer; }
	const D3D12_INDEX_BUFFER_VIEW& GetIndexBufferView() const { return m_indexBufferView; }

	inline Vertex* GetVertices() const { return m_vertices;}
	inline UINT* GetIndices() const {return m_indices;}
	int GetNumVertices() const { return m_numVertices;}
	int GetNumIndices() const { return m_numIndices;}

private:
	std::string m_name;

	Vertex* m_vertices;
	UINT* m_indices;

	// Vertex buffer
	ID3D12Resource* m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	// Index buffer
	ID3D12Resource* m_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

	int m_numVertices;
	int m_numIndices;
};
