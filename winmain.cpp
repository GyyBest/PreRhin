/********************************************************************
         @filename:  winmain.cpp
         @author:    ChenYang
         @date:      2014/11/18   20:02
         @brief:     
 ********************************************************************/

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "prerhin.h"
#include "vector3.h"

bool exiting = false;
long windowWidth = 800;
long windowHeight = 600;
long windowBits = 32;
bool fullscreen = false;
int x, y;
bool lBtnDn = false;
Vector3 vec;
HDC hDC;

Rhin *kGLRender = NULL;

void setupPixelFormat(HDC hDC)
{
    int pixelFormat;

    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), // size
        1,                              // version
        PFD_SUPPORT_OPENGL |            // OpenGL window
        PFD_DRAW_TO_WINDOW |            // render to window
        PFD_DOUBLEBUFFER,               // support double buffering
        PFD_TYPE_RGBA,                  // color type
        32,                             // preferred color depth
        0, 0, 0, 0, 0, 0,               // color bits (ignored)
        0,                              // no alpha buffer
        0,                              // alpha bits (ignored)
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits (ignored)                   
        16,                             // depth buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffers
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // no layer, visible, damage masks
    };
    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HGLRC hRC; // rendering context
    static HDC hDC;
    int width, height;
    
    switch (msg) {
        case WM_CREATE: {   // window creation
            hDC = GetDC(hwnd);  // Get handle of the window you will draw
            //kHdc = hDC;
            setupPixelFormat(hDC);
            hRC = wglCreateContext(hDC);
            wglMakeCurrent(hDC, hRC);
            break;
            }
                        
        case WM_CLOSE:      // window is closing
        case WM_DESTROY:    // window is destroy
        case WM_QUIT: {
            wglMakeCurrent(hDC, NULL);
            wglDeleteContext(hRC);
            PostQuitMessage(0);
            break;
        }

        case WM_SIZE: {
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            //kGLRender->setupProjection(width, height);
            kGLRender->reshape(width, height);
            break;
        }

        case WM_ACTIVATEAPP: // activate app
            break;

        case WM_PAINT: {   // paint
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_LBUTTONDOWN: {       // left mouse button
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            kGLRender->leftButtonDown(x, y);
            lBtnDn = true;
            break;
        }
            
        case WM_RBUTTONDOWN: {       // right mouse button
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            vec = kGLRender->getScreenPos(x, y);
            kGLRender->drawVoxel(vec);
            break;
        }

        case WM_MOUSEMOVE: {         // mouse movement
            if (lBtnDn) {       // left button is pressed and mouse move
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                kGLRender->mouseMove(x, y);
            }
            break;
        }
        case WM_LBUTTONUP: {          // left button release
            lBtnDn = false;
        }
            break;

        case WM_RBUTTONUP:          // right button release
            break;

        case WM_KEYUP:
            break;

        case WM_KEYDOWN: {
            int fwKeys;
            LPARAM keyData;
            fwKeys = (int)wParam;    // virtual-key code 
            keyData = lParam;          // key data 

            switch(fwKeys) {
                case VK_ESCAPE: {
                    PostQuitMessage(0);
                    break;
                }
                default:
                    break;
            }
            break;
        }

        default:
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX windowClass; // window class
    HWND hwnd;              // window handle
    MSG msg;                // message
    DWORD dwExStyle;        // window extended style
    DWORD dwStyle;          // window style
    RECT windowRect;

    kGLRender = new Rhin();

    windowRect.left = (long)0;  // set left value to 0
    windowRect.right = (long)windowWidth;   // set right value to requested
    windowRect.top = (long)0;   // set top value to 0
    windowRect.bottom = (long)windowHeight; // set bottom value to requested
    
    // fill out the window class structure
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = "MyClass";
    windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

    if (!RegisterClassEx(&windowClass))
        MessageBox(NULL, "Error to register window!", "Error", MB_OK);

    if (fullscreen) {               // fullscreen ?
        DEVMODE dmScreenSettings;   // device mode
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = windowWidth;  // screen width
        dmScreenSettings.dmPelsHeight = windowHeight; // screen height
        dmScreenSettings.dmBitsPerPel = windowBits;  // bits per pixel
        dmScreenSettings.dmFields = DM_BITSPERPEL |
            DM_PELSWIDTH | DM_PELSHEIGHT;
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) !=
            DISP_CHANGE_SUCCESSFUL) {
                // setting display mode failed, switch to windowed
                MessageBox(NULL, "Display mode failed", NULL, MB_OK);
                fullscreen = false;
        }
    }

    if (fullscreen) {           // are we still in fullscreen mode ?
        dwExStyle = WS_EX_APPWINDOW;    // window extended style
        dwStyle = WS_POPUP;             // window style
        ShowCursor(false);             // hide mouse pointer
    } else {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW;
    }
    
    // adjust window to true requested size
    AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle);

    hwnd = CreateWindowEx(NULL,     // extended style
                          "MyClass", // class name
                          "The OpenGL Window Application", // app name
                          dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                          0, 0,     // x, y coordinate
                          windowRect.right - windowRect.left, // width, height
                          windowRect.bottom - windowRect.top,
                          NULL,     // handle to parent
                          NULL,     // handle to menu
                          hInstance,    // application instance
                          NULL);    // no extra params
    hDC = GetDC(hwnd);

    if (!hwnd)
        MessageBox(NULL, "Error to create window!", "Error", MB_OK);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    kGLRender->init();

    while (!exiting) {
        //kGLRender->prepare(0.0f);
        kGLRender->render();
        SwapBuffers(hDC);

        while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
            if (!GetMessage(&msg, NULL, 0, 0)) {
                exiting = true;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete kGLRender;

    if (fullscreen) {
        ChangeDisplaySettings(NULL, 0); // if so switch back to the desktop
        ShowCursor(true);               // show mouse pointer
    }
    return (int)msg.wParam;
}