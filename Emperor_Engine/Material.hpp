#ifndef __EMP_MATERIAL_HPP__
#define __EMP_MATERIAL_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Buffers.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "BlendState.hpp"
#include "Shader.hpp"
#include "iMaterial.hpp"
#include "APIProgram.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class MaterialPass
      {
      private:
         ArrayList<const Texture<RS>*> vTextures;
         ArrayList<const Texture<RS>*> fTextures;

         ArrayList<const TextureSampler<RS>*> vSamplers;
         ArrayList<const TextureSampler<RS>*> fSamplers;

         ArrayList<UniformBuffer<RS>*> vUniforms;
         ArrayList<UniformBuffer<RS>*> fUniforms;

         BlendState<RS>* blend;

         VertexShader<RS>* vShader;
         FragmentShader<RS>* fShader;
         APIProgram<RS>* program;
      protected:
      public:
         MaterialPass() : vShader(0), fShader(0), program(0) {}
         ~MaterialPass() {}

         void addTextureReferenceForVertex(const Texture<RS>* t)
            {vTextures.push_back(t);}
         void addTextureReferenceForFragment(const Texture<RS>* t)
            {fTextures.push_back(t);}

         void addSamplerReferenceForVertex(const TextureSampler<RS>* ts)
            {vSamplers.push_back(ts);}
         void addSamplerReferenceForFragment(const TextureSampler<RS>* ts)
            {fSamplers.push_back(ts);}

         void addUniformReferenceForVertex(UniformBuffer<RS>* ub)
            {vUniforms.push_back(ub);}
         void addUniformReferenceForFragment(UniformBuffer<RS>* ub)
            {fUniforms.push_back(ub);}

         void setVertexShader(const String& fileName,
            const String& functionName, const Vertex&);
         void setFragmentShader(const String& fileNmae,
            const String& functionName);
         void finalize();

         void setBlendState(const String&);

         void bindPass() const;
      };

   template <RenderSystem RS>
   class MaterialTechnique
      {
      private:
         ArrayList<Pair<MaterialPass<RS>, MaterialPassDescription>> passes;
         uint32 LOD;
         uint32 quality;
         uint32 id;

         UniformBuffer<RS>* material;

      protected:
      public:
         MaterialTechnique() : LOD(0), quality(0), material(0), id(0) {}

         MaterialTechnique(uint32 i, uint32 l, uint32 q, UniformBuffer<RS>* m) : 
            id(i), LOD(l), quality(q), material(m) {}

         void addPass(const MaterialPassDescription& desc);

         void setLOD(uint32 l) {LOD = l;}
         uint32 getLOD() const {return LOD;}

         void setQuality(uint32 q) {quality = q;}
         uint32 getQuality() const {return quality;}

         void setID(uint32 q) {id = q;}
         uint32 getID() const {return id;}

         void render(uint32) const;

         void _setupBuffers(UniformBuffer<RS>* m)
            {
            material = m;
            }
      };


   template <RenderSystem RS>
   class Material : public iMaterial
      {
      private:
         ArrayList<MaterialTechnique<RS>> techniques;
         ArrayList<MaterialPassDescription> passDefs;

         uint32 matIndex;

         UniformBuffer<RS> material;

         bool finalized;
      protected:
         virtual ~Material() {}
      public:
         Material() : finalized(false), matIndex(0) {}

         uint32 addSize(uint32 typeSize);

         void finalizeDefinition();

         void setValue(uint32, void*);

         uint32 createTechnique(uint32 id, uint32 quality, uint32 LOD);

         uint32 createPass(const MaterialPassDescription&);

         void addPassToTechnique(uint32 tech, uint32 pass);


         void draw(uint32 id, uint32 quality, uint32 lod, uint32 indexCount) const;

         void destroy();
      };
   }

#endif