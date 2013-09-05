#include "APITexture.hpp"
#include "Engine.hpp"
#include "APITranslations.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   APITexture<RS_DX11>::~APITexture()
      {
      if(texture)
         texture->Release();
      }

   void APITexture<RS_DX11>::loadFile(const String& s)
      {

      }

   void APITexture<RS_DX11>::bindToVertex(uint32 slot) const
      {

      }

   void APITexture<RS_DX11>::bindToFragment(uint32 slot) const
      {

      }

   APITexture1D<RS_DX11>::~APITexture1D()
      {
      if(tex1d)
         tex1d->Release();
      }

   void APITexture1D<RS_DX11>::init(uint32 size, StructureFormat format)
      {

      }

   void APITexture1D<RS_DX11>::fill(byte* data, uint32 size)
      {

      }

   APITexture2D<RS_DX11>::~APITexture2D()
      {
      if(tex2d)
         tex2d->Release();
      }

   void APITexture2D<RS_DX11>::init(uint32 width, uint32 height, StructureFormat format)
      {

      }

   void APITexture2D<RS_DX11>::fill(byte* data, uint32 size)
      {

      }
   
   APITexture3D<RS_DX11>::~APITexture3D()
      {
      if(tex3d)
         tex3d->Release();
      }

   void APITexture3D<RS_DX11>::init(uint32 width, uint32 height, uint32 depth, StructureFormat format)
      {

      }

   void APITexture3D<RS_DX11>::fill(byte* data, uint32 size)
      {

      }
#endif

#if EMP_USE_OPENGL
   APITexture<RS_GL43>::~APITexture()
      {
      glDeleteTextures(1, &textureID);
      }

   void APITexture<RS_GL43>::loadFile(const String& fn)
      {
      /*
      int w, h, c;
      unsigned char* data = SOIL_load_image(fn.c_str(), &w, &h, &c, SOIL_LOAD_RGB);
      */

      }


   void APITexture<RS_GL43>::bindToVertex(uint32 ind) const
      {

      }

   void APITexture<RS_GL43>::bindToFragment(uint32 ind) const
      {

      }

   // size here is number of texels
   void APITexture1D<RS_GL43>::init(uint32 size, StructureFormat fmt)
      {

      }

   // size here is byte size
   void APITexture1D<RS_GL43>::fill(byte* data, uint32 size)
      {

      }

   void APITexture2D<RS_GL43>::init(uint32 width, uint32 height, StructureFormat fmt)
      {

      }

   void APITexture2D<RS_GL43>::fill(byte* data, uint32 size)
      {

      }

   void APITexture3D<RS_GL43>::init(uint32 width, uint32 height, uint32 depth, StructureFormat fmt)
      {

      }

   void APITexture3D<RS_GL43>::fill(byte* data, uint32 size)
      {

      }
#endif
   }
