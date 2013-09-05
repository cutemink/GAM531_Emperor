#ifndef __EMP_RASTERIZER_STATE_HPP__
#define __EMP_RASTERIZER_STATE_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "APIRasterizerState.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class RasterizerState
      {
      private:
         APIRasterizerState<RS> rast;
      protected:
      public:
         RasterizerState() {}
         ~RasterizerState() {}

         void initRasterState(const RasterizerStateDescription& r) {rast.init(r);}

         void bindRenderer() {rast.bind();}
      };
   }

#endif