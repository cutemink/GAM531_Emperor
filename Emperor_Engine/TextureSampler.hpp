#ifndef __EMP_TEXTURE_SAMPLER_HPP__
#define __EMP_TEXTURE_SAMPLER_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "APITextureSampler.hpp"
#include "iTextureSampler.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class TextureSampler : public iTextureSampler
      {
      private:
         APITextureSampler<RS> sampler;

         TextureFilter filter;
         TextureAddressMode uAddressMode;
         TextureAddressMode vAddressMode;
         TextureAddressMode wAddressMode;
         float mipLODBias;
         uint32 maxAnisotropy;
         TextureComparisonMethod comparisonMethod;
         Color borderColor;
         float minLOD;
         float maxLOD;

      protected:
         TextureSampler(const TextureSampler& a) {}
         TextureSampler& operator=(const TextureSampler& a) {return *this;}
         ~TextureSampler() {}
      public:
         TextureSampler() : uAddressMode(TA_WRAP), vAddressMode(TA_WRAP),
            wAddressMode(TA_WRAP), maxAnisotropy(1), comparisonMethod(TC_ALWAYS),
            borderColor(Color(0.0f, 0.0f, 0.0f, 0.0f)), minLOD(0.0f), maxLOD(0.0f), 
            mipLODBias(0.0f) {}

         void build();

         void destroy();

         void bindToVertex(uint32 slot) const;
         void bindToFragment(uint32 slot) const;


         //setters and getters
         const TextureFilter& getFilter() const {return filter;}
         void setFilter(const TextureFilter& t) {filter = t;}

         TextureAddressMode getAddressModeU() const {return uAddressMode;}
         void setAddressModeU(TextureAddressMode t) {uAddressMode = t;}

         TextureAddressMode getAddressModeV() const {return vAddressMode;}
         void setAddressModeV(TextureAddressMode t) {vAddressMode = t;}

         TextureAddressMode getAddressModeW() const {return wAddressMode;}
         void setAddressModeW(TextureAddressMode t) {wAddressMode = t;}

         float getMipLODBias() const {return mipLODBias;}
         void setMipLODBias(float t) {mipLODBias = t;}

         uint32 getMaxAnisotropy() const {return maxAnisotropy;}
         void setMaxAnisotropy(uint32 t) {maxAnisotropy = t;}

         TextureComparisonMethod getComparisonMethod() const {return comparisonMethod;}
         void setComparisonMethod(TextureComparisonMethod t) {comparisonMethod = t;}

         const Color& getBorderColor() const {return borderColor;}
         void setBorderColor(const Color& t) {borderColor = t;}

         float getMinLOD() const {return minLOD;}
         void setMinLOD(float t) {minLOD = t;}

         float getMaxLOD() const {return maxLOD;}
         void setMaxLOD(float t) {maxLOD = t;}
      };
   }

#endif