#include "Renderer.h"
#include <stdio.h>
#include <Window/Window.h>

Renderer::Renderer(Window* pWindow):
	mWindow(pWindow), 
	mDevice(nullptr),
	mDeviceContext(nullptr),
	mSwapChain(nullptr),
	mRenderTargetView(nullptr)
{
	CreateDevice();
	CreateSwapChain();
	CreateRenderTargetView();
}

void Renderer::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 1, D3D11_SDK_VERSION, mDevice.GetAddressOf(), nullptr, mDeviceContext.GetAddressOf())))
	{
		printf("Failed to create d3d11 device and context. \n");
		abort();
	}
	else
	{
		printf("Successfully created d3d11 device and context! \n");
	}
}

void Renderer::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
	swapchainDesc.BufferCount = 1;
	swapchainDesc.BufferDesc.Width = mWindow->GetSize().X;
	swapchainDesc.BufferDesc.Height = mWindow->GetSize().Y;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.OutputWindow = mWindow->GetWindowNativeHandler();
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.Windowed = true;

	ComPtr<IDXGIDevice> dxgiDevice;
	mDevice.As(&dxgiDevice);

	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

	ComPtr<IDXGIFactory> dxgiFactorory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactorory));

	if (FAILED(dxgiFactorory->CreateSwapChain(mDevice.Get(), &swapchainDesc, mSwapChain.GetAddressOf())))
	{
		printf("Failed to create Swap Chain. \n");
		abort();
	}
	else
	{
		printf("Swap Chain created successfully. \n");
	}
}

void Renderer::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> colorBuffer;
	mSwapChain->GetBuffer(0, IID_PPV_ARGS(&colorBuffer));

	if (FAILED(mDevice->CreateRenderTargetView(colorBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf())))
	{
		printf("Failed to create Render Target View. \n");
		abort();
	}
	else
	{
		printf("Render Target View created successfully. \n");
	}
}

void Renderer::ClearColor(XMFLOAT4 color)
{
	float clearColor[] = { color.x, color.y, color.z, color.w };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), clearColor);
}

void Renderer::Present()
{
	mSwapChain->Present(1, 0);
}
