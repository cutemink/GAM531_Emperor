#include "APITextureSampler.hpp"
#include "Engine.hpp"
#include "APITranslations.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   APITextureSampler<RS_DX11>::~APITextureSampler()
      {
      if(sampler)
         sampler->Release();
      }

   void APITextureSampler<RS_DX11>::bindToVertex(uint32 slot) const
      {

      }

   void APITextureSampler<RS_DX11>::bindToFragment(uint32 slot) const
      {

      }

   void APITextureSampler<RS_DX11>::build(const TextureFilter& tf, TextureAddressMode u, 
      TextureAddressMode v, TextureAddressMode w, 
      float mlb, uint32 ma, TextureComparisonMethod cm, 
      const Color& bc, float nl, float xl)
      {

      }
#endif

#if EMP_USE_OPENGL
   APITextureSampler<RS_GL43>::~APITextureSampler()
      {

      }

   void APITextureSampler<RS_GL43>::build(const TextureFilter& tf, TextureAddressMode u, 
      TextureAddressMode v, TextureAddressMode w, float mlb, uint32 ma, TextureComparisonMethod cm, 
      const Color& bc, float nl, float xl)
      {

      }

   void APITextureSampler<RS_GL43>::bindToVertex(uint32 slot) const
      {

      }

   void APITextureSampler<RS_GL43>::bindToFragment(uint32 slot) const
      {

      }
#endif
   }
