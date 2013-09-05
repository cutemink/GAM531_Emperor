#ifndef __EMP_SHADER_HPP__
#define __EMP_SHADER_HPP__

#include "Common.hpp"
#include "APIShader.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "Buffers.hpp"

namespace Emperor
   {
   class Shader
      {
      private:
      protected:
         String fileName;
         String function;

         virtual ~Shader() {}

         virtual void init() = 0;
      public:
         Shader() {}

         void init(String fn, String func);
         virtual void initFromDef(String def, String func) = 0;

         const String& getFilename() {return fileName;}
         const String& getFunction() {return function;}

         virtual void destroy() = 0;
      };

   template <RenderSystem RS>
   class VertexShader : public Shader
      {
      private:
         APIVertexShader<RS> vs;
         Vertex ref;
      protected:
         ~VertexShader() {}
         void init();
      public:
         VertexShader() {}
         void destroy();

         void associateVertex(const Vertex&);
         void initFromDef(String def, String func);

         void bindShader();

         uint32 _exposeID();
      };

   template <RenderSystem RS>
   class FragmentShader : public Shader
      {
      private:
         APIFragmentShader<RS> fs;
      protected:
         ~FragmentShader() {}
         void init();

      public:
         FragmentShader() {}
         void destroy();
         void initFromDef(String def, String func);

         void bindShader();

         uint32 _exposeID();
      };
   }

#endif