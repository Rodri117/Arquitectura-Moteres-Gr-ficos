//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
// Rodrigo D.R
// 
//--------------------------------------------------------------------------------------

//Más ordenado el projecto y el orden de llamadas
#include "Prerequisities.h"

#include "Commons.h"

#include "RTime.h"
#include "UserInterface.h"

#include "Window.h"
#include "DeviceContext.h"
#include "Device.h"
#include "DepthStencilView.h"
#include "Texture.h"
#include "InputLayout.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "Transform.h"
#include "SamplerState.h"
#include "Viewport.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ModelLoader.h"
#include "ShaderProgram.h"
#include "ConstantBuffer.h"


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
Window                              g_window;
DeviceContext                       g_deviceContext;
Device                              g_device;
DepthStencilView                    g_depthStencilView;
Texture                             g_ModelTexture;
Texture                             g_depthStencil;
Texture                             g_backBuffer;
//InputLayout                         g_inputLayout;
SwapChain                           g_swapChain;
RenderTargetView                    g_renderTargetView;
SamplerState                        g_samplerState;
Viewport                            g_viewport;
Transform                           g_transform;
RTime                               g_Time;

Camera                              cam;
VertexBuffer                        g_vertexBuffer;
LoadData                            LD;
IndexBuffer                         g_indexBuffer;
ModelLoader                         g_modelLoader;
ShaderProgram                       g_shaderProgram;
UserInterface                       UI;
ConstantBuffer                      g_constantBuffer;

//ID3D11VertexShader*                 g_pVertexShader = nullptr;
//ID3D11PixelShader*                  g_pPixelShader = nullptr;

ID3D11Buffer* g_Camera = nullptr;
//ID3D11Buffer*                       g_pCBChangesEveryFrame = nullptr;

XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT
InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT
InitDevice();
LRESULT
CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void
Render();
void
update();
void
destroy();

//--------------------------------------------------------------------------------------
int
WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //Inicializamos la ventana
    if (FAILED(g_window.init(hInstance, nCmdShow, WndProc, "ChemasteR")))
        return 0;

    if (FAILED(InitDevice())) {
        destroy();
        return 0;
    }

    //Inicializamos el tiempo
    g_Time.init();
    //Inicializamos el transform
    g_transform.init();

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message) {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            g_Time.uptade();
            update();
            Render();
        }
    }

    destroy();

    return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT
CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, nullptr, ppBlobOut, &pErrorBlob, nullptr);
    if (FAILED(hr)) {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------

HRESULT
InitDevice() {
    HRESULT hr = S_OK;

    //Create swap chain
    g_swapChain.init(g_device, g_deviceContext, g_backBuffer, g_window);

    // Create a render target view
    g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);

    g_backBuffer.destroy();
    if (FAILED(hr)) {
        return hr;
    }

    // Create depth stencil texture
    g_depthStencil.init(g_device,
        g_window.m_width,
        g_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL);

    // Create the depth stencil view
    g_depthStencilView.init(g_device, g_depthStencil.m_texture, DXGI_FORMAT_D24_UNORM_S8_UINT);

    // Setup the viewport
    g_viewport.init(g_window);


    //Define the input layout
    std::vector <D3D11_INPUT_ELEMENT_DESC> Layout;

    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);


    // Create the input layout
    //g_inputLayout.init(g_device, Layout, pVSBlob);
    g_shaderProgram.init(g_device, "Tutorial07.fx", Layout);

    /*LD = g_ModelTexture*/

    LD = g_modelLoader.load("Pistol.obj");

    //Set VertexBuffer
    g_vertexBuffer.init(g_device, LD);

    //INDEX BUFFER
    g_indexBuffer.init(g_device, LD);


    //Create the constant buffers
    D3D11_BUFFER_DESC CamBufferDesc;
    memset(&CamBufferDesc, 0, sizeof(CamBufferDesc));
    CamBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    CamBufferDesc.ByteWidth = sizeof(Camera);
    CamBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    CamBufferDesc.CPUAccessFlags = 0;
    hr = g_device.CreateBuffer(&CamBufferDesc, nullptr, &g_Camera);
    if (FAILED(hr)) {
        return hr;
    }

    //AQUÍ CREAMOS EL CBChanges
    //Buffer modelo
    g_constantBuffer.init(g_device, sizeof(CBChangesEveryFrame));


    // Load the Texture
    g_ModelTexture.init(g_device, "GunAlbedo.dds");

    //Create the sample state
    g_samplerState.init(g_device);

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
    XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    g_View = XMMatrixLookAtLH(Eye, At, Up);

    // Initialize the projection matrix (global)
    g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);

    cam.mView = XMMatrixTranspose(g_View);
    cam.mProjection = XMMatrixTranspose(g_Projection);

    //Initialize Classes
    UI.init(g_window.m_hWnd, g_device.m_device, g_deviceContext.m_deviceContext);

    return S_OK;
}


