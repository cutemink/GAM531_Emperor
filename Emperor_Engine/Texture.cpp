#include "Texture.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   void Texture<RS>::loadFile(const String& s)
      {
      texture->loadFile(s);
      }

   template <RenderSystem RS>
   void Texture<RS>::destroy()
      {
      TextureManager<RS>::getPtr()->removeResource(this);
      delete this;
      }

   template <RenderSystem RS>
   void Texture<RS>::bindToVertex(uint32 slot) const
      {
      texture->bindToVertex(slot);
      }

   template <RenderSystem RS>
   void Texture<RS>::bindToFragment(uint32 slot) const
      {
      texture->bindToFragment(slot);
      }

   template <RenderSystem RS>
   void Texture1D<RS>::initCustom(uint32 size, StructureFormat format)
      {
      try
         {
         tex1d.init(size, format);
         texSize = size;
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void Texture1D<RS>::fill(byte* data, uint32 size)
      {
      try
         {
         if(texSize) //indicates successful init
            tex1d.fill(data, size);
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void Texture2D<RS>::initCustom(uint32 width, uint32 height, StructureFormat format)
      {
      try
         {
         tex2d.init(width, height, format);
         texSize = width * height;
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void Texture2D<RS>::fill(byte* data, uint32 size)
      {
      try
         {
         if(texSize) //indicates successful init
            tex2d.fill(data, size);
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void Texture3D<RS>::initCustom(uint32 width, uint32 height, uint32 depth, StructureFormat format)
      {
      try
         {
         tex3d.init(width, height, depth, format);
         texSize = width * height * depth;
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void Texture3D<RS>::fill(byte* data, uint32 size)
      {
      try
         {
         if(texSize) //indicates successful init
            tex3d.fill(data, size);
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

#if (EMP_USE_OPENGL == ON)
   template class Texture<RS_GL43>;
   template class Texture1D<RS_GL43>;
   template class Texture2D<RS_GL43>;
   template class Texture3D<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Texture<RS_DX11>;
   template class Texture1D<RS_DX11>;
   template class Texture2D<RS_DX11>;
   template class Texture3D<RS_DX11>;
#endif
   }