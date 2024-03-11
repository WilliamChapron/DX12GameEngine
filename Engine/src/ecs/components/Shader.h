#pragma once

class Renderer;

using namespace DirectX;
using Microsoft::WRL::ComPtr;


class ShaderComponent : public Component
{
public:
	ShaderComponent(std::string name, Renderer* pRenderer);
	~ShaderComponent();

	void InitializePSO();
	void InitializeRootSignature();
	void Update(Renderer* pRenderer) override;
	void UpdatePSO();
	void UpdateRootSignature();


	inline ID3DBlob* GetVertexShaderBlob() const { return m_vertexShaderBlob.Get(); }
	inline ID3DBlob* GetPixelShaderBlob() const { return m_pixelShaderBlob.Get(); }
	inline ID3D12PipelineState* GetPipelineState() const { return m_pPipelineState.Get(); }
	inline ID3D12RootSignature* GetRootSignature() const { return m_pRootSignature.Get(); }

private:

	Renderer* m_pRenderer;

	ComPtr<ID3DBlob> m_vertexShaderBlob;
	ComPtr<ID3DBlob> m_pixelShaderBlob;

	ComPtr<ID3D12PipelineState> m_pPipelineState;
	ComPtr<ID3D12RootSignature> m_pRootSignature;
	
};