//Esta función está encargada de actualizar la LÓGICA del programa

float f = 0;
void
update() {

    UI.update();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Begin("TRANSFORM");
    ImGui::Text("POSITION");
    ImGui::SliderFloat("Position X", &g_transform.m_v3Position.x, -4.0f, 1.0f);
    ImGui::SliderFloat("Position Y", &g_transform.m_v3Position.y, -2.0f, 2.0f);
    ImGui::SliderFloat("Position Z", &g_transform.m_v3Position.z, -2.0f, 2.0f);

    ImGui::Text("ROTATION");
    ImGui::SliderFloat("Rotation X", &g_transform.m_v3Rotate.x, -6.0f, 6.0f);
    ImGui::SliderFloat("Rotation Y", &g_transform.m_v3Rotate.y, -6.0f, 6.0f);
    //ImGui::SliderFloat("Position Y", &g_transform.m_v3Position.y, -2.0f, 2.0f);
    //ImGui::SliderFloat("Position Z", &g_transform.m_v3Position.z, -2.0f, 2.0f);
    ImGui::End();

    UI.vec3Control("Position", &g_transform.m_v3Position.x);
    UI.vec3Control("Rotation", &g_transform.m_v3Rotate.x);
    UI.vec3Control("Escale", &g_transform.m_v3Scale.x, 0.5f);

    g_transform.m_fRotateNum += 0.0002f;

    g_World = XMMatrixScaling(g_transform.m_v3Scale.x,
        g_transform.m_v3Scale.y,
        g_transform.m_v3Scale.z) *

        //XMMatrixRotationY  (g_transform.m_fRotateNum) * 
        XMMatrixRotationX(g_transform.m_v3Rotate.x) *
        XMMatrixRotationY(g_transform.m_v3Rotate.y) *
        XMMatrixRotationZ(g_transform.m_v3Rotate.z) *

        XMMatrixTranslation(g_transform.m_v3Position.x,
            g_transform.m_v3Position.y,
            g_transform.m_v3Position.z);

    // Update variables that change once per frame
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;

    //Update Mesh Buffers
    /*g_deviceContext.UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);*/
    //Aquí mandamos a llamar el update
    g_constantBuffer.update(g_deviceContext, 0, nullptr, &cb, 0, 0);

    //UpdateCamera Buffers
    g_deviceContext.UpdateSubresource(g_Camera, 0, nullptr, &cam, 0, 0);


}


//--------------------------------------------------------------------------------------
// Limpiar los objetos creados
//--------------------------------------------------------------------------------------
void
destroy() {
    g_deviceContext.destroy();
    g_samplerState.destroy();
    g_ModelTexture.destroy();

    if (g_Camera) g_Camera->Release();
    //if( g_pCBChangesEveryFrame ) g_pCBChangesEveryFrame->Release();
    g_constantBuffer.destroy();
    g_vertexBuffer.destroy();
    /*if( g_pVertexBuffer ) g_pVertexBuffer->Release();*/
    /*if( g_pIndexBuffer ) g_pIndexBuffer->Release();*/
    g_indexBuffer.destroy();
    g_shaderProgram.destroy();
    g_depthStencil.destroy();
    g_depthStencilView.destroy();
    g_renderTargetView.destroy();
    g_swapChain.destroy();
    UI.destroy();
    g_device.destroy();

}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT
ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



