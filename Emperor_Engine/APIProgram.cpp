#include "APIProgram.hpp"

namespace Emperor
   {
#if EMP_USE_OPENGL
   void APIProgram<RS_GL43>::init(uint32 vertexShader, uint32 fragmentShader)
      {/*
         prg = glCreateProgram();
         glAttachShader(prg, vertexShader);
         glAttachShader(prg, fragmentShader);
         glLinkProgram(prg);
         
         auto er = glGetError();
         if(er != GL_NO_ERROR)
            EMP_DEVICE_ERROR(String("Failed to link program!\nError code: "));*/
      }

   void APIProgram<RS_GL43>::bind()
      {
      //glUseProgram(prg);
      }
#endif
   }
