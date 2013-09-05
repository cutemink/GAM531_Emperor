#include "Common.hpp"
#if EMP_USE_WINDOWS

#include "Window.hpp"
#include "Managers.hpp"

namespace Emperor
   {
   void Window::init()
      {

      }

   void Window::showWindow(bool a)
      {

      }

   void Window::destroy()
      {

      }

   void Window::setName(const String& name)
      {

      }

   void Window::setClass(const WindowClass& cl)
      { 
      windowClass = cl;
      WNDCLASS w; 
      w.style = 0;
      w.cbClsExtra = 0;
      w.cbWndExtra = 0;
      w.hIcon = 0;
      w.hCursor = 0;
      w.hbrBackground = 0;
      w.lpszMenuName = 0;
      w.lpfnWndProc = _windowProcess;
      w.hInstance = appInst;
      w.lpszClassName = cl.className.c_str();
      RegisterClass(&w);
      }

   void Window::setPosition(const Vector<int,2>& pos)
      {

      }

   void Window::setSize(const Vector<int,2>& sz)
      {

      }

   void Window::_processMessage()
      {

      }

   LRESULT CALLBACK Window::_windowProcess(HWND hWnd, UINT msg, WPARAM wParam,
      LPARAM lParam)
      {
      return 0;
      }
   }

#endif