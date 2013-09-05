#include "Mesh.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   void Mesh<RS>::loadFromList(const Vertex* vd, const ArrayList<byte*>& v, const 
      ArrayList<uint32>& in, const PrimitiveTopology& pt)
      {
      uint32 vsize = vd->getByteSize();
      vertex.setVertexDef(*vd);

      int vs = v.size();
      while(vs--)
         vertex.addSize(vsize);

      byte* d = new byte[vsize * v.size()];
      uint32 c = 0;
      for(auto i = v.begin(), end = v.end(); i<end; i++, c++)
         memcpy(d + (c * vsize),(*i), vsize);

      vertex.fill(d);
      delete [] d;


      index.bindVector(&vertex);
      vs = in.size();
      while(vs--)
         index.addType<uint32>();

      d = new byte[sizeof(uint32) * in.size()];

      c = 0;
      for(auto i = in.begin(), end = in.end(); i < end; i++, c++)
         memcpy(d + (c * sizeof(uint32)), &(*i), sizeof(uint32));
      
      index.fill(d);
      delete [] d;

      prim = pt;
      }

   template <RenderSystem RS>
   void Mesh<RS>::loadFromFile(const String& filename)
      {
      File f;
      ArrayList<String> contents;
      String a;

      f.open(filename);

      if(!f)
         EMP_RESOURCE_ERROR("Unable to open mesh " + filename + ", using default...");
      while(f.good())
         {
         getLine(f,a);
         contents.push_back(a);
         }
      f.close();


      if(filename.find(".obj",filename.length() - 4))
         {
         _loadOBJ(contents);
         }
      else
         EMP_RESOURCE_ERROR("Unsupported mesh format, make sure extension is correct and supported, using default...");
      }

   template <RenderSystem RS>
   void Mesh<RS>::bindMesh() const
      {
      vertex.bindVertex();
      index.bindIndex();
      //prim.bindTopology();//logic moved else where
      }

   template <RenderSystem RS>
   void Mesh<RS>::destroy()
      {
      MeshManager<RS>::getPtr()->removeResource(this);
      delete this;
      }

   //This is a crappy solution, find a better one
   struct temp_vertex
      {
      float px, py, pz, nx, ny, nz, tu, tv;

      bool operator==(const temp_vertex& a)
         {
         return px == a.px && py == a.py && pz == a.pz && nx == a.nx
            && ny == a.ny && nz == a.nz && tu == a.tu && tv == a.tv;
         }

      void pos(const Vector<float,3>& a)
         {
         pos(a.x(), a.y(), a.z());
         }

      void norm(const Vector<float,3>& a)
         {
         norm(a.x(), a.y(), a.z());
         }

      void tex(const Vector<float,2>& a)
         {
         tex(a.x(), a.y());
         }

      void pos(float x, float y, float z)
         {
         px = x;
         py = y;
         pz = z;
         }

      void norm(float x, float y, float z)
         {
         nx = x;
         ny = y;
         nz = z;
         }

      void tex(float u, float v)
         {
         tu = u;
         tv = v;
         }
      };


   template <RenderSystem RS>
   void Mesh<RS>::_loadOBJ(const ArrayList<String>& data)
      {
      /*
      ArrayList<Vector<float,3>> vertices;
      ArrayList<Vector<float,3>> normals;
      ArrayList<Vector<float,2>> uvs;
      ArrayList<Vector<int, 3>> indices;
      ArrayList<Vector<int, 3>> nIndices;
      ArrayList<Vector<int, 3>> tIndices;
      for(auto i = data.begin(), end = data.end(); i<end;i++)
         {
         auto st = (*i).substr(0,2);
         if(st == "v ")
            {
            StringStream ss((*i).substr(2));
            Vector<float,3> v;
            ss >> v.x();
            ss >> v.y();
            ss >> v.z();
            vertices.push_back(v);
            }
         else if(st == "vn")
            {
            StringStream ss((*i).substr(3));
            Vector<float,3> vn;
            ss >> vn.x();
            ss >> vn.y();
            ss >> vn.z();
            normals.push_back(vn);
            }
         else if(st == "vt")
            {
            StringStream ss((*i).substr(3));
            Vector<float,2> vt;
            ss >> vt.x();
            ss >> vt.y();
            // PLATFORM_UVW(vt);
            vt.y() = 1 - vt.y();
            uvs.push_back(vt);
            }
         else if(st == "f ")
            {
            auto sList = SplitString((*i).substr(2), ' ');
            auto xList = SplitString(sList[0], '/');
            auto yList = SplitString(sList[1], '/');
            auto zList = SplitString(sList[2], '/');

            Vector<int,3> in, nin, tin;
            in.x() = in.y() = in.z() = -1;
            nin = tin = in;

            StringStream(xList[0]) >> in.x();
            StringStream(xList[1]) >> tin.x();
            StringStream(xList[2]) >> nin.x();

            StringStream(yList[0]) >> in.y();
            StringStream(yList[1]) >> tin.y();
            StringStream(yList[2]) >> nin.y();

            StringStream(zList[0]) >> in.z();
            StringStream(zList[1]) >> tin.z();
            StringStream(zList[2]) >> nin.z();

            in.x()--, in.y()--, in.z()--;
            tin.x()--, tin.y()--, tin.z()--;
            nin.x()--, nin.y()--, nin.z()--;

            indices.push_back(in);
            nIndices.push_back(nin);
            tIndices.push_back(tin);
            }
         }

      LinearSet<temp_vertex> tVert;

      ArrayList<uint32> fia;


      uint32 c = 0, j = 0;
      for(auto i = indices.begin(), end = indices.end(); i<end; i++, c++)
         {
         temp_vertex a;
         a.pos(vertices[(*i).x()]);
         a.norm(normals[nIndices[c].x()]);
         a.tex(uvs[tIndices[c].x()]);
         fia.push_back(tVert.push_back(a));

         a.pos(vertices[(*i).y()]);
         a.norm(normals[nIndices[c].y()]);
         a.tex(uvs[tIndices[c].y()]);
         fia.push_back(tVert.push_back(a));

         a.pos(vertices[(*i).z()]);
         a.norm(normals[nIndices[c].z()]);
         a.tex(uvs[tIndices[c].z()]);
         fia.push_back(tVert.push_back(a));
         }

      auto vt = Vertex();
      vt.addVector3("POSITION");
      vt.addVector3("NORMAL");
      vt.addVector2("TEXCOORD");
      vt.finalize();

      prim = PT_TRIANGLE_LIST;
      vertex.setVertexDef(vt);

      unsigned int vs = tVert.getSize();
      while(vs--)
         vertex.addSize(vt.getByteSize());

      vertex.fill((byte*)tVert.getDataPtr());

      vs = fia.size();
      while(vs--)
         index.addType<uint32>();
      index.bindVector(&vertex);
      index.fill((byte*)&fia.front());
      */
      }

#if (EMP_USE_OPENGL == ON)
   template class Mesh<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Mesh<RS_DX11>;
#endif
   }
