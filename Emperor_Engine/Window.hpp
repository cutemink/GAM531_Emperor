#ifndef __EMP_WINDOW_MS_HPP__
#define __EMP_WINDOW_MS_HPP__

#include "Common.hpp"
#include "Vector.hpp"
#include "Types.hpp"
#include "iWindow.hpp"

namespace Emperor
   {
   class Window : public iWindow
      {
      private:
         HWND winHnd;
         HINSTANCE appInst;
         WINDOWPLACEMENT winPlac;
         WindowClass windowClass;
         String windowName;
         uint32 windowStyle;
         Vector<int,2> position;
         Vector<int,2> size;
         ArrayList<WindowMessage> messages;


      protected:
         virtual ~Window() {}
      public:
         Window() : winHnd(0), appInst(0), windowStyle(0), position(Coord(0,0)), 
            size(Coord(0,0)) {}

         void init();
         void destroy();

         void setName(const String& name);
         const String& getName() {return windowName;}

         void setClass(const WindowClass& cl);
         const WindowClass& getClass() {return windowClass;}

         void setPosition(const Vector<int,2>& pos);
         const Vector<int,2>& getPosition() {return position;}

         void setSize(const Vector<int,2>& sz);
         const Vector<int,2>& getSize() {return size;}

         WindowID getWindowID() const {return winHnd;}

         void showWindow(bool a);

         void _processMessage();

         static LRESULT CALLBACK _windowProcess(HWND hWnd, UINT msg,
            WPARAM wParam, LPARAM lParam);

      };

   }

#endif