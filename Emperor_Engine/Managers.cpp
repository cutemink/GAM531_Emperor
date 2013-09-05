#include "Managers.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   ArrayList<MessagePackage> WindowManager::retrieveWindowMessages()
      {
      messageList.clear();
      for(auto i = objects.begin(); i < objects.end(); ++i)
         {
         currentProcess = (*i);
         (*i)->_processMessage();
         }
      currentProcess = 0;
      return messageList;
      }

   void WindowManager::collectMessage(WindowMessage message)
      {
      messageList.push_back(MessagePackage(currentProcess,message));
      }

   template <RenderSystem RS>
   bool ActorManager<RS>::bindNext()
      {
      if(it != activeObjects.end())
         {

         it++;
         return true;
         }
      return false;

      }

   template <RenderSystem RS>
   void ActorManager<RS>::render()
      {
      auto i = it -1;
      auto mat = NO_VIRT(Actor<RS>, *i, getMaterial)();
      auto mesh = NO_VIRT(Actor<RS>, *i, getMesh)();

      NO_VIRT(Mesh<RS>, mesh, bindMesh)();
      Engine<RS>::getPtr()->_getPlatformDevice().bindPrimitive(((Mesh<RS>*)mesh)->getPrimitive());
      NO_VIRT(Material<RS>, mat, draw)(0,0,0,NO_VIRT(Mesh<RS>,mesh, getIndexCount)());
      }

   template <RenderSystem RS>
   void NodeManager<RS>::init()
      {
      nodeBuffer = (Texture1D<RS>*)TextureManager<RS>::getPtr()->newResource("__EMP_NODES__",TT_1D);
      nodeBuffer->initCustom(MAX_NODES * 4, SF_4X4BYTE_FLOAT);

      nodeSampler = SamplerManager<RS>::getPtr()->newResource("__EMP_NODES__");
      nodeSampler->setAddressModeU(TA_WRAP);
      nodeSampler->build();
      }

   template <RenderSystem RS>
   Node<RS>* NodeManager<RS>::createObject()
      {
      auto i = nodeMatrices.push_back(Matrix<float,4>());
      auto n = new Node<RS>(i);

      objects.push_back(n);
      activeObjects.push_back(n);

      return n;
      }

   template <RenderSystem RS>
   void NodeManager<RS>::removeObject(Node<RS>* o)
      {
      nodeMatrices.erase(o->getIndex());

      auto i = searchList(objects.begin(), objects.end(), o);
      if(i != objects.end())
         objects.erase(i);
      }

   template <RenderSystem RS>
   void NodeManager<RS>::updateValues()
      {
      for(auto i = activeObjects.begin(), end = activeObjects.end(); i<end; i++)
         (*i)->_updateAbs(Matrix<float,4>().identity());
      }

   template <RenderSystem RS>
   void NodeManager<RS>::_updateBuffers()
      {
      auto inv = CameraManager<RS>::getPtr()->getView();


      for(auto i = objects.begin(), end = objects.end(); i < end; i++)
         {
         nodeMatrices[(*i)->getIndex()] = (*i)->_getAbs() * inv;
         }

      nodeBuffer->fill((byte*)nodeMatrices.getArray(), MAX_NODES * NODE_SIZE);
      }

   template <RenderSystem RS>
   void NodeManager<RS>::_bindBuffers()
      {
      nodeBuffer->bindToVertex(0);
      nodeSampler->bindToVertex(0);
      }

   template <RenderSystem RS>
   bool CameraManager<RS>::bindNext()
      {
      if(it != activeObjects.end())
         {
         auto node = NO_VIRT(Camera<RS>, *it, getNode)();
         view = inverse(NO_VIRT(Node<RS>, node, _getAbs)());
         (*it)->_bindRenderer();

         it++;
         return true;
         }
      return false;
      }

   template <RenderSystem RS>
   Vector<float,3> LightManager<RS>::compPoint(0.0f);

   template <RenderSystem RS>
   bool LightManager<RS>::lightCompare(Light<RS>* a, Light<RS>* b)
      {
      return ((*a).getNode()->getPosition() - LightManager::compPoint).fLength() <
         ((*b).getNode()->getPosition() - LightManager::compPoint).fLength();
      }

   template <RenderSystem RS>
   void LightManager<RS>::orderLights(Vector<float,3> position)
      {
      LightManager::compPoint = position;
      sortList(activeObjects.begin(), activeObjects.end(), LightManager::lightCompare);
      }

   template <RenderSystem RS>
   bool LightManager<RS>::bindNext()
      {
      if(it != activeObjects.end())
         {


         it++;

         return true;
         }
      return false;
      }

   template <RenderSystem RS>
   bool LightManager<RS>::bindNext(LightType t)
      {
      while(it != activeObjects.end() && (*it)->getLightType() != t)
         it++;
      if(it != activeObjects.end())
         {


         it++;
         return true;
         }
      return false;
      }

   template <RenderSystem RS>
   void MeshManager<RS>::init()
      {
      auto r = newResource(Defaults::mapName);
      ArrayList<String> vals(Defaults::modelDef, Defaults::modelDef + Defaults::modelSize);
      r->_loadOBJ(vals);
      }

   template <RenderSystem RS>
   Mesh<RS>* MeshManager<RS>::createResource(const String& r)
      {
      auto out = new Mesh<RS>();
      try
         {
         out->loadFromFile(r);
         resources[r] = out;
         }
      catch(ResourceLoadFailException e)
         {
         LOG(e.what());
         out->destroy();
         out = resources[Defaults::mapName];
         }
      return out;
      }

   template <RenderSystem RS>
   Material<RS>* MaterialManager<RS>::createResource(const String& r)
      {
      LOG("Create Resource not implemented yet");

      return 0;
      }

   template <RenderSystem RS>
   void TextureManager<RS>::init()
      {
      auto def = (Texture2D<RS>*)newResource(Defaults::mapName, TT_2D);
      def->initCustom(2, 2, SF_4X4BYTE_FLOAT);
      def->fill((byte*)Defaults::textureDef, sizeof(Defaults::textureDef));
      }

   template <RenderSystem RS>
   Texture<RS>* TextureManager<RS>::createResource(const String& r)
      {
      auto out = new Texture<RS>();
      try
         {
         out->loadFile(r);
         resources[r] = out;
         }
      catch(ResourceLoadFailException e)
         {
         LOG(e.what());
         out->destroy();
         out = resources[Defaults::mapName];
         }
      return out;
      }

   template <RenderSystem RS>
   Texture<RS>* TextureManager<RS>::newResource(const String& r, TextureType t)
      {
      Texture<RS>* out = 0;
      if(resources.find(r) == resources.end())
         {
         switch(t)
            {
            case TT_1D:
               out = new Texture1D<RS>();
               break;
            case TT_2D:
               out = new Texture2D<RS>();
               break;
            case TT_3D:
               out = new Texture3D<RS>();
               break;
            case TT_CUBE:
               LOG("Cube textures not yet implemented...");
               break;
            }
         resources[r] = out;
         }
      else
         LOG("A resource with that name already exists, aborting...");
      return out;
      }

   template <RenderSystem RS>
   TextureSampler<RS>* SamplerManager<RS>::createResource(const String& r)
      {
      LOG("Create Resource not implemented yet");

      return 0;
      }

   template <RenderSystem RS>
   BlendState<RS>* BlendStateManager<RS>::createResource(const String& r)
      {
      LOG("Create Resource not implemented yet");

      return 0;
      }

#if (EMP_USE_OPENGL == ON)
   template class BlendStateManager<RS_GL43>;
   template class CameraManager<RS_GL43>;
   template class ActorManager<RS_GL43>;
   template class MeshManager<RS_GL43>;
   template class NodeManager<RS_GL43>;
   template class TextureManager<RS_GL43>;
   template class SamplerManager<RS_GL43>;
   template class MaterialManager<RS_GL43>;
   template class LightManager<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class BlendStateManager<RS_DX11>;
   template class CameraManager<RS_DX11>;
   template class ActorManager<RS_DX11>;
   template class MeshManager<RS_DX11>;
   template class NodeManager<RS_DX11>;
   template class TextureManager<RS_DX11>;
   template class SamplerManager<RS_DX11>;
   template class MaterialManager<RS_DX11>;
   template class LightManager<RS_DX11>;
#endif

   }