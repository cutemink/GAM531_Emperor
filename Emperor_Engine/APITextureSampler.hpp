#ifndef __EMP_API_TEXTURE_SAMPLER_HPP__
#define __EMP_API_TEXTURE_SAMPLER_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class APITextureSampler{};

#if EMP_USE_DIRECTX
   template <>
   class APITextureSampler<RS_DX11>
      {
      private:
         ID3D11SamplerState* sampler;
      protected:
      public:
         APITextureSampler() : sampler(0) {}
         virtual ~APITextureSampler();

         void build(const TextureFilter&, TextureAddressMode, TextureAddressMode,
            TextureAddressMode, float, uint32, TextureComparisonMethod, const Color&,
            float, float);
         void bindToVertex(uint32 slot) const;
         void bindToFragment(uint32 slot) const;
      };
#endif

#if EMP_USE_OPENGL
   template<>
   class APITextureSampler<RS_GL43>
      {
      private:
         GLuint samplerID;
      protected:
      public:
         APITextureSampler() : samplerID(0) {}
         virtual ~APITextureSampler();

         void build(const TextureFilter&, TextureAddressMode, TextureAddressMode,
            TextureAddressMode, float, uint32, TextureComparisonMethod, const Color&,
            float, float);
         void bindToVertex(uint32 slot) const;
         void bindToFragment(uint32 slot) const;
      };
#endif
   }

#endif