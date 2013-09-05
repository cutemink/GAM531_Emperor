#ifndef __EMP_I_WINDOW_HPP__
#define __EMP_I_WINDOW_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {
   class iWindow
      {
      private:
      protected:
         iWindow() {}
         virtual ~iWindow() {}
      public:      
         virtual void init() = 0;
         virtual void destroy() = 0;

         virtual void setName(const String& name) = 0;
         virtual const String& getName() = 0;

         virtual void setClass(const WindowClass& cl) = 0;
         virtual const WindowClass& getClass() = 0;

         virtual void setPosition(const Vector<int,2>& pos) = 0;
         virtual const Vector<int,2>& getPosition() = 0;

         virtual void setSize(const Vector<int,2>& sz) = 0;
         virtual const Vector<int,2>& getSize() = 0;

         virtual WindowID getWindowID() const = 0;
      };
   }

#endif