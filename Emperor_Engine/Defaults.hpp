#ifndef __EMP_DEFAULTS_HPP__
#define __EMP_DEFAULTS_HPP__

namespace Emperor
   {

   class Defaults
      {
      public:
         static const char shaderDefGL[];
         static const char shaderDefDX[];
         static const char vertexFunc[];
         static const char fragmentFunc[];
         static const char mapName[];
         static const float textureDef[16];
         static const int modelSize;
         static const char modelDef[][52];
      };

   }

#endif