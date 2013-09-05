#ifndef __EMP_ENGINE_HPP__
#define __EMP_ENGINE_HPP__

#include "iEngine.hpp"
#include "SceneController.hpp"
#include "ResourceController.hpp"
#include "Device.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Engine : public iEngine , public Singleton<Engine<RS>>
      {
      private:
         friend iEngine* createEngine(RenderSystem);
         friend void releaseEngine(iEngine*);

         bool fullScreen;

         //Controllers
         SceneController<RS> sCont;
         ResourceController<RS> rCont;

         //Devices
         Device<RS> dev;
      protected:

         Engine() : fullScreen(false) {}
         virtual ~Engine() {}
      public:
         void initialize();
         void release();

         void activateDevice(iWindow*);
         void render();

         iSceneController* getSceneController() {return &sCont;}
         iResourceController* getResourceController() {return &rCont;}

         void setFullScreen(bool);
         bool isFullScreen() {return fullScreen;}

         Device<RS>& _getPlatformDevice() {return dev;}
      };

   template <RenderSystem RS>
   void _renderFromVertex(uint32 size);

   template <RenderSystem RS>
   void _renderFromIndex(uint32 size);

   }

#endif