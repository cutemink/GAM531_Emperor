#include "Shader.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   void Shader::init(String fn, String func)
      {
      fileName = fn;
      function = func;
      init();
      }

   template <RenderSystem RS>
   void VertexShader<RS>::destroy()
      {
      delete this;
      }

   template <RenderSystem RS>
   void VertexShader<RS>::associateVertex(const Vertex& v)
      {
      ref = v;
      }

   template <RenderSystem RS>
   void VertexShader<RS>::bindShader()
      {
      vs.bind();
      }

   template <RenderSystem RS>
   void VertexShader<RS>::init()
      {
      vs.init(fileName, function, ref);
      }

   template <RenderSystem RS>
   void VertexShader<RS>::initFromDef(String def, String func)
      {
      vs.initFromDef(def, func, ref);
      }

   template <RenderSystem RS>
   uint32 VertexShader<RS>::_exposeID()
      {
      return vs._exposeID();
      }

   template <RenderSystem RS>
   void FragmentShader<RS>::destroy()
      {
      delete this;
      }

   template <RenderSystem RS>
   void FragmentShader<RS>::bindShader()
      {
      fs.bind();
      }

   template <RenderSystem RS>
   void FragmentShader<RS>::init()
      {
      fs.init(fileName, function);
      }


   template <RenderSystem RS>
   void FragmentShader<RS>::initFromDef(String def, String func)
      {
      fs.initFromDef(def, func);
      }

   template <RenderSystem RS>
   uint32 FragmentShader<RS>::_exposeID()
      {
      return fs._exposeID();
      }

#if (EMP_USE_OPENGL == ON)
   template class VertexShader<RS_GL43>;
   template class FragmentShader<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class VertexShader<RS_DX11>;
   template class FragmentShader<RS_DX11>;
#endif
   }
