#pragma once

// Project Includes
#include "CommonLib.h"

// Windows Includes
#include <windows.h>

// Standard Includes
#include <string>

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

//----------------------------------------------------------------------------------------------------------------------
namespace Common
{

//----------------------------------------------------------------------------------------------------------------------
class COMMON_API BaseModalDialog
{
public:

   /** 
   * Constructor
   **/
   BaseModalDialog();

   /**
   * Destructor
   **/
   virtual ~BaseModalDialog();

protected:
   
   /**
   * Creates the dialog
   *
   * @param instance - instance of the application that owns the dialog
   * @param templateName - name of an included dialog template resource
   * @param parent - handle to the parent window of the dialog
   *
   * @return int - result from EndDialog when the dialog exits
   *
   **/
   INT_PTR Init(HINSTANCE instance, const wchar_t * templateName, HWND parent);

   /**
   * Initializes all the controls in the dialog
   **/
   virtual void InitComponents() = 0;

   /** 
   * The dialog message procedure for the base dialog
   *
   * This procedure will foward dialog messages to the ModalDlgProc of the class instance that created the dialog
   *
   * @param hwnd - handle to the dialog to whom the message was sent
   * @param message - the message sent to the dialog
   * @param lparam - additional message information
   * @param wparam - additional message information
   *
   * @return BOOL - TRUE if it was handled, otherwise FALSE
   */
   static INT_PTR CALLBACK BaseModalDlgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

   /**
   * Dialog message procedure for derived classes
   *
   * Derived classes should override this method to process any dialog message they are interested in
   *
   * @param hwnd - handle to the dialog to whom the message was sent
   * @param message - the message sent to the dialog
   * @param lparam - additional message information
   * @param wparam - additional message information
   *
   * @return LRESULT - TRUE if the message was handled, otherwise false.
   **/
   virtual INT_PTR CALLBACK ModalDlgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


   HWND m_hwnd;            // Handle to the dialog
};

//----------------------------------------------------------------------------------------------------------------------
} // End namespace