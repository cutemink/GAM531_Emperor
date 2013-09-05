#ifndef __EMP_TEXTURE_DX_HPP__
#define __EMP_TEXTURE_DX_HPP__

#include "Common.hpp"
#include "APITexture.hpp"
#include "TextureSampler.hpp"
#include "iTexture.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Texture : public iTexture
      {
      private:
      protected:
         APITexture<RS>* texture;
         ~Texture() {}
      public:
         Texture() : texture(new APITexture<RS>()) {}
         Texture(APITexture<RS>* a) : texture(a) {}

         void loadFile(const String&);
         void destroy();


         void bindToVertex(uint32 slot) const;
         void bindToFragment(uint32 slot) const;
      };

   template <RenderSystem RS>
   class Texture1D : public iTexture1D,  public Texture<RS>
      {
      private:
         APITexture1D<RS> tex1d; 
         uint32 texSize;
      protected:
      public:
         Texture1D() : texSize(0) {texture = (APITexture<RS>*)&tex1d;}
         void initCustom(uint32 size, StructureFormat format);
         void fill(byte*,uint32);
      };

   template <RenderSystem RS>
   class Texture2D : public iTexture2D,   public Texture<RS>
      {
      private:
         APITexture2D<RS> tex2d; 
         uint32 texSize;
      protected:
      public:
         Texture2D() : texSize(0) {texture = (APITexture<RS>*)&tex2d;}
         void initCustom(uint32 width, uint32 height, StructureFormat format);
         void fill(byte*,uint32);
      };

   template <RenderSystem RS>
   class Texture3D : public iTexture3D,   public Texture<RS>
      {
      private:
         APITexture3D<RS> tex3d; 
         uint32 texSize;
      protected:
      public:
         Texture3D() : texSize(0) {texture = (APITexture<RS>*)&tex3d;}
         void initCustom(uint32 width, uint32 height, uint32 depth, StructureFormat format);
         void fill(byte*,uint32);
      };
   }



#endif