#include "DeviceContext.h"

void
DeviceContext::init() {

}

void
DeviceContext::update() {

}

void
DeviceContext::render() {

}

void
DeviceContext::destroy() {
	m_deviceContext->ClearState();
}

void
DeviceContext::DrawIndexed(unsigned int IndexCount,
	unsigned int StartIndexLocation,
	unsigned int BaseVertexLocation) {
	m_deviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void
DeviceContext::PSSetSamplers(unsigned int StartSlot,
	unsigned int NumSampler,
	ID3D11SamplerState* const* ppSamplers) {
	m_deviceContext->PSSetSamplers(StartSlot, NumSampler, ppSamplers);
}

void
DeviceContext::PSSetShaderResources(unsigned int StartSlot,
	unsigned int NumView,
	ID3D11ShaderResourceView* const* ppShaderRenderResourceView) {
	m_deviceContext->PSSetShaderResources(StartSlot, NumView, ppShaderRenderResourceView);
}

void
DeviceContext::PSSetConstantBuffers(unsigned int StartSlot,
	unsigned int NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers) {
	m_deviceContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader,
	ID3D11ClassInstance* const* ppClassInstance,
	unsigned int NumClassIntences) {
	m_deviceContext->PSSetShader(pPixelShader, ppClassInstance, NumClassIntences);
}

void
DeviceContext::VSSetConstantBuffers(unsigned int StartSlot,
	unsigned int NumBuffer,
	ID3D11Buffer* const* ppConstantBuffer) {
	m_deviceContext->VSSetConstantBuffers(StartSlot, NumBuffer, ppConstantBuffer);
}

void
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader,
	ID3D11ClassInstance* const* ppClassInstances,
	unsigned int NumClassInstances) {
	m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void
DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
	const float ColorRGBA[4]) {
	m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void
DeviceContext::OMSetRenderTarget(unsigned int NumViews,
	ID3D11RenderTargetView* const* ppRenderTargetView,
	ID3D11DepthStencilView* pDepthStencilView) {
	m_deviceContext->OMSetRenderTargets(NumViews, ppRenderTargetView, pDepthStencilView);
}

void
DeviceContext::RSSetViewports(unsigned int NumViewports,
	const D3D11_VIEWPORT* pViewports) {
	m_deviceContext->RSSetViewports(NumViewports, pViewports);
}

void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
	m_deviceContext->IASetInputLayout(pInputLayout);
}

void
DeviceContext::IASetVertexBuffer(unsigned int StartSlot,
	unsigned int NumBuffers,
	ID3D11Buffer* const* ppVertextBuffer,
	const unsigned int* pStride,
	const unsigned int* pOffsets) {
	m_deviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertextBuffer, pStride, pOffsets);
}

void
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
	DXGI_FORMAT Format,
	unsigned int Offset) {
	m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void
DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) {
	m_deviceContext->IASetPrimitiveTopology(Topology);
}

void
DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource,
	unsigned int DstSubresource,
	const D3D11_BOX* pDstBox,
	const void* pSrcData,
	unsigned int SrcRowPitch,
	unsigned int SrcDapthPitch) {
	m_deviceContext->UpdateSubresource(pDstResource, DstSubresource, pDstBox,
		pSrcData, SrcRowPitch, SrcDapthPitch);
}