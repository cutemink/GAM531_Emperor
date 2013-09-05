#ifndef __EMP_I_BLEND_STATE_HPP__
#define __EMP_I_BLEND_STATE_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {
   class iBlendState
      {
      private:
      protected:
         iBlendState() {}
         virtual ~iBlendState() {}
      public:
         virtual void destroy() = 0;

         virtual void finalize() = 0;

         virtual void setDescription(const BlendStateDescription&, uint32 renderTarget) = 0;
         virtual void setAlphaToCoverage(bool a) = 0;
         virtual void setIndependantBlend(bool a) = 0;

         virtual void bindBlendState() const = 0;
      };
   }

#endif