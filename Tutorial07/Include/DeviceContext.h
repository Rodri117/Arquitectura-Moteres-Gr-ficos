#include "Prerrequisitos.h"
#pragma once

class
DeviceContext {
public:
	DeviceContext() = default;
	~DeviceContext() {SAFE_RELEASE(m_deviceContext);}

	void
	init();

	void
	update();

	void
	render();

	void
	destroy();

	//
	void
	DrawIndexed(unsigned int IndexCount,
			unsigned int StartIndexLocation,
			unsigned int BaseVertextLocation);
	//
	void
	PSSetSamplers(unsigned int StartSolt,
			unsigned int NumSampler,
			ID3D11SamplerState* const* ppSamplers);
	//
	void
	PSSetShaderResources(unsigned int StartSlot,
			unsigned int NumView,
			ID3D11ShaderResourceView* const* ppShaderResourceViews);
	//
	void
	PSSetConstantBuffers(unsigned int StartSlot,
			unsigned int NumBuffer,
			ID3D11Buffer* const* ppConstantBuffer);
	//
	void
	PSSetShader(ID3D11PixelShader* pPixelShader,
			ID3D11ClassInstance* const* ppClassInstances,
			unsigned int NumClassInstances);
	//
	void
	VSSetConstantBuffers(unsigned int StartSlot,
			unsigned int NumBuffer,
			ID3D11Buffer* const* ppConstantBuffer);
	//
	void
	VSSetShader(ID3D11PixelShader* pPixelShader,
			ID3D11ClassInstance* const* ppClassInstances,
			unsigned int NumClassInstances);

	//
	void
	ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
			const float ColorRGBA[4]);
	//
	void
	OMSetRenderTarget(unsigned int NumViews,
			ID3D11RenderTargetView* const* ppRenderTargetView,
			ID3D11DepthStencilView* pDepthStencilView);
	//
	void
	RSSetViewports(unsigned int NumViewports,
			const D3D11_VIEWPORT* pViewports);
	//
	void
	IASetInputLayout(ID3D11InputLayout* pInputLayout);
	//
	void 
	IASetVertexBuffer(unsigned int StartSlot,
		unsigned int NumBuffers,
		ID3D11Buffer* const* ppVertextBuffer,
		const unsigned int* pStride,
		const unsigned int* pOffsets);
	//
	void
	IASetVertextBuffer(ID3D11Buffer* pIndexBuffer,
			DXGI_FORMAT Format,
			unsigned int Offset);
	//
	void
	IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
	//
	void
	UpdateSubresource(ID3D11Resource* pDstResource,
			unsigned int DstSubresource,
			const D3D11_BOX* pDstBox,
			const void* pSrcData,
			unsigned int SrcRowPitch,
			unsigned int SrcDapthPitch);

public:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};