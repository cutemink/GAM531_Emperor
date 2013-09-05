#include "Material.hpp"
#include "Engine.hpp"
#include "Managers.hpp"
#include "ShaderManager.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   void MaterialPass<RS>::setVertexShader(const String& f, const String& fn, const
      Vertex& vd)
      {
      vShader = ShaderManager<RS>::getPtr()->getVertexShader(f, fn, &vd);
      }

   template <RenderSystem RS>
   void MaterialPass<RS>::setFragmentShader(const String& f, const String& fn)
      {
      fShader = ShaderManager<RS>::getPtr()->getFragmentShader(f, fn);
      }

   template <RenderSystem RS>
   void MaterialPass<RS>::finalize()
      {
      if(fShader && vShader)
         {
         program = new APIProgram<RS>();
         program->init(vShader->_exposeID(), fShader->_exposeID());
         }
      else
         {
         LOG("Material pass cannot be finalized unless vertex and fragment shader are set, aborting...");
         }
      }

   template <RenderSystem RS>
   void MaterialPass<RS>::setBlendState(const String& r)
      {
      blend = BlendStateManager<RS>::getPtr()->getResource(r);
      }

   template <RenderSystem RS>
   void MaterialPass<RS>::bindPass() const
      {
      program->bind();
      vShader->bindShader();

      for(auto i = vTextures.begin(), end = vTextures.end(); i < end; i++)
         (*i)->bindToVertex(i -vTextures.begin() + 1);

      for(auto i = vSamplers.begin(), end = vSamplers.end(); i < end; i++)
         (*i)->bindToVertex(i -vSamplers.begin() + 1);

      for(auto i = vUniforms.begin(), end = vUniforms.end(); i < end; i++)
         (*i)->bindToVertex(i - vUniforms.begin());

      fShader->bindShader();

      for(auto i = fTextures.begin(), end = fTextures.end(); i < end; i++)
         (*i)->bindToFragment(i - fTextures.begin() + 1);

      for(auto i = fSamplers.begin(), end = fSamplers.end(); i < end; i++)
         (*i)->bindToFragment(i - fSamplers.begin() + 1);

      for(auto i = fUniforms.begin(), end = fUniforms.end(); i < end; i++)
         (*i)->bindToFragment(i - fUniforms.begin());

      blend->bindBlendState();

      }

   template <RenderSystem RS>
   void MaterialTechnique<RS>::addPass(const MaterialPassDescription& desc)
      {
      MaterialPass<RS> mp;

      mp.setVertexShader(desc.vertexFilename, desc.vertexFunction, desc.vertexDef);
      mp.setFragmentShader(desc.fragmentFilename, desc.fragmentFunction);

      for(auto i = desc.samplers.begin(), end = desc.samplers.end(); i<end; i++)
         {
         auto op = desc.samplerOptions[i - desc.samplers.begin()];
         if(op == MPDO_VERTEX || op == MPDO_BOTH)
            mp.addSamplerReferenceForVertex(SamplerManager<RS>::getPtr()->getResource(*i));
         if(op == MPDO_FRAGMENT || op == MPDO_BOTH)
            mp.addSamplerReferenceForFragment(SamplerManager<RS>::getPtr()->getResource(*i));
         }

      for(auto i = desc.textures.begin(), end = desc.textures.end(); i<end; i++)
         {
         auto op = desc.textureOptions[i - desc.textures.begin()];
         if(op == MPDO_VERTEX || op == MPDO_BOTH)
            mp.addTextureReferenceForVertex(TextureManager<RS>::getPtr()->getResource(*i));
         if(op == MPDO_FRAGMENT || op == MPDO_BOTH)
            mp.addTextureReferenceForFragment(TextureManager<RS>::getPtr()->getResource(*i));
         }

      mp.setBlendState(desc.blendState);
	  mp.finalize();

      passes.push_back(Pair<MaterialPass<RS>,MaterialPassDescription>(mp,desc));
      }

   template <RenderSystem RS>
   void MaterialTechnique<RS>::render(uint32 indexCount) const
      {
      for(auto i = passes.begin(), end = passes.end(); i<end;i++)
         {
         (*i).first.bindPass();
         auto& desc = (*i).second;

         NodeManager<RS>::getPtr()->_bindBuffers();

         //set material
         switch(desc.useMaterialBuffer)
            {
            case MPDO_VERTEX:
               material->bindToVertex(desc.materialSlot);
               break;
            case MPDO_FRAGMENT:
               material->bindToFragment(desc.materialSlot);
               break;
            case MPDO_BOTH:
               material->bindToVertex(desc.materialSlot);
               material->bindToFragment(desc.materialSlot);
               break;
            }

         //set actor
         ActorManager<RS>& aMan = *ActorManager<RS>::getPtr();
         switch(desc.useActor)
            {
            case MPDO_VERTEX:
               aMan.getCurrent()->_bindVertex(desc.actorSlot);
               break;
            case MPDO_FRAGMENT:
               aMan.getCurrent()->_bindFragment(desc.actorSlot);
               break;
            case MPDO_BOTH:
               aMan.getCurrent()->_bindVertex(desc.actorSlot);
               aMan.getCurrent()->_bindFragment(desc.actorSlot);
               break;
            }

         //set camera
         CameraManager<RS>& cMan = *CameraManager<RS>::getPtr();
         switch(desc.useCamera)
            {
            case MPDO_VERTEX:
               cMan.getCurrent()->_bindVertex(desc.cameraSlot);
               break;
            case MPDO_FRAGMENT:
               cMan.getCurrent()->_bindFragment(desc.cameraSlot);
               break;
            case MPDO_BOTH:
               cMan.getCurrent()->_bindVertex(desc.cameraSlot);
               cMan.getCurrent()->_bindFragment(desc.cameraSlot);
               break;
            }


         if(desc.loopThroughLights)
            {
            LightManager<RS>& lMan = *LightManager<RS>::getPtr();
            lMan.prepareLoop();
            if(desc.loopThroughOneLightType)
               {
               while(lMan.bindNext(desc.lightLoopType))
                  {
                  switch(desc.useSingleLight)
                     {
                     case MPDO_VERTEX:
                        lMan.getCurrent()->_bindVertex(desc.singleLightSlot);
                        break;
                     case MPDO_FRAGMENT:
                        lMan.getCurrent()->_bindFragment(desc.singleLightSlot);
                        break;
                     case MPDO_BOTH:
                        lMan.getCurrent()->_bindVertex(desc.singleLightSlot);
                        lMan.getCurrent()->_bindFragment(desc.singleLightSlot);
                        break;
                     }
                  int c = (*i).second.loopCount;
                  while(c--)
                     {
                     _renderFromIndex<RS>(indexCount);
                     }
                  }
               }
            else
               {
               while(lMan.bindNext())
                  {
                  switch(desc.useSingleLight)
                     {
                     case MPDO_VERTEX:
                        lMan.getCurrent()->_bindVertex(desc.singleLightSlot);
                        break;
                     case MPDO_FRAGMENT:
                        lMan.getCurrent()->_bindFragment(desc.singleLightSlot);
                        break;
                     case MPDO_BOTH:
                        lMan.getCurrent()->_bindVertex(desc.singleLightSlot);
                        lMan.getCurrent()->_bindFragment(desc.singleLightSlot);
                        break;
                     }
                  int c = (*i).second.loopCount;
                  while(c--)
                     {
                     _renderFromIndex<RS>(indexCount);
                     }
                  }
               }
            }
         else
            {
            int c = desc.loopCount;
            while(c--)
               _renderFromIndex<RS>(indexCount);
            }
         }
      }

   template <RenderSystem RS>
   uint32 Material<RS>::addSize(uint32 typeSize)
      {
      finalized = false;
      material.addSize(typeSize);
      return matIndex++;
      }

   template <RenderSystem RS>
   void Material<RS>::finalizeDefinition()
      {
      //material.finalize();
      finalized = true;
      }

   template <RenderSystem RS>
   void Material<RS>::setValue(uint32 i, void* d)
      {
      material.lock();
      material.setData(i,d);
      material.unlock();
      }

   template <RenderSystem RS>
   uint32 Material<RS>::createTechnique(uint32 id, uint32 quality, uint32 LOD)
      {
      techniques.push_back(MaterialTechnique<RS>(id, LOD, quality, &material));
      return techniques.size() - 1;
      }

   template <RenderSystem RS>
   uint32 Material<RS>::createPass(const MaterialPassDescription& mpd)
      {
      passDefs.push_back(mpd);
      return passDefs.size() - 1;
      }

   template <RenderSystem RS>
   void Material<RS>::addPassToTechnique(uint32 t, uint32 p)
      {
      techniques[t].addPass(passDefs[p]);
      }

   template <RenderSystem RS>
   void Material<RS>::draw(uint32 id, uint32 quality, uint32 lod, uint32 indexCount) const
      {
      for(auto i = techniques.begin(), end = techniques.end(); i<end; i++)
         {
         if((*i).getID() == id && (*i).getLOD() == lod && (*i).getQuality() == quality)
            {
            (*i).render(indexCount);
            break;
            }
         }

      }

   template <RenderSystem RS>
   void Material<RS>::destroy()
      {
      MaterialManager<RS>::getPtr()->removeResource(this);
      delete this;
      }

#if (EMP_USE_OPENGL == ON)
   template class Material<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Material<RS_DX11>;
#endif
   }
