#include "ShaderManager.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   ShaderManager<RS>::ShaderManager()
      {
      }

   template <RenderSystem RS>
   void ShaderManager<RS>::init()
      {
      //construct safe default shader
      VertexShader<RS>* dv = 0;
      FragmentShader<RS>* df = 0;

      dv = new VertexShader<RS>();
      df = new FragmentShader<RS>();

      Vertex def;
      def.addVector3("POSITION");
      def.finalize();

      dv->associateVertex(def);

      if(RS == RS_DX11)
         {
         dv->initFromDef(Defaults::shaderDefDX, Defaults::vertexFunc);
         df->initFromDef(Defaults::shaderDefDX, Defaults::fragmentFunc);
         }
      else
         {
         dv->initFromDef(Defaults::shaderDefGL, Defaults::vertexFunc);
         df->initFromDef(Defaults::shaderDefGL, Defaults::fragmentFunc);
         }

      vShaders[Defaults::mapName][Defaults::mapName] = dv;
      fShaders[Defaults::mapName][Defaults::mapName] = df;
      }

   template <RenderSystem RS>
   ShaderManager<RS>::~ShaderManager()
      {
      for(auto i = vShaders.begin(); i!=vShaders.end(); i++)
         {
         for(auto j = (*i).second.begin(); j != (*i).second.end(); j++)
            {
            (*j).second->destroy();
            }
         }

      for(auto i = fShaders.begin(); i!=fShaders.end(); i++)
         {
         for(auto j = (*i).second.begin(); j != (*i).second.end(); j++)
            {
            (*j).second->destroy();
            }
         }
      }

   template <RenderSystem RS>
   VertexShader<RS>* ShaderManager<RS>::getVertexShader(const String& file, const String&
      function, const Vertex* p)
      {
      VertexShader<RS>* out = 0;
      auto f = vShaders.find(file);
      if(f != vShaders.end())
         {
         auto fn = (*f).second.find(function);
         if(fn != (*f).second.end())
            {
            out  = (*fn).second;
            }
         else
            {
            out = new VertexShader<RS>();
            if(p)
               out->associateVertex(*p);
            try
               {
               out->Shader::init(file, function);
               vShaders[file][function] = out;
               }
            catch(DeviceFailureException e)
               {
               LOG(e.what());
               out->destroy();
               out = vShaders[Defaults::mapName][Defaults::mapName];
               }
            }
         }
      else
         {
         vShaders[file] = HashMap<String,VertexShader<RS>*>();
         out = new VertexShader<RS>();
         if(p)
            out->associateVertex(*p);
         try
            {
            out->Shader::init(file, function);
            vShaders[file][function] = out;
            }
         catch(DeviceFailureException e)
            {
            LOG(e.what());
            out->destroy();
            out = vShaders[Defaults::mapName][Defaults::mapName];
            }
         }
      return out;
      }

   template <RenderSystem RS>
   FragmentShader<RS>* ShaderManager<RS>::getFragmentShader(const String& file, const String& function)
      {
      FragmentShader<RS>* out = 0;
      auto f = fShaders.find(file);
      if(f != fShaders.end())
         {
         auto fn = (*f).second.find(function);
         if(fn != (*f).second.end())
            {
            out  = (*fn).second;
            }
         else
            {
            out = new FragmentShader<RS>();
            try
               {
               out->Shader::init(file, function);
               fShaders[file][function] = out;
               }
            catch(DeviceFailureException e)
               {
               LOG(e.what());
               out->destroy();
               out = fShaders[Defaults::mapName][Defaults::mapName];
               }
            }
         }
      else
         {
         fShaders[file] = HashMap<String,FragmentShader<RS>*>();
         out = new FragmentShader<RS>();
         try
            {
            out->Shader::init(file, function);
            fShaders[file][function] = out;
            }
         catch(DeviceFailureException e)
            {
            LOG(e.what());
            out->destroy();
            out = fShaders[Defaults::mapName][Defaults::mapName];
            }
         }
      return out;
      }

   template <RenderSystem RS>
   void ShaderManager<RS>::preloadVertexShaders(const ArrayList<Pair<String,String>>& r)
      {
      auto end = r.end();
      for(auto i = r.begin(); i < end; i++)
         {
         auto v = new VertexShader<RS>();
         v->Shader::init((*i).first, (*i).second);
         vShaders[(*i).first][(*i).second] = v;
         }
      }

   template <RenderSystem RS>
   void ShaderManager<RS>::preloadFragmentShader(const ArrayList<Pair<String,String>>& r)
      {
      auto end = r.end();
      for(auto i = r.begin(); i < end; i++)
         {
         auto f = new FragmentShader<RS>();
         f->Shader::init((*i).first, (*i).second);
         fShaders[(*i).first][(*i).second] = f;
         }
      }

#if (EMP_USE_OPENGL == ON)
   template class ShaderManager<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class ShaderManager<RS_DX11>;
#endif
   }