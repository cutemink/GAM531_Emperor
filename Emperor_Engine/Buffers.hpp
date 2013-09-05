#ifndef __EMP_BUFFERS_HPP__
#define __EMP_BUFFERS_HPP__

#include "Common.hpp"
#include "APIBuffer.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Buffer
      {
      private:
      protected:
         APIBuffer<RS>* buffer;
         ArrayList<uint32> dynamIndex;
         uint32 byteSize;
         uint32 indexSize;
         uint32 padding;

         bool finalized;
         bool locked;
         virtual void finalize() = 0;
         void releaseBuffer() {buffer->Release();}

         Buffer(APIBuffer<RS>* b) : byteSize(0), indexSize(0), padding(0), 
            finalized(false), locked(false), buffer(b) {}
      public:
         virtual ~Buffer();

         template <class T>
         void addType();

         template <class T>
         void addType(T);

         void addSize(uint32);

         void fill(const byte*);
         void fill(const byte*, uint32);

         void lock();

         template <class T>
         void setData(uint32 index, T);

         void setData(uint32 index, void* data);

         void unlock();

         uint32 getByteSize() const {return byteSize;}
         uint32 getIndexSize() const {return indexSize;}
      };

   template <RenderSystem RS>
   class VertexBuffer : public Buffer<RS>
      {
      private:
         Vertex vertDef;
      protected:
         void finalize();
      public:
         VertexBuffer() : Buffer(new APIVertexBuffer<RS>()) {}

         void setVertexDef(const Vertex& v) {vertDef = v;}
         void bindVertex() const;
      };

   template <RenderSystem RS>
   class IndexBuffer : public Buffer<RS>
      {
      private:
      protected:
         Buffer<RS>* vBuff;
         void finalize();
      public:
         IndexBuffer() : Buffer(new APIIndexBuffer<RS>()), vBuff(0) {}
         void bindVector(VertexBuffer<RS>* a) {vBuff = a;}

         void bindIndex() const;
      };

   template <RenderSystem RS>
   class UniformBuffer : public Buffer<RS>
      {
      private:
      protected:
         void finalize();
      public:
         UniformBuffer() : Buffer(new APIUniformBuffer<RS>()) {}

         void bindToVertex(uint32 slot) const;
         void bindToFragment(uint32 slot) const;
      };

   template <RenderSystem RS>
   template <class T>
   void Buffer<RS>::addType()
      {
      if(finalized)
         {
         if(locked)
            unlock();
         releaseBuffer();
         finalized = false;
         }
      uint32 i = sizeof(T);
      dynamIndex.push_back(byteSize);
      byteSize += i;
      indexSize++;
      }

   template <RenderSystem RS>
   template <class T>
   void Buffer<RS>::addType(T d)
      {
      if(finalized)
         {
         if(locked)
            unlock();
         releaseBuffer();
         finalized = false;
         }
      uint32 i = sizeof(d);
      dynamIndex.push_back(byteSize);
      byteSize += i;
      indexSize++;
      }

   template <RenderSystem RS>
   template<class T>
   void Buffer<RS>::setData(uint32 index, T d)
      {
      if(locked)
         {
         buffer.setData<T>(dynamIndex[index], d);
         }
      else
         LOG("You cannot set data of an unlocked buffer...");
      }

   template <RenderSystem RS>
   void Buffer<RS>::setData(uint32 index, void* d)
      {
      if(locked)
         {
         uint32 size = 0;
         if(dynamIndex.size() != index + 1)
            size = dynamIndex[index + 1] - dynamIndex[index];
         else
            size = byteSize - dynamIndex[index];
         buffer->setData(dynamIndex[index], d, size);
         }
      else
         LOG("You cannot set data of an unlocked buffer...");
      }
   }
#endif
