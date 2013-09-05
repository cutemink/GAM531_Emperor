#ifndef __EMP_API_TEXTURE_HPP__
#define __EMP_API_TEXTURE_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class APITexture{};

   template <RenderSystem RS>
   class APITexture1D{};

   template <RenderSystem RS>
   class APITexture2D{};

   template <RenderSystem RS>
   class APITexture3D{};

#if EMP_USE_DIRECTX
   template <>
   class APITexture<RS_DX11>
      {
      private:
      protected:
         ID3D11ShaderResourceView* texture;
      public:
         APITexture() : texture(0) {}
         virtual ~APITexture();

         void loadFile(const String&);

         void bindToVertex(uint32 slot) const;
         void bindToFragment(uint32 slot) const;
      };

   template <>
   class APITexture1D<RS_DX11> : APITexture<RS_DX11>
      {
      private:
         ID3D11Texture1D* tex1d;
      protected:
      public:
         APITexture1D() : tex1d(0) {}
         virtual ~APITexture1D();

         void init(uint32, StructureFormat);
         void fill(byte*, uint32);
      };

   template <>
   class APITexture2D<RS_DX11> : APITexture<RS_DX11>
      {
      private:
         ID3D11Texture2D* tex2d;
      protected:
      public:
         APITexture2D() : tex2d(0) {}
         virtual ~APITexture2D();

         void init(uint32, uint32, StructureFormat);
         void fill(byte*, uint32);
      };

   template <>
   class APITexture3D<RS_DX11> : APITexture<RS_DX11>
      {
      private:
         ID3D11Texture3D* tex3d;
      protected:
      public:
         APITexture3D() : tex3d(0) {}
         virtual ~APITexture3D();

         void init(uint32, uint32, uint32, StructureFormat);
         void fill(byte*, uint32);
      };
#endif

#if EMP_USE_OPENGL
   template<>
   class APITexture<RS_GL43>
      {
      private:
      protected:
         GLuint textureID;
         GLint iFormat;
         GLuint format;
         GLuint type;
         GLuint dim;
      public:
         APITexture() : textureID(0), format(0), iFormat(0), type(0), dim(0) {}
         virtual ~APITexture();

         void loadFile(const String&);

         void bindToVertex(uint32 slot) const;
         void bindToFragment(uint32 slot) const;
      };

   template<>
   class APITexture1D<RS_GL43> : APITexture<RS_GL43>
      {
      private:
      protected:
      public:
         APITexture1D() {}
         virtual ~APITexture1D() {}

         void init(uint32, StructureFormat);
         void fill(byte*, uint32);
      };

   template<>
   class APITexture2D<RS_GL43> : APITexture<RS_GL43>
      {
      private:
         uint32 wth, hgt;
      protected:
      public:
         APITexture2D() : wth(0), hgt(0) {}
         virtual ~APITexture2D() {}

         void init(uint32, uint32, StructureFormat);
         void fill(byte*, uint32);
      };

   template<>
   class APITexture3D<RS_GL43> : APITexture<RS_GL43>
      {
      private:
         uint32 wth, hgt, dth;
      protected:
      public:
         APITexture3D() : wth(0), hgt(0), dth(0) {}
         virtual ~APITexture3D() {}

         void init(uint32, uint32, uint32, StructureFormat);
         void fill(byte*, uint32);
      };
#endif
   }

#endif