//--------------------------------------------------------------------------------------
LRESULT
CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:

        switch (wParam) {

        case 'A':
            g_transform.m_v3Position.x -= g_transform.m_fSpeed * g_Time.m_fDeltaTime;
            break;

        case 'D':
            g_transform.m_v3Position.x += g_transform.m_fSpeed * g_Time.m_fDeltaTime;
            break;

        case 'W':
            g_transform.m_v3Position.y += g_transform.m_fSpeed * g_Time.m_fDeltaTime;
            break;

        case 'S':
            g_transform.m_v3Position.y -= g_transform.m_fSpeed * g_Time.m_fDeltaTime;
            break;

        case 'I':
            g_transform.m_v3Position.z += g_transform.m_fSpeed * g_Time.m_fDeltaTime;
            break;

        case 'O':
            g_transform.m_v3Position.z -= g_transform.m_fSpeed * g_Time.m_fDeltaTime;
            break;

        case '1':
            g_vMeshColor = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
            break;

        case '2':
            g_vMeshColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
            break;

        case '3':
            g_vMeshColor = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
            break;

        case '4':
            g_vMeshColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
            break;
        }

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
// Esta función esta encarga de actualizar exclusivamente
// los datos que se presentan en pantalla
//--------------------------------------------------------------------------------------
void
Render() {
    //
    // Clear the back buffer
    //
    /*float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };*/ // red, green, blue, alpha
    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    //g_deviceContext.ClearDepthStencilView(g_depthStencilView.m_pDepthStencilView, 
    //                                      D3D11_CLEAR_DEPTH, 
    //                                      1.0f, 
    //                                      0 );
    g_depthStencilView.render(g_deviceContext);

    //Class render target view
    //g_deviceContext.ClearRenderTargetView(g_renderTargetView.m_renderTargetView, ClearColor );
    //g_deviceContext.OMSetRenderTargets(1, &g_renderTargetView.m_renderTargetView, g_depthStencilView.m_pDepthStencilView);
    g_renderTargetView.render(g_deviceContext, g_depthStencilView);



    //Class viewport
    //g_deviceContext.RSSetViewports(1, &g_viewport.m_viewport); //va en mi clase de viewport
    g_viewport.render(g_deviceContext);

    //// Set the input layout
    //g_deviceContext.IASetInputLayout(g_shaderProgram.m_inputLayout.m_inputLayout);

    g_shaderProgram.render(g_deviceContext);

    //Set constants buffers (camera)
    g_deviceContext.VSSetConstantBuffers(0, 1, &g_Camera);

    //Set sampler
   /* g_deviceContext.PSSetSamplers( 0, 1, &g_samplerState.m_sampler );*/
    g_samplerState.render(g_deviceContext);

    //Set vertex e indexbuffer
    g_vertexBuffer.render(g_deviceContext, 0);
    g_indexBuffer.render(g_deviceContext, DXGI_FORMAT_R32_UINT);

    //Set constant buffers
    //g_deviceContext.VSSetConstantBuffers( 1, 1, &g_pCBChangesEveryFrame );
    //g_deviceContext.PSSetConstantBuffers( 1, 1, &g_pCBChangesEveryFrame );
    //Aquí mandamos a llamar los PsetConstantBuffers
    g_constantBuffer.VSSetConstantBuffer(g_deviceContext, 1, 1);
    g_constantBuffer.PSSetConstantBuffers(g_deviceContext, 1, 1);

    // Set primitive topology
    g_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //Set shader resources (texture)
   /* g_deviceContext.PSSetShaderResources( 0, 1, &g_ModelTexture.m_textureFromImg );*/
    g_ModelTexture.render(g_deviceContext);



    // Set index buffer
    //g_deviceContext.IASetIndexBuffer(g_indexBuffer.m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

    g_deviceContext.DrawIndexed(LD.index.size(), 0, 0);

    UI.render();

    //
    // Present our back buffer to our front buffer
    //
    g_swapChain.present();
}
