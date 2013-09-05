#include "Vertex.hpp"

namespace Emperor
   {
   Vertex::Vertex() : desc(0), data(0), byteSize(0), indexSize(0), finalized(0) {}

   Vertex::~Vertex()
      {
      if(data)
         delete [] data;
      }

   void Vertex::_addSize(uint32 size)
      {
      dynamIndex.push_back(byteSize);
      byteSize += size;
      indexSize++;

      if(finalized)
         {
         if(data)
            {
            delete [] data;
            data = 0;
            }
         finalized = false;
         }
      }

   uint32 Vertex::_getSemanticCount(const String& s)
      {
      auto i = semanticCounter.find(s);
      if(i != semanticCounter.end())
         {
         uint32 r = (*i).second + 1;
         semanticCounter[s] = r;
         return r;
         }
      else
         {
         semanticCounter[s] = 0;
         return 0;
         }
      }

   void Vertex::addFloat(const String& s)
      {
      InputElement d = {s.c_str(), _getSemanticCount(s), 
         SF_1X4BYTE_FLOAT, 0, byteSize, 0};
      desc.push_back(d);
      _addSize(sizeof(float));
      }

   void Vertex::addUint(const String& s)
      {
      InputElement d = {s.c_str(), _getSemanticCount(s), 
         SF_1X4BYTE_UINT, 0, byteSize, 0};
      desc.push_back(d);
      _addSize(sizeof(uint32));
      }

   void Vertex::addInt(const String& s)
      {
      InputElement d = {s.c_str(), _getSemanticCount(s), 
         SF_1X4BYTE_SINT, 0, byteSize, 0};
      desc.push_back(d);
      _addSize(sizeof(int));
      }

   void Vertex::addVector2(const String& s)
      {
      InputElement d = {s.c_str(), _getSemanticCount(s), 
         SF_2X4BYTE_FLOAT, 0, byteSize, 0};
      desc.push_back(d);
      _addSize(sizeof(Vector<float,2>));
      }

   void Vertex::addVector3(const String& s)
      {
      InputElement d = {s.c_str(), _getSemanticCount(s), 
         SF_3X4BYTE_FLOAT, 0, byteSize, 0};
      desc.push_back(d);
      _addSize(sizeof(Vector<float,3>));
      }

   void Vertex::addVector4(const String& s)
      {
      InputElement d = {s.c_str(), _getSemanticCount(s), 
         SF_4X4BYTE_FLOAT, 0, byteSize, 0};
      desc.push_back(d);
      _addSize(sizeof(Vector<float,4>));
      }

   void Vertex::finalize()
      {
      if(!byteSize)
         return;
      if(data)
         delete [] data;
      data = new byte[byteSize];
      finalized = true;
      }


   void Vertex::fill(byte* b, uint32 s)
      {
      memcpy(data, b, s);
      }

   void Vertex::fill(byte* b)
      {
      fill(b, byteSize);
      }

   Vertex::Vertex(const Vertex& v)
      {
      *this = v;
      }

   Vertex& Vertex::operator=(const Vertex& v)
      {
      desc = v.desc;
      semanticCounter = v.semanticCounter;
      dynamIndex = v.dynamIndex;
      byteSize = v.byteSize;
      indexSize = v.indexSize;

      data = 0;
      finalized = false;

      return *this;
      }
   }


