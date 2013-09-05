#ifndef __EMP_MESH_HPP__
#define __EMP_MESH_HPP__

#include "iMesh.hpp"
#include "Vertex.hpp"
#include "Buffers.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Mesh : public iMesh
      {
      private:
         VertexBuffer<RS> vertex;
         IndexBuffer<RS> index;
         PrimitiveTopology prim;
      protected:

         virtual ~Mesh() {}
      public:
         Mesh() {}

         void loadFromList(const Vertex*, const ArrayList<byte*>&, const 
            ArrayList<uint32>&, const PrimitiveTopology&);
         void loadFromFile(const String&);
         void _loadOBJ(const ArrayList<String>&);

         uint32 getVertexCount() const {return vertex.getIndexSize();}
         uint32 getIndexCount() const {return index.getIndexSize();}

         const PrimitiveTopology& getPrimitive() const {return prim;}

         void bindMesh() const;

         void destroy();
      };
   }

#endif