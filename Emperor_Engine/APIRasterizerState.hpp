#ifndef __EMP_API_RASTERIZER_STATE_HPP__
#define __EMP_API_RASTERIZER_STATE_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class APIRasterizerState;

#if EMP_USE_DIRECTX
   template<>
   class APIRasterizerState<RS_DX11>
      {
      private:
         ID3D11RasterizerState* rasterState;
      protected:
      public:
         APIRasterizerState() : rasterState(0) {}
         ~APIRasterizerState();

         void init(const RasterizerStateDescription&);
         void bind();
      };
#endif

#if EMP_USE_OPENGL
   template<>
   class APIRasterizerState<RS_GL43>
      {
      private:
         void (*aaLine)(GLuint);
         void (*cullFace)(GLuint);
         GLuint cullDir;
         GLint depthBias;
         GLfloat depthClamp;
         GLuint fillMode;
         GLuint windOrder;
         void (*multiSample)(GLuint);
         void (*scissorTest)(GLuint);
         void (*depthClip)(GLuint);
      protected:
      public:
         APIRasterizerState();
         ~APIRasterizerState() {}

         void init(const RasterizerStateDescription&);
         void bind();
      };
#endif
   }

#endif