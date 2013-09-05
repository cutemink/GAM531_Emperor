#ifndef __EMP_I_MATERIAL_HPP__
#define __EMP_I_MATERIAL_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "Structs.hpp"

namespace Emperor
   {

   class iMaterial
      {
      private:
      protected:
         iMaterial() {}
         virtual ~iMaterial() {}
      public:
         virtual uint32 addSize(uint32 typeSize) = 0;

         virtual void finalizeDefinition() = 0;

         virtual void setValue(uint32 index, void* data) = 0;

         virtual uint32 createTechnique(uint32 id, uint32 quality, uint32 LOD) = 0;
         virtual uint32 createPass(const MaterialPassDescription&) = 0;

         virtual void addPassToTechnique(uint32 tech, uint32 pass) = 0;

         virtual void destroy() = 0;
      };

   }

#endif