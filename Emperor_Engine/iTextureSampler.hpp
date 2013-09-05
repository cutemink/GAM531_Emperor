#ifndef __EMP_I_TEXTURE_SAMPLER_HPP__
#define __EMP_I_TEXTURE_SAMPLER_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {
   class iTextureSampler
      {
      private:
      protected:
         iTextureSampler() {}
         virtual ~iTextureSampler() {}
      public:
         virtual void build() = 0;

         virtual void destroy() = 0;

         //setters and getters
         virtual const TextureFilter& getFilter() const = 0;
         virtual void setFilter(const TextureFilter& t) = 0;

         virtual TextureAddressMode getAddressModeU() const = 0;
         virtual void setAddressModeU(TextureAddressMode t) = 0;

         virtual TextureAddressMode getAddressModeV() const = 0;
         virtual void setAddressModeV(TextureAddressMode t) = 0;

         virtual TextureAddressMode getAddressModeW() const = 0;
         virtual void setAddressModeW(TextureAddressMode t) = 0;

         virtual float getMipLODBias() const = 0;
         virtual void setMipLODBias(float t) = 0;

         virtual uint32 getMaxAnisotropy() const = 0;
         virtual void setMaxAnisotropy(uint32 t) = 0;

         virtual TextureComparisonMethod getComparisonMethod() const = 0;
         virtual void setComparisonMethod(TextureComparisonMethod t) = 0;

         virtual const Color& getBorderColor() const = 0;
         virtual void setBorderColor(const Color& t) = 0;

         virtual float getMinLOD() const = 0;
         virtual void setMinLOD(float t) = 0;

         virtual float getMaxLOD() const = 0;
         virtual void setMaxLOD(float t) = 0;
      };

   }

#endif