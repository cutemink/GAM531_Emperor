#ifndef __EMP_I_MESH_HPP__
#define __EMP_I_MESH_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {
   class Vertex;

   class iMesh
      {
      private:
      protected:
         iMesh() {}
         virtual ~iMesh() {}
      public:
         virtual void loadFromList(const Vertex* vertexDefinition, 
            const ArrayList<byte*>& vertexList, const ArrayList<uint32>& indexList,
            const PrimitiveTopology& primitiveTopology) = 0;

         virtual void loadFromFile(const String& fileName) = 0;

         virtual uint32 getVertexCount() const = 0;
         virtual uint32 getIndexCount() const = 0;

         virtual void bindMesh() const = 0;

         virtual void destroy() = 0;
      };

   }

#endif