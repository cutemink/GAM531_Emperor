#ifndef __EMP_BLEND_STATE_DX__
#define __EMP_BLEND_STATE_DX__

#include "APIBlendState.hpp"
#include "iBlendState.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class BlendState : public iBlendState
      {
      private:
         APIBlendState<RS> bs;
         HashMap<uint32, BlendStateDescription> dList;

         bool alphaToCoverage;
         bool independantBlend;

         bool finalized;
      protected:
         virtual ~BlendState() {}
      public:
         BlendState() : finalized(false), alphaToCoverage(false),
            independantBlend(false) {dList[0] = BlendStateDescription();}
         void destroy();

         void finalize();

         void setDescription(const BlendStateDescription&, uint32 renderTarget = 0);
         void setAlphaToCoverage(bool a) {alphaToCoverage = a;}
         void setIndependantBlend(bool a) {independantBlend = a;}

         void bindBlendState() const;
      };
   }

#endif