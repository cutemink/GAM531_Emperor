#include "Buffers.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   Buffer<RS>::~Buffer()
      {
      if(locked)
         unlock();
      if(finalized)
         releaseBuffer();
      delete buffer;
      }

   template <RenderSystem RS>
   void Buffer<RS>::addSize(uint32 s)
      {
      if(finalized)
         {
         if(locked)
            unlock();
         releaseBuffer();
         finalized = false;
         }
      dynamIndex.push_back(byteSize);
      byteSize += s;
      indexSize++;
      }

   template <RenderSystem RS>
   void Buffer<RS>::fill(const byte* b)
      {
      fill(b, byteSize);
      }

   template <RenderSystem RS>
   void Buffer<RS>::fill(const byte* b, uint32 size)
      {
      if(!finalized)
         {
         finalize();
         if(!finalized)
            {
            LOG("Failed to fill buffer!");
            return;
            }
         }

      try
         {
         buffer->fill(b,size);
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void Buffer<RS>::lock()
      {
      if(!finalized)
         {
         finalize();
         if(!finalized)
            {
            LOG("Failed to lock buffer!");
            return;//exit function on failure
            }
         }

      try
         {
         buffer->lock();
         locked = true;  
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void Buffer<RS>::unlock()
      {
      if(locked)
         {
         buffer->unlock();
         locked = false;
         }
      else
         LOG("Attempting to unlock an already unlocked buffer, operation aborted...");
      }

   template <RenderSystem RS>
   void VertexBuffer<RS>::finalize()
      {
      try
         {
         ((APIVertexBuffer<RS>*)buffer)->finalize(vertDef, byteSize);
         finalized = true;
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void IndexBuffer<RS>::finalize()
      {
      try
         {
         ((APIIndexBuffer<RS>*)buffer)->finalize(byteSize);
         finalized = true;
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void UniformBuffer<RS>::finalize()
      {
      try
         {
         ((APIUniformBuffer<RS>*)buffer)->finalize(byteSize);
         finalized = true;
         }
      catch(DeviceFailureException e)
         {
         LOG(e.what());
         }
      }

   template <RenderSystem RS>
   void VertexBuffer<RS>::bindVertex() const
      {
      ((APIVertexBuffer<RS>*)buffer)->bind(vertDef.getByteSize());
      }

   template <RenderSystem RS>
   void IndexBuffer<RS>::bindIndex() const
      {
      ((APIIndexBuffer<RS>*)buffer)->bind();
      }

   template <RenderSystem RS>
   void UniformBuffer<RS>::bindToVertex(uint32 slot) const
      {
      ((APIUniformBuffer<RS>*)buffer)->bindToVertex(slot);
      }

   template <RenderSystem RS>
   void UniformBuffer<RS>::bindToFragment(uint32 slot) const
      {
      ((APIUniformBuffer<RS>*)buffer)->bindToFragment(slot);
      }


#if (EMP_USE_OPENGL == ON)
   template class Buffer<RS_GL43>;
   template class UniformBuffer<RS_GL43>;
   template class VertexBuffer<RS_GL43>;
   template class IndexBuffer<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Buffer<RS_DX11>;
   template class UniformBuffer<RS_DX11>;
   template class VertexBuffer<RS_DX11>;
   template class IndexBuffer<RS_DX11>;
#endif
   }
