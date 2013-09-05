#ifndef __EMP_API_PROGRAM_HPP__
#define __EMP_API_PROGRAM_HPP__

#include "Common.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class APIProgram;

#if EMP_USE_DIRECTX
   template<>
   class APIProgram<RS_DX11>
      {
      //This doesn't have any use in DX11
      private:
      protected:
      public:
         APIProgram() {}
         ~APIProgram() {}
         void init(uint32 vertexShader, uint32 fragmentShader) {}
         void bind() {}
      };
#endif

#if EMP_USE_OPENGL
   template<>
   class APIProgram<RS_GL43>
      {
      private:
         GLuint prg;
      protected:
      public:
         APIProgram() : prg(0) {}
         ~APIProgram() {}
         void init(uint32 vertexShader, uint32 fragmentShader);
         void bind();
      };
#endif
   }
#endif