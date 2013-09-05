#include "APIRasterizerState.hpp"
#include "Engine.hpp"
#include "APITranslations.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   APIRasterizerState<RS_DX11>::~APIRasterizerState()
      {
      if(rasterState)
         rasterState->Release();
      }

   void APIRasterizerState<RS_DX11>::init(const RasterizerStateDescription& r)
      {

      }

   void APIRasterizerState<RS_DX11>::bind()
      {

      }
#endif

#if EMP_USE_OPENGL
   inline void _glEnProx(GLuint a)
      {
      glEnable(a);
      }

   inline void _glDsProx(GLuint a)
      {
      glDisable(a);
      }

   void APIRasterizerState<RS_GL43>::init(const RasterizerStateDescription& r)
      {

      }

   void APIRasterizerState<RS_GL43>::bind()
      {

      }

   APIRasterizerState<RS_GL43>::APIRasterizerState()
      {//defaults

      }
#endif
   }
