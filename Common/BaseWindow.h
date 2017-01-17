#pragma once

// Project Includes
#include "CommonLib.h"

// Windows Includes
#include <windows.h>

// Standard Includes
#include <string>
#include <map>

//-----------------------------------------------------------------------------
// Disable compiler warning about exporting template instantiations from DLL
// See MSDN
// It is OK as long we are only suppressing warnings about template instances that have also been instantiated
// by clients of the DLL.
// For example: As long as the client uses std::vector<int> for example, we can too
// The same goes for the Boost Library
#pragma warning( push )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )

//------------------------------------------------------------------------------
namespace Common
{

//----------------------------------------------------------------------------------------------------------------------
// Enable you to make windows as class instances. The Windows API is so C orientated that a little work needed to be done
// to give you your own overidable windows procedure. In the base class here, the windows messages are routed to a virtual
// WinProc where derived classes may intercept and handle messages. If a message is not handled, it is left to the base
// windows procedure.
//
class COMMON_API BaseWindow
{
public:

   /** 
   * Constructor
   *
   * Sets up the attributes used to create a window
   * Derived classes should set window style here, after calling the base constructor
   **/
   BaseWindow();

   /**
   * Destructor
   **/
   virtual ~BaseWindow();

   /**
   * Creates the window
   *
   * @param instance - instance of the application that owns the window
   * @param menu - handle to a menu to attach to the window, this may be NULL
   * @param x - x coord of the top left of the window
   * @param y - y coord of the top left of the window
   * @param width - desired width of the window
   * @param height - desired height of the window
   *
   * @return - handle to the window that was crteated
   *
   * @throws BaseException - if there was a problem creating the window
   **/
   HWND Init(HINSTANCE instance, HWND parent, HMENU menu, int x, int y, int width, int height);
   
   /**
   * Runs a loop that dispatches window messages until a quit message is received
   * Derived classes should override this method if anything but window messages needs to be processed
   *
   * @throws BaseException - if the window has not yet been created
   **/
   virtual int Run();

protected:
   
   /** 
   * The windows message procedure for the base window
   *
   * This procedure will foward window messages to the WindowProc of the class instance that created the window
   *
   * @param hwnd - handle to the window to whom the message was sent
   * @param message - the message sent to the window
   * @param lparam - additional message information
   * @param wparam - additional message information
   *
   * @return LRESULT - result of the message processing, depends on the message sent
   */
   static LRESULT CALLBACK BaseWndProc(HWND, UINT, WPARAM, LPARAM);

   /**
   * Windows message procedure for derived classes
   *
   * Derived classes should override this method to process any window message they are interested in
   *
   * @param hwnd - handle to the window to whom the message was sent
   * @param message - the message sent to the window
   * @param lparam - additional message information
   * @param wparam - additional message information
   * @param callDefWndProc OUT - Whether or not the message should be passed to the default window procedure after this method returns
   *
   * @return LRESULT - result of the message processing, depends on the message sent
   **/
   virtual LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, bool & callDefWndProc);


   WNDCLASSEX   m_wndclass;      // Describes the window being created
   DWORD        m_style;         // Style of the window
   DWORD        m_extendedStyle; // Extended style of the window
   std::wstring m_className;     // Class name for the instance of the window
   std::wstring m_title;         // Title for the window

   HWND         m_hwnd;          // Handle to the window
   bool         m_active;        // Is the window active
   bool         m_maximized;     // Is the window maximized
   bool         m_minimized;     // Is the window minimized
   bool         m_sizing;        // Is the window in the middle of resizing
};

//----------------------------------------------------------------------------------------------------------------------
} // End namespace
