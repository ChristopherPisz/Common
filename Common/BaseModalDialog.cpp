
// Project Includes
#include "Stdafx.h"
#include "BaseModalDialog.h"

// Common Lib Includes
#include "Exception.h"

// Standard Includes
#include <sstream>

//-----------------------------------------------------------------------------
namespace Common
{

//-----------------------------------------------------------------------------
BaseModalDialog::BaseModalDialog()
   :
   m_hwnd(NULL)
{
}

//-----------------------------------------------------------------------------
BaseModalDialog::~BaseModalDialog()
{
}

//-----------------------------------------------------------------------------
INT_PTR BaseModalDialog::Init(HINSTANCE instance, const wchar_t * templateName, HWND parent)
{
   return DialogBoxParam(instance, 
                         templateName,
                         parent,
                         BaseModalDlgProc,
                         reinterpret_cast<LPARAM>(this));
}

//-----------------------------------------------------------------------------
INT_PTR CALLBACK BaseModalDialog::BaseModalDlgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
   if( message == WM_INITDIALOG )
   {
      // Store a pointer to the object owning this dialog
      BaseModalDialog * obj = reinterpret_cast<BaseModalDialog *>(lparam);
      SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(obj));

      // Store a handle to the dialog
      obj->m_hwnd = hwnd;

      // Initialize the dialogs components
      obj->InitComponents();
   }

   // Retrieve a pointer to the object owning this dialog
   BaseModalDialog * obj = reinterpret_cast<BaseModalDialog *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

   // Pass the message to derived classes
   INT_PTR result = false;

   if( obj )
   {
      result = obj->ModalDlgProc(hwnd, message, wparam, lparam);
   }
   
   return result;
}

//-----------------------------------------------------------------------------
INT_PTR CALLBACK BaseModalDialog::ModalDlgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
   return false;
}

//-----------------------------------------------------------------------------
} // End namespace


