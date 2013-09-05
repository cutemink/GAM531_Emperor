#include "Engine.hpp"
#include "ResourceController.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   void Engine<RS>::initialize()
      {
      sCont.nodMan.init();
      rCont.shdMan.init();
      rCont.texMan.init();
      rCont.mshMan.init();
      }

   template <RenderSystem RS>
   void Engine<RS>::release()
      {

      }


   template <RenderSystem RS>
   void Engine<RS>::render()
      {
      //update Node positions
      sCont.nodMan.updateValues();


      //being rendering
      if(dev.isActive())
         {
         dev.renderStart();

         //render for each active camera
         sCont.camMan.prepareLoop();
         while(sCont.camMan.bindNext())
            {
            sCont.nodMan._updateBuffers();
            sCont.actMan.prepareLoop();
            while(sCont.actMan.bindNext())
               {
               //potentially pointless, will need a light cap to make use of this
               sCont.lgtMan.orderLights(
                  getPosition(
                     NO_VIRT(Node<RS>,sCont.actMan.getCurrent()->getNode(), _getAbs)()
                  )
               );
               sCont.actMan.render();
               }
            }
         dev.renderEnd();
         }
      }

   template <RenderSystem RS>
   void Engine<RS>::activateDevice(iWindow* win)
      {
      if(dev.isActive())
         dev.release();
      dev.init((Window*)win);
      }

   template <RenderSystem RS>
   void Engine<RS>::setFullScreen(bool b)
      {
      if(b != fullScreen)
         {
         dev.setFullScreen(b);
         fullScreen = b;
         }
      }

   iEngine* createEngine(RenderSystem t)
      {
      if(t == RS_DX11)
#if EMP_USE_DIRECTX
         return new Engine<RS_DX11>();
#else
         return nullptr;
#endif
      else
#if EMP_USE_OPENGL
         return new Engine<RS_GL43>();
#else
         return nullptr;
#endif
      }

   void releaseEngine(iEngine* a)
      {
      delete a;
      }

   template <RenderSystem RS>
   void _renderFromVertex(uint32 size)
      {
      Engine<RS>::getPtr()->_getPlatformDevice().draw(size, 0);
      }

   template <RenderSystem RS>
   void _renderFromIndex(uint32 size)
      {
      Engine<RS>::getPtr()->_getPlatformDevice().drawIndexed(size, 0, 0);
      }

#if (EMP_USE_OPENGL == ON)
   template class Engine<RS_GL43>;
   template void _renderFromVertex<RS_GL43>(uint32);
   template void _renderFromIndex<RS_GL43>(uint32);
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Engine<RS_DX11>;
   template void _renderFromVertex<RS_DX11>(uint32);
   template void _renderFromIndex<RS_DX11>(uint32);
#endif

   }