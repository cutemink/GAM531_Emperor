#ifndef __EMP_I_TEXTURE_HPP__
#define __EMP_I_TEXTURE_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   class iTexture
      {
      private:
      protected:
         iTexture() {}
         virtual ~iTexture() {}
      public:
         virtual void loadFile(const String& fileName) = 0;
         virtual void destroy() = 0;
      };

   class iTexture1D
      {
      private:
      protected:
         iTexture1D() {}
         virtual ~iTexture1D() {}
      public:
         virtual void initCustom(uint32 size, StructureFormat format) = 0;
         virtual void fill(byte*,uint32) = 0;
      };

   class iTexture2D
      {
      private:
      protected:
         iTexture2D() {}
         virtual ~iTexture2D() {}
      public:
         virtual void initCustom(uint32 width, uint32 height, StructureFormat format) = 0;
         virtual void fill(byte*,uint32) = 0;
      };

   class iTexture3D
      {
      private:
      protected:
         iTexture3D() {}
         virtual ~iTexture3D() {}
      public:
         virtual void initCustom(uint32 width, uint32 height, uint32 depth, StructureFormat format) = 0;
         virtual void fill(byte*,uint32) = 0;
      };

   }

#endif