// DirectX.cpp : Defines the entry point for the application.
#include "stdafx.h"
#include "DirectX.h"
#include "DXWindow.h"
#include <Iostream>
void init_graphics(void);




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{


    DXWindow wMain(0,0,640,480,L"Graphics Window");

    init_graphics();

	while(LOOP_GAME())
	{
        CLS();
                // select which vertex format we are using
        d3ddev->SetFVF(CUSTOMFVF);
        wMain.Graphics->BegineDraw();
        // select the vertex buffer to display
        d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
        wMain.Graphics->DrawCircle(100,100,50);
        
        // copy the vertex buffer to the back buffer
        d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

        wMain.Graphics->EndDraw();
       std::cout << " WTFDFFFF" << std::endl;
        SYNC();
	}
    //wMain.
}





void init_graphics(void)
{
    // create three vertices using the CUSTOMVERTEX struct built earlier
    
    CUSTOMVERTEX vertices[] =
    {
        { 320.0f, 50.0f, 0.5f,  1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 520.0f, 400.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 120.0f, 400.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };



// create the vertex and store the pointer into v_buffer, which is created globally
    d3ddev->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &v_buffer,
                               NULL);

    VOID* pVoid;    // the void pointer

    v_buffer->Lock(0, 0, (void**)&pVoid, 0);    // lock the vertex buffer
    memcpy(pVoid, vertices, sizeof(vertices));    // copy the vertices to the locked buffer
    v_buffer->Unlock();    // unlock the vertex buffer
}