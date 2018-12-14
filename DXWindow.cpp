
#include "resource.h"

#include "DXWindow.h"
#include "stdafx.h  "


LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
LPDIRECT3D9 d3d;             // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);        // closes Direct3D and releases memory

DXWindow *SCREEN;

DXWindow::DXWindow(){}
DXWindow::~DXWindow(){ ShutdownWindows(); cleanD3D(); }

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 105:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
INT_PTR CALLBACK About   (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}




DXWindow::DXWindow(int x,int y, int w, int h, LPCWSTR title)
    : Title(title)
{
         bool Success = 0;
        
         Instance = GetModuleHandle(NULL);
        
        
         ClassName = title;

//Step 1: Registering the Window Class
        WINDOW_CLASS.cbSize        = sizeof(WNDCLASSEX);
        WINDOW_CLASS.style         = 0;
        WINDOW_CLASS.lpfnWndProc   = WndProc;
        WINDOW_CLASS.cbClsExtra    = 0;
        WINDOW_CLASS.cbWndExtra    = 0;
        WINDOW_CLASS.hInstance     = Instance;
        WINDOW_CLASS.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
        WINDOW_CLASS.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        WINDOW_CLASS.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
        WINDOW_CLASS.lpszMenuName  = nullptr;
        WINDOW_CLASS.lpszClassName = ClassName;
        WINDOW_CLASS.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
        
        if(!RegisterClassEx(&WINDOW_CLASS))
        {
            MessageBox(NULL, L"Window Registration Failed!", L"Error!",MB_ICONEXCLAMATION | MB_OK);
        }

// =============== Creating the Window =================================================================================================================================
        Handle = CreateWindowEx(WS_EX_CLIENTEDGE, ClassName, title, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, w, h,nullptr, nullptr, Instance, nullptr);
        
        if(Handle == NULL){MessageBox(NULL, L"Window Creation Failed!", L"Error!",MB_ICONEXCLAMATION | MB_OK);}
        
        SetGraphicsMode(DeviceContext, GM_ADVANCED);
        
        Graphics = new Graphics2D();
        Graphics->Init(Handle);
//==================================================================================================================================================================      
        
        ShowWindow(Handle, SW_SHOWNORMAL);
        UpdateWindow(Handle);
        
        DeviceContext =  GetDC(Handle);
        
        if(DeviceContext == nullptr)Success = false;
        
        initD3D(Handle);
}



void DXWindow::ShutdownWindows()
{
// Show the mouse cursor.
        ShowCursor(true);
// Remove the window.
        DestroyWindow(Handle);
        Handle = NULL;
        delete Graphics;
// Remove the application instance.
        UnregisterClass(ClassName, Instance);
        Instance = NULL;
return;
}







bool LOOP_GAME(){
MSG msg;

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

        switch ( msg.message){
            case WM_QUIT:
                 return false; 
              break;
        }
		
return true;
}


void CLS(){
         d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
         d3ddev->BeginScene();    // begins the 3D scene
}



void SYNC(){
        d3ddev->EndScene();    // ends the 3D scene
        d3ddev->Present(NULL, NULL, NULL, NULL);    // displays the created frame
}


void SetActiveWindow(DXWindow window){
        SCREEN = &window;
}




//====================================================================================================================================
//________________________________________________ DIRECT 3D CODE ____________________________________________________________________

// this is the function used to render a single frame

void render_frame(void)
{
    // clear the window to a deep blue
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
    d3ddev->BeginScene();    // begins the 3D scene

    // do 3D rendering on the back buffer here

    d3ddev->EndScene();    // ends the 3D scene
    d3ddev->Present(NULL, NULL, NULL, NULL);    // displays the created frame
}

void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D

    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

void cleanD3D(void)
{
    
    v_buffer->Release(); 
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}




//====================================================================================================================================
//________________________________________________ DIRECT 2D CODE ____________________________________________________________________


using namespace D2D1;

Graphics2D::~Graphics2D(){}


Graphics2D::Graphics2D():
    Factory( NULL),
    RenderTarget(NULL){
}



bool Graphics2D::Init(HWND wndhandle)
{

  HRESULT res =  D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &Factory);
  if(res != S_OK) return false;

  RECT rect;

  GetClientRect(wndhandle, &rect);

  res = Factory->CreateHwndRenderTarget(
                 RenderTargetProperties(),
                 HwndRenderTargetProperties(
                                            wndhandle, 
                                            SizeU(rect.right, rect.bottom)
                                            ), 
                           &RenderTarget);
                 
   if(res != S_OK) return false;
}



void Graphics2D::DrawCircle(int x,int y, float radius)
{
        ID2D1SolidColorBrush *brush;

        RenderTarget->CreateSolidColorBrush( ColorF(1,0,0,1), &brush);
        RenderTarget->DrawEllipse(Ellipse(Point2F(x,y),radius,radius), brush, 3.0f);

        brush->Release();
}
