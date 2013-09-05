#ifndef __EMP_SHADER_MANAGER_HPP__
#define __EMP_SHADER_MANAGER_HPP__

#include "Common.hpp"
#include "Shader.hpp"
namespace Emperor
   {
   template <RenderSystem RS>
   class ShaderManager : public Singleton<ShaderManager<RS>>
      {
      private:
         HashMap<String, HashMap<String, VertexShader<RS>*>> vShaders;
         HashMap<String, HashMap<String, FragmentShader<RS>*>> fShaders;
      protected:
      public:
         ShaderManager();
         ~ShaderManager();

         VertexShader<RS>* getVertexShader(const String& file, 
            const String& function, const Vertex*);
         FragmentShader<RS>* getFragmentShader(const String& file, 
            const String& function);

         void init();

         void preloadVertexShaders(const ArrayList<Pair<String,String>>&);
         void preloadFragmentShader(const ArrayList<Pair<String,String>>&);
      };
   }

#endif