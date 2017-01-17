
// Project Includes
#include "Stdafx.h"
#include "BaseWindow.h"

// Common Lib Includes
#include "Exception.h"

// Standard Includes
#include <sstream>

//-----------------------------------------------------------------------------
namespace Common
{

//-----------------------------------------------------------------------------
BaseWindow::BaseWindow()
   :
   m_style(0),
   m_extendedStyle(0),
   m_className(L"BaseWindow"),
   m_title(L""),
   m_hwnd(NULL),
   m_active(false),
   m_maximized(false),
   m_minimized(false),
   m_sizing(false)
{
   m_wndclass.cbSize        = sizeof(m_wndclass);
   m_wndclass.style         = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;;
   m_wndclass.lpfnWndProc   = BaseWndProc;
   m_wndclass.cbClsExtra    = 0;
   m_wndclass.cbWndExtra    = 0;
   m_wndclass.hInstance     = NULL; 
   m_wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
   m_wndclass.hIconSm       = LoadIcon(NULL,IDI_APPLICATION);
   m_wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
   m_wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
   m_wndclass.lpszMenuName  = NULL;
   m_wndclass.hIconSm       = NULL;
}

//-----------------------------------------------------------------------------
BaseWindow::~BaseWindow()
{
}

//-----------------------------------------------------------------------------
HWND BaseWindow::Init(HINSTANCE instance, HWND parent, HMENU menu, int x, int y, int width, int height)
{
   m_wndclass.lpszClassName = m_className.c_str();
   m_wndclass.hInstance     = instance;

   // If this window class has been already registered, this call will fail
   if( !RegisterClassEx(&m_wndclass) )
   {
      throw Exception(__FILE__, __LINE__, "Failed to register BaseWindow class with OS");
   }

   m_hwnd = CreateWindowEx(m_extendedStyle,
                           m_className.c_str(),
                           m_title.c_str(),
                           m_style, 
                           x,
                           y,
                           width,
                           height,
                           parent,
                           menu,
                           instance,
                           static_cast<void*>(this));

   if( !m_hwnd )
   {
      DWORD err = GetLastError();
      throw Exception(__FILE__, __LINE__, "Failed to create window");
   }

   return m_hwnd;
}

//-----------------------------------------------------------------------------
int BaseWindow::Run()
{
   // Check if the window has been created
   if( !m_hwnd )
   {
      throw Exception(__FILE__, __LINE__, "Window has not yet been created.");
   }

   ShowWindow(m_hwnd, SW_SHOWNORMAL);
   m_active = true;

   // Process window messages until the application is exited
   MSG msg;                         // Windows message 

   while(true)
   {
      if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
         if(msg.message == WM_QUIT)
         {
            break;
         }

         TranslateMessage(&msg);		// Translate any accelerator keys
         DispatchMessage(&msg);		// Send the message to event handler
      }
   }

   return(static_cast<int>(msg.wParam));
}

//-----------------------------------------------------------------------------
LRESULT CALLBACK BaseWindow::BaseWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
   if( message == WM_NCCREATE )
   {
      // A pointer to the object owning this windows is passed in the CREATESTRUCT
      // Store it in the window
      LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lparam);
      SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
   }
    
   // Retrieve a pointer to the object owning this window
   BaseWindow * obj = reinterpret_cast<BaseWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

   // Pass the message to derived classes
   bool    callDefWndProc = true;
   LRESULT result         = 0;

   if( obj )
   {
      result = obj->WindowProc(hwnd, message, wparam, lparam, callDefWndProc);
   }

   if( callDefWndProc )
   {
      return DefWindowProc(hwnd, message, wparam, lparam);
   }
   else
   {
      return result;
   }
}

//-----------------------------------------------------------------------------
LRESULT BaseWindow::WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, bool & callDefWndProc)
{
   // This may be overridden by derived classes to process messages   
   switch( message )
   {
      case WM_ENTERSIZEMOVE:
      {
         // Halt while the app is sizing or moving
         m_active = false;
         m_sizing = true;
         
         callDefWndProc = true;
         return 0;
      }

      case WM_SIZE:
      {
         if( wparam == SIZE_MINIMIZED )
         {
            m_active    = false;
            m_minimized = true;
            m_maximized = false;
         }
         else
         {
            RECT currentClientRect;
            GetClientRect(m_hwnd, &currentClientRect);

            if( currentClientRect.top == 0 && currentClientRect.bottom == 0 )
            {
               // Rapidly clicking the task bar to minimize and restore a window
               // can cause a WM_SIZE message with SIZE_RESTORED when 
               // the window has actually become minimized due to rapid change
               // so just ignore this message
            }
            else if( wparam == SIZE_MAXIMIZED )
            {
               if( m_minimized )
               {
                  m_active    = true;
               }
               
               m_minimized = false;
               m_maximized = true;
            }
            else if( wparam == SIZE_RESTORED )
            {
               
               if( m_maximized )
               {
                  m_maximized = false;
               }
               else if( m_minimized )
               {
                  m_active    = true;
                  m_minimized = false;
               }
               else if( m_sizing )
               {
                  // If we're neither maximized nor minimized, the window size is changing because the user is dragging the window edges.
                  // In this case, we wait until the user stops dragging, and a WM_EXITSIZEMOVE message comes.
               }
               else
               {
                  // This WM_SIZE come from resizing the window via an API like SetWindowPos()
               }
            }
         }

         callDefWndProc = false;
         return 0;
      }

      case WM_EXITSIZEMOVE:
      {
         m_active = true;
         m_sizing = false;
         
         callDefWndProc = true;
         return 0;
      }

      case WM_DESTROY:
      {
         PostQuitMessage(0);

         callDefWndProc = false;
         return 0;
      }

      default:
      {
         callDefWndProc = true;
         return 0;
      }
   }
}

//-----------------------------------------------------------------------------
} // namespace common_lib_cpisz

