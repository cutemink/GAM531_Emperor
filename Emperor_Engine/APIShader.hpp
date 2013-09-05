#ifndef __EMP_API_SHADER_HPP__
#define __EMP_API_SHADER_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "Vertex.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class APIVertexShader{};

   template <RenderSystem RS>
   class APIFragmentShader{};

#if EMP_USE_DIRECTX
   template <>
   class APIVertexShader<RS_DX11>
      {
      private:
         ID3D11VertexShader* vs;
         ID3D11InputLayout* layout;

      protected:
      public:
         APIVertexShader() : vs(0), layout(0) {}
         ~APIVertexShader();

         void init(const String&, const String&, const Vertex&);
         void initFromDef(const String&, const String&, const Vertex&);

         void bind();

         uint32 _exposeID() {return 0;}
      };

   template <>
   class APIFragmentShader<RS_DX11>
      {
      private:
         ID3D11PixelShader* fs;
      protected:
      public:
         APIFragmentShader() : fs(0) {}
         ~APIFragmentShader();

         void init(const String&, const String&);
         void initFromDef(const String&, const String&);

         void bind();

         uint32 _exposeID() {return 0;}
      };
#endif

#if EMP_USE_OPENGL
   template<>
   class APIVertexShader<RS_GL43>
      {
      private:
         GLuint vs;

      protected:
      public:
         APIVertexShader() : vs(0) {}
         ~APIVertexShader() {}

         void init(const String&, const String&, const Vertex&);
         void initFromDef(const String&, const String&, const Vertex&, const String& = String());

         void bind();

         uint32 _exposeID() {return vs;}
      };

   template<>
   class APIFragmentShader<RS_GL43>
      {
      private:
         GLuint fs;
      protected:
      public:
         APIFragmentShader() : fs(0) {}
         ~APIFragmentShader() {}

         void init(const String&, const String&);
         void initFromDef(const String&, const String&, const String& = String());

         void bind();

         uint32 _exposeID() {return fs;}
      };
#endif
   }

#endif