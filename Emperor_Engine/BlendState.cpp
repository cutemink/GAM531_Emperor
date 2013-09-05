#include "BlendState.hpp"
#include "Managers.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   void BlendState<RS>::destroy()
      {
      BlendStateManager<RS>::getPtr()->removeResource(this);
      delete this;
      }


   template <RenderSystem RS>
   void BlendState<RS>::setDescription(const BlendStateDescription& desc, uint32 rend)
      {
      dList[rend] = desc;
      finalized = false;
      }

   template <RenderSystem RS>
   void BlendState<RS>::bindBlendState() const
      {
      if(!finalized)
         {
         LOG("Cannot bind unfinalized blend state at 0x" << this << "!");
         return;
         }

      bs.bindBlendState();
      }

   template <RenderSystem RS>
   void BlendState<RS>::finalize() 
      {
      try
         {
         bs.finalize(dList, independantBlend, alphaToCoverage);
         finalized = true;
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

#if (EMP_USE_OPENGL == ON)
   template class BlendState<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class BlendState<RS_DX11>;
#endif
   }
