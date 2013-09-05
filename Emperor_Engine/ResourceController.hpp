#ifndef __EMP_RESOURCE_CONTROLLER_HPP__
#define __EMP_RESOURCE_CONTROLLER_HPP__

#include "Common.hpp"
#include "iResourceController.hpp"
#include "Managers.hpp"
#include "ShaderManager.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class ResourceController : public iResourceController
      {
      private:
      protected:
      public:
         MeshManager<RS> mshMan;
         MaterialManager<RS> matMan;
         TextureManager<RS> texMan;
         SamplerManager<RS> smpMan;
         BlendStateManager<RS> blnMan;
         ShaderManager<RS> shdMan;

         const iMesh* getMesh(const String& n)
            {return new Mesh<RS>();}
         const iMaterial* getMaterial(const String& n)
            {return new Material<RS>();}
         const iTexture* getTexture(const String& n)
            {return new Texture<RS>();}
         const iTextureSampler* getSampler(const String& n)
            {return new TextureSampler<RS>();}
         const iBlendState* getBlendState(const String& n)
            {return new BlendState<RS>();}

         iMesh* newCustomMesh(const String& n)
            {return new Mesh<RS>();}
         iMaterial* newCustomMaterial(const String& n)
            {return new Material<RS>();}
         iTexture* newCustomTexture(const String& n, TextureType t)
            {return new Texture<RS>();}
         iTextureSampler* newCustomSampler(const String& n)
            {return new TextureSampler<RS>();}
         iBlendState* newBlendState(const String& n)
            {return new BlendState<RS>();}
      };

   }

#endif