#ifndef __EMP_I_ENGINE_HPP__
#define __EMP_I_ENGINE_HPP__

#include "Common.hpp"

#include "iResourceController.hpp"
#include "iSceneController.hpp"
#include "iWindow.hpp"

namespace Emperor
   {

   class iEngine
      {
      private:
         friend iEngine* createEngine(RenderSystem);
         friend void releaseEngine(iEngine*);
      protected:
         virtual ~iEngine() {}
      public:
         virtual void initialize() = 0;
         virtual void release() = 0;

         virtual void setFullScreen(bool) = 0;
         virtual bool isFullScreen() = 0;

         virtual void activateDevice(iWindow*) = 0;

         virtual iResourceController* getResourceController() = 0;
         virtual iSceneController* getSceneController() = 0;

         virtual void render() = 0;
      };

   iEngine* createEngine(RenderSystem);

   void releaseEngine(iEngine*);

   }

#endif