#ifndef __EMP_VERTEX_HPP__
#define __EMP_VERTEX_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {
   class Vertex
      {
      private:
      protected:
         ArrayList<InputElement> desc;
         HashMap<String, uint32> semanticCounter;

         byte* data;
         ArrayList<uint32> dynamIndex;
         uint32 byteSize;
         uint32 indexSize;

         bool finalized;

         void _addSize(uint32 size);
         uint32 _getSemanticCount(const String&);
      public:
         Vertex();
         Vertex(const Vertex&);
         virtual ~Vertex();

         void addFloat(const String&);
         void addInt(const String&);
         void addUint(const String&);

         void addVector2(const String&);
         void addVector3(const String&);
         void addVector4(const String&);

         Vertex& operator=(const Vertex&);

         void finalize();

         void fill(byte*, uint32);
         void fill(byte*);

         template <class T>
         void setData(const T& d, uint32 index)
            {
            memcpy(data + dynamIndex[index], &d, sizeof(d));
            }

         const byte* getData() const {return data;}
         void getData(byte* d) const {memcpy(d, data, byteSize);}

         uint32 getByteSize() const {return byteSize;}
         uint32 getNumOfElements() const {return indexSize;}

         const ArrayList<InputElement>& getVertexDescription() const 
            {return desc;}
      };
   }



#endif