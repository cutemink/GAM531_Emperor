#include "APIBlendState.hpp"
#include "Engine.hpp"
#include "APITranslations.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   APIBlendState<RS_DX11>::~APIBlendState()
      {
      if(bs)
         bs->Release();
      }


   void APIBlendState<RS_DX11>::bindBlendState() const
      {

      }


   void APIBlendState<RS_DX11>::finalize(const HashMap<uint32, BlendStateDescription>& dList,
      bool independantBlend, bool alphaToCoverage)
      {

      }
#endif

#if EMP_USE_OPENGL
   void APIBlendState<RS_GL43>::bindBlendState() const
      {

      }

   

   inline void _glEnProxi(GLuint i)
      {
      glEnablei(GL_BLEND, i);
      }

   inline void _glDsProxi(GLuint i)
      {
      glDisablei(GL_BLEND, i);
      }

   void APIBlendState<RS_GL43>::finalize(const HashMap<uint32, BlendStateDescription>& dList, 
      bool independantBlend, bool alphaToCoverage)
      {

      }
#endif
   }
