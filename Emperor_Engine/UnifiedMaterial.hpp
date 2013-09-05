#include "iMaterial.hpp"
#include "iResourceController.hpp"
#include "iBlendState.hpp"
#include "iTextureSampler.hpp"
#include <cfloat>

#define UM_PREPASS_BLENDSTATE_NAME "UnifiedMaterialPrepassBlendState"
#define UM_MAINPASS_BLENDSTATE_NAME "UnifiedMaterialMainpassBlendState"
#define UM_SAMPLER_NAME "UnifiedMaterialSampler"
#define UM_VS_NAME "BasicVertex"
#define UM_FS_NAME "BasicFragment"

namespace Emperor
   {
   class UnifiedMaterial
      {
      iMaterial*  _material;

      public:
         UnifiedMaterial(
            const String& name,
            iResourceController* resource,
            const String& diffuseTex,
            const String& ambientTex = "black.png",
            const String& specularTex = "black.png",
            float specularity = 0.0f,
            float shininess = 256.0f
         ) : _material(nullptr)
            {
            Vertex vDef;
            vDef.addVector3("POSITION");
            vDef.addVector3("NORMAL");
            vDef.addVector2("TEXCOORD");
            vDef.finalize();

            _material = resource->newCustomMaterial(name);
            _material->createTechnique(0,0,0);
            iBlendState* blend = (iBlendState*)resource->getBlendState(UM_PREPASS_BLENDSTATE_NAME);
            if (!blend)
               {
               blend = resource->newBlendState(UM_PREPASS_BLENDSTATE_NAME);
               blend->setAlphaToCoverage(false);
               blend->setIndependantBlend(false);
               blend->finalize();
               }

            MaterialPassDescription prePass;
            prePass.actorSlot = 2;
            prePass.blendState = UM_PREPASS_BLENDSTATE_NAME;
            prePass.cameraSlot = 0;
            prePass.fragmentFilename = UM_FS_NAME;
            prePass.fragmentFunction = "PrePassFragmentShader";
            prePass.loopCount = 1;
            prePass.loopThroughLights = false;
            prePass.loopThroughOneLightType = false;
            prePass.useActor = MPDO_VERTEX;
            prePass.useCamera = MPDO_VERTEX;
            prePass.useMaterialBuffer = MPDO_NONE;
            prePass.useSingleLight = MPDO_NONE;
            prePass.vertexDef = vDef;
            prePass.vertexFilename = UM_VS_NAME;
            prePass.vertexFunction = "PrePassVertexShader";

            _material->createPass(prePass);
            _material->addPassToTechnique(0,0);

            MaterialPassDescription mainPass;
            mainPass.cameraSlot = 0;
            mainPass.fragmentFilename = UM_FS_NAME;
            mainPass.fragmentFunction = "BasicFragmentShader";
            mainPass.loopCount = 1;
            mainPass.loopThroughLights = true;
            mainPass.loopThroughOneLightType = false;
            mainPass.materialSlot = 0;

            iTextureSampler* sampler = (iTextureSampler*)resource->getSampler(UM_SAMPLER_NAME);
            if (!sampler)
               {
               sampler = resource->newCustomSampler(UM_SAMPLER_NAME);

               TextureFilter tf;
               tf.linearMag = true;
               tf.linearMin = true;
               tf.linearMip = true;

               sampler->setFilter(tf);
               sampler->setBorderColor(Color(0,0,0,0));
               sampler->setComparisonMethod(TC_NEVER);
               sampler->setMaxAnisotropy(1);
               sampler->setMaxLOD(FLT_MAX);
               sampler->setMinLOD(0.0f);
               sampler->setMipLODBias(0.0f);
               sampler->setAddressModeU(TA_CLAMP);
               sampler->setAddressModeV(TA_CLAMP);
               sampler->setAddressModeW(TA_CLAMP);

               sampler->build();
               }

            mainPass.samplerOptions.push_back(MPDO_BOTH);
            mainPass.samplers.push_back(UM_SAMPLER_NAME);

            mainPass.singleLightSlot = 1;

            mainPass.textureOptions.push_back(MPDO_FRAGMENT);
            mainPass.textures.push_back(diffuseTex);
            mainPass.textureOptions.push_back(MPDO_FRAGMENT);
            mainPass.textures.push_back(ambientTex);
            mainPass.textureOptions.push_back(MPDO_FRAGMENT);
            mainPass.textures.push_back(specularTex);

            mainPass.useCamera = MPDO_BOTH;
            mainPass.useMaterialBuffer = MPDO_FRAGMENT;
            mainPass.materialSlot = 3;
            mainPass.useSingleLight = MPDO_BOTH;
            mainPass.vertexFilename = UM_VS_NAME;
            mainPass.vertexFunction = "BasicVertexShader";

            mainPass.useActor = MPDO_BOTH;
            mainPass.actorSlot = 2;

            _material->addSize(sizeof(float));
            _material->addSize(sizeof(float));

            blend = (iBlendState*)resource->getBlendState(UM_MAINPASS_BLENDSTATE_NAME);
            if (!blend)
               {
               blend = resource->newBlendState(UM_MAINPASS_BLENDSTATE_NAME);
               blend->setAlphaToCoverage(false);
               blend->setIndependantBlend(false);

               BlendStateDescription bd;
               bd.blendEnabled = true;
               blend->setDescription(bd, 0);
               blend->finalize();
               }

            mainPass.blendState = UM_MAINPASS_BLENDSTATE_NAME;
            mainPass.vertexDef = vDef;
            _material->createPass(mainPass);
            _material->addPassToTechnique(0,1);
            _material->finalizeDefinition();

            _material->setValue(0, &specularity);
            _material->setValue(1, &shininess);
            }

         const iMaterial* material() const
            {
            return _material;
            }
      };
   }

#undef UM_PREPASS_BLENDSTATE_NAME
#undef UM_SAMPLER_NAME
