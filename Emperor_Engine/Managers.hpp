#ifndef __EMP_MANAGERS_HPP__
#define __EMP_MANAGERS_HPP__

#include "Common.hpp"
#include "BaseManager.hpp"
#include "ResourceManager.hpp"
#include "Actor.hpp"
#include "Buffers.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Node.hpp"
#include "Window.hpp"

namespace Emperor
   {
   class WindowManager : public Singleton<WindowManager>, public BaseManager<Window>
      {
      private:
         ArrayList<MessagePackage> messageList;
         Window* currentProcess;
      protected:
      public:
         WindowManager() : currentProcess(0) {}
         virtual ~WindowManager() {}

         ArrayList<MessagePackage> retrieveWindowMessages();
         void collectMessage(WindowMessage message);
      };

   template <RenderSystem RS>
   class NodeManager : public Singleton<NodeManager<RS>>, public BaseManager<Node<RS>>
      {
      private:
         Roster<Matrix<float,4>, MAX_NODES> nodeMatrices;

         Texture1D<RS>* nodeBuffer;
         TextureSampler<RS>* nodeSampler;
      protected:
      public:
         NodeManager() {}
         virtual ~NodeManager() {}

         void init();

         Node<RS>* createObject();
         void removeObject(Node<RS>*);


         void updateValues();

         void _updateBuffers();
         void _bindBuffers();
      };


   template <RenderSystem RS>
   class ActorManager : public Singleton<ActorManager<RS>>, public IterativeManager<Actor<RS>>
      {
      private:
      protected:
      public:
         ActorManager() {}
         virtual ~ActorManager() {}

         bool bindNext();
         void render();
      };


   template <RenderSystem RS>
   class CameraManager : public Singleton<CameraManager<RS>>, public IterativeManager<Camera<RS>>
      {
      private:
         Matrix<float, 4> view;
      protected:
      public:
         CameraManager() {}
         virtual ~CameraManager() {}

         bool bindNext();
         Matrix<float, 4> getView() const {return view;}
      };

   template <RenderSystem RS>
   class LightManager : public Singleton<LightManager<RS>>, public IterativeManager<Light<RS>>
      {
      private:
      protected:
         static Vector<float, 3> compPoint;
         static bool lightCompare(Light<RS>* a, Light<RS>* b);
      public:
         LightManager() {}
         virtual ~LightManager() {}

         void orderLights(Vector<float,3> position);

         bool bindNext();
         bool bindNext(LightType);
      };

   template <RenderSystem RS>
   class MeshManager : public Singleton<MeshManager<RS>>, public ResourceManager<Mesh<RS>>
      {
      private:
      protected:
         Mesh<RS>* createResource(const String& r);
      public:
         void init();

         MeshManager() {}
         virtual ~MeshManager() {}
      };


   template <RenderSystem RS>
   class MaterialManager : public Singleton<MaterialManager<RS>>, public ResourceManager<Material<RS>>
      {
      private:
      protected:
         Material<RS>* createResource(const String& r);
      public:
         MaterialManager() {}
         virtual ~MaterialManager() {}
      };

   template <RenderSystem RS>
   class TextureManager : public Singleton<TextureManager<RS>>, public ResourceManager<Texture<RS>>
      {
      private:
      protected:
         Texture<RS>* createResource(const String& r);
      public:
         TextureManager() {}
         virtual ~TextureManager() {}

         Texture<RS>* newResource(const String&, TextureType);
         void init();
      };

   template <RenderSystem RS>
   class SamplerManager : public Singleton<SamplerManager<RS>>, public ResourceManager<TextureSampler<RS>>
      {
      private:
      protected:
         TextureSampler<RS>* createResource(const String& r);
      public:
         SamplerManager() {}
         virtual ~SamplerManager() {}
      };


   template <RenderSystem RS>
   class BlendStateManager : public Singleton<BlendStateManager<RS>>, public ResourceManager<BlendState<RS>>
      {
      private:
      protected:
         BlendState<RS>* createResource(const String& r);
      public:
         BlendStateManager() {}
         virtual ~BlendStateManager() {}
      };
   }


#endif