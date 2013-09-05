#include "TextureSampler.hpp"
#include "Managers.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   void TextureSampler<RS>::build()
      {
      try
         {
         sampler.build(filter, uAddressMode, vAddressMode, wAddressMode, mipLODBias, maxAnisotropy,
            comparisonMethod, borderColor, minLOD, maxLOD);
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());//not much else can be done here
         }
      }

   template <RenderSystem RS>
   void TextureSampler<RS>::destroy()
      {
      SamplerManager<RS>::getPtr()->removeResource(this);
      delete this;
      }

   template <RenderSystem RS>
   void TextureSampler<RS>::bindToVertex(uint32 slot) const
      {
      sampler.bindToVertex(slot);
      }

   template <RenderSystem RS>
   void TextureSampler<RS>::bindToFragment(uint32 slot) const
      {
      sampler.bindToFragment(slot);
      }

#if (EMP_USE_OPENGL == ON)
   template class TextureSampler<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class TextureSampler<RS_DX11>;
#endif
   }