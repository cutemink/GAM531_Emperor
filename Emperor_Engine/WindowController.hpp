#ifndef __EMP_WINDOW_CONTROLLER_HPP__
#define __EMP_WINDOW_CONTROLLER_HPP__

#include "Managers.hpp"
#include "iWindow.hpp"

namespace Emperor
   {

   class WindowController
      {
      private:
         static WindowManager winMan;
      protected:
      public:
         static iWindow* createWindow() {return new Window();}
         static ArrayList<MessagePackage> retrieveWindowMessages() 
            {return ArrayList<MessagePackage>();}
      };

   }

#endif