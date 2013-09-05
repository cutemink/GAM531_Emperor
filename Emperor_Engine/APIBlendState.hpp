#ifndef __EMP_API_BLEND_STATE_HPP__
#define __EMP_API_BLEND_STATE_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class APIBlendState{};

#if EMP_USE_DIRECTX
   template<>
   class APIBlendState<RS_DX11>
      {
      private:
         ID3D11BlendState* bs;
      protected:
      public:
         APIBlendState() : bs(0) {}
         virtual ~APIBlendState();

         void bindBlendState() const;
         void finalize(const HashMap<uint32, BlendStateDescription>&, bool, bool);
      };
#endif

#if EMP_USE_OPENGL
   struct _glBlend
      {
      GLuint index;
      void (*enableFunc)(GLuint);
      GLuint blendOp;
      GLuint blendOpAlpha;
      GLuint destBlend;
      GLuint destBlendAlpha;
      GLuint srcBlend;
      GLuint srcBlendAlpha;
      };

   template<>
   class APIBlendState<RS_GL43>
      {
      private:
         ArrayList<_glBlend> states;
      protected:
      public:
         APIBlendState() {}
         virtual ~APIBlendState() {}

         void bindBlendState() const;
         void finalize(const HashMap<uint32, BlendStateDescription>&, bool, bool);
      };
#endif
   }

#endif