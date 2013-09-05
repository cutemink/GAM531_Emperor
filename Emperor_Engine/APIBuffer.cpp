#include "APIBuffer.hpp"
#include "Engine.hpp"
#include "APITranslations.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   APIBuffer<RS_DX11>::~APIBuffer()
      {
      Release();
      }

   void APIBuffer<RS_DX11>::Release()
      {
      if(buffer)
         {
         buffer->Release();
         buffer = 0;
         }
      }

   void APIVertexBuffer<RS_DX11>::finalize(const Vertex& v, uint32 size)
      {

      }

   void APIIndexBuffer<RS_DX11>::finalize(uint32 size)
      {

      }

   void APIUniformBuffer<RS_DX11>::finalize(uint32 size)
      {

      }

   void APIBuffer<RS_DX11>::fill(const byte* b, uint32 size)
      {

      }

   void APIBuffer<RS_DX11>::lock()
      {

      }

   void APIBuffer<RS_DX11>::unlock()
      {

      }

   template <class T>
   void APIBuffer<RS_DX11>::setData(uint32 i,T d)
      {

      }

   void APIBuffer<RS_DX11>::setData(uint32 i, void* d, uint32 s)
      {

      }

   void APIVertexBuffer<RS_DX11>::bind(uint32 vertexSize) const
      {

      }

   void APIIndexBuffer<RS_DX11>::bind() const
      {

      }

   void APIUniformBuffer<RS_DX11>::bindToVertex(uint32 slot) const
      {

      }

   void APIUniformBuffer<RS_DX11>::bindToFragment(uint32 slot) const
      {

      }
#endif

#if EMP_USE_OPENGL
   APIBuffer<RS_GL43>::~APIBuffer()
      {
      Release();
      }

   void APIBuffer<RS_GL43>::Release()
      {

      }

   static void _initVertex(const Vertex& v)
      {

      }

   void APIVertexBuffer<RS_GL43>::finalize(const Vertex& v, uint32 size)
      {

      }

      //get rid of useless param
   void APIIndexBuffer<RS_GL43>::finalize(uint32 size)
      {

      }

   void APIUniformBuffer<RS_GL43>::finalize(uint32 size)
      {

      }

   void APIVertexBuffer<RS_GL43>::fill(const byte* d, uint32 i)
      {

      }

   void APIIndexBuffer<RS_GL43>::fill(const byte* d, uint32 i)
      {

      }

   void APIUniformBuffer<RS_GL43>::fill(const byte* d, uint32 i)
      {

      }

   void APIVertexBuffer<RS_GL43>::lock()
      {

      }

   void APIIndexBuffer<RS_GL43>::lock()
      {

      }

   void APIUniformBuffer<RS_GL43>::lock()
      {

      }

   void APIVertexBuffer<RS_GL43>::unlock()
      {

      }

   void APIIndexBuffer<RS_GL43>::unlock()
      {

      }

   void APIUniformBuffer<RS_GL43>::unlock()
      {

      }

   template <class T>
   void APIBuffer<RS_GL43>::setData(uint32 i , T d)
      {

      }

   void APIBuffer<RS_GL43>::setData(uint32 i, void* d, uint32 s)
      {

      }

   void APIVertexBuffer<RS_GL43>::bind(uint32) const
      {

      }

   void APIIndexBuffer<RS_GL43>::bind() const
      {

      }

   void APIUniformBuffer<RS_GL43>::bindToVertex(uint32 index) const
      {

      }

   void APIUniformBuffer<RS_GL43>::bindToFragment(uint32 index) const
      {

      }
#endif
   }
