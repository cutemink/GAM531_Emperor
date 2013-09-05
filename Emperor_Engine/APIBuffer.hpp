#ifndef __EMP_API_BUFFER_HPP__
#define __EMP_API_BUFFER_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "Vertex.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class APIBuffer;
   template <RenderSystem RS>
   class APIVertexBuffer;
   template <RenderSystem RS>
   class APIIndexBuffer;
   template <RenderSystem RS>
   class APIUniformBuffer;

#if EMP_USE_DIRECTX
   template<>
   class APIBuffer<RS_DX11>
      {
      private:
      protected:
         ID3D11Buffer* buffer;
         D3D11_MAPPED_SUBRESOURCE sub;
         APIBuffer() : buffer(0) {}
      public:
         virtual ~APIBuffer();

         void Release();

         
         void fill(const byte*, uint32);

         void lock();

         template <class T>
         void setData(uint32,T);
         void setData(uint32,void*,uint32);

         void unlock();
      };

   template<>
   class APIVertexBuffer<RS_DX11> : public APIBuffer<RS_DX11>
      {
      private:
      protected:
      public:
         APIVertexBuffer() {}
         void finalize(const Vertex&, uint32);
         void bind(uint32) const;
      };

   template<>
   class APIIndexBuffer<RS_DX11> : public APIBuffer<RS_DX11>
      {
      private:
      protected:
      public:
         APIIndexBuffer() {}
         void finalize(uint32 byteSize);
         void bind() const;
      };

   template<>
   class APIUniformBuffer<RS_DX11> : public APIBuffer<RS_DX11>
      {
      private:
      protected:
      public:
         APIUniformBuffer() {}
         void finalize(uint32 byteSize);
         void bindToVertex(uint32) const;
         void bindToFragment(uint32) const;
      };
#endif

#if EMP_USE_OPENGL
   template<>
   class APIBuffer<RS_GL43>
      {
      private:
      protected:
         GLuint bufferID;
         ArrayList<byte> tBuff;
         uint32 bSize;
         APIBuffer() : bufferID(0), bSize(0) {}
      public:
         virtual ~APIBuffer();

         void Release();

         virtual void fill(const byte*, uint32) = 0;
         virtual void lock() = 0;
         virtual void unlock() = 0;


         template <class T>
         void setData(uint32,T);
         void setData(uint32,void*,uint32);

      };

   template<>
   class APIVertexBuffer<RS_GL43> : public APIBuffer<RS_GL43>
      {
      private:
         Vertex vert;
         GLuint vID;
      protected:
      public:
         APIVertexBuffer() : vID(0) {}
         void fill(const byte*, uint32);
         void finalize(const Vertex&, uint32);
         void bind(uint32) const;
         void lock();
         void unlock();
      };

   template<>
   class APIIndexBuffer<RS_GL43> : public APIBuffer<RS_GL43>
      {
      private:
      protected:
      public:
         APIIndexBuffer() {}
         void fill(const byte*, uint32);
         void finalize(uint32 byteSize);
         void bind() const;
         void lock();
         void unlock();
      };

   template<>
   class APIUniformBuffer<RS_GL43> : public APIBuffer<RS_GL43>
      {
      private:
      protected:
      public:
         APIUniformBuffer() {}
         void fill(const byte*, uint32);
         void finalize(uint32 byteSize);
         void bindToVertex(uint32) const;
         void bindToFragment(uint32) const;
         void lock();
         void unlock();
      };
#endif
   }

#endif