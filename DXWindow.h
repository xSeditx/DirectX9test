#pragma once

#include<Windows.h>

#include<d2d1.h>
#include<d3d9.h>
#include<d3dx9.h>


#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
    float x, 
          y, 
          z, 
          rhw;      // from the D3DFVF_XYZRHW flag
    DWORD color;    // from the D3DFVF_DIFFUSE flag
};

extern LPDIRECT3D9 d3d;             // the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

// function prototypes
extern void initD3D(HWND hWnd);    // sets up and initializes Direct3D
extern void render_frame(void);    // renders a single frame
extern void cleanD3D(void);        // closes Direct3D and releases memory



class Graphics2D{
      
        ID2D1Factory             *Factory;
        ID2D1HwndRenderTarget    *RenderTarget;

public:
        Graphics2D();~Graphics2D();
      
        bool Init             (HWND wndhandle);
        void BegineDraw       ()                           { RenderTarget->BeginDraw();}
        void EndDraw          ()                           { RenderTarget->EndDraw()  ;}
        void DrawCircle       (int x,int y, float radius);
        void CLS              ();
        void SYNC             ();
};


class Graphics3D{
public:        
        IDirect3D9            *Interface;            // the pointer to our Direct3D interface
        IDirect3DDevice9      *Device;         // the pointer to the device class
        
        void Init_Direct3D    (HWND hWnd);    // sets up and initializes Direct3D
        void Render_Frame     ();             // renders a single frame
        void cleanD3D         ();             // closes Direct3D and releases memory
};

//
//LPDIRECT3D9

class DXWindow{
public: 
        DXWindow();~DXWindow();
        DXWindow::DXWindow(int x,int y, int h, int w,  LPCWSTR title);
    
    
        HINSTANCE   Instance;
        WNDCLASSEX  WINDOW_CLASS;
        LPCWSTR     ClassName;
    
    
        MSG Messages;
    
        HWND Handle;
        HDC DeviceContext;
    
        Graphics2D *Graphics;


//  DXDeviceContext;
         LPCWSTR Title;
        
        struct Position
        {
            int X,
                Y;
        }Position;
        struct Size
        {
            int Height,
                Width;
        }Size;
    
    
//  Inputs 
        struct Mouse
        {
                int X,
                    Y;
                
                float Speed,
                      Angle;
                struct Buttons{
                        bool Left,
                             Right;
                        int  Center;
                }Button;
        }Mouse;
    
        struct Keyboard
        {
                int Keys[500];
        }Keyboard;
    
    
        double FPS;

        float Get_SyncRate();
        void  Set_Sync_Rate();
    
        void  ShutdownWindows();
private: 
        float Sync_Rate;
};



extern DXWindow *SCREEN;

extern bool LOOP_GAME();
extern void CLS();
extern void SYNC();

extern void SetActiveWindow(DXWindow window);


extern  LPDIRECT3DVERTEXBUFFER9 v_buffer;







 //INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);