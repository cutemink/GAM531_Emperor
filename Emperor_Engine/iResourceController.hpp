#ifndef __EMP_I_RESOURCE_CONTROLLER_HPP__
#define __EMP_I_RESOURCE_CONTROLLER_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   class iMesh;
   class iMaterial;
   class iTexture;
   class iTextureSampler;
   class iBlendState;

   class iResourceController
      {
      private:
      protected:
         iResourceController() {}
         virtual ~iResourceController() {}
      public:
         virtual const iMesh* getMesh(const String&) = 0;
         virtual const iMaterial* getMaterial(const String&) = 0;
         virtual const iTexture* getTexture(const String&) = 0;
         virtual const iTextureSampler* getSampler(const String&) = 0;
         virtual const iBlendState* getBlendState(const String&) = 0;

         virtual iMesh* newCustomMesh(const String&) = 0;
         virtual iMaterial* newCustomMaterial(const String&) = 0;
         virtual iTexture* newCustomTexture(const String&, TextureType t) = 0;
         virtual iTextureSampler* newCustomSampler(const String&) = 0;
         virtual iBlendState* newBlendState(const String&) = 0;
      };

   }

#endif