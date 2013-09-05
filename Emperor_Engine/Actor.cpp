#include "Actor.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   Actor<RS>::Actor()  : mat(0), mesh(0)
      {
      buffer.addType<uint32>();//node ID
      }

   template <RenderSystem RS>
   void Actor<RS>::destroy()
      {
      deactivate();
      ActorManager<RS>::getPtr()->removeObject(this);
      delete this;
      }

   template <RenderSystem RS>
   void Actor<RS>::setMesh(const iMesh* m)
      {
      if(!m)
         deactivate();
      mesh = (Mesh<RS>*)m;
      if(active)
         update();
      }

   template <RenderSystem RS>
   void Actor<RS>::setMesh(const String& name)
      {
      setMesh(MeshManager<RS>::getPtr()->getResource(name));
      }

   template <RenderSystem RS>
   void Actor<RS>::setMaterial(const iMaterial* m)
      {
      if(!m)
         deactivate();
      mat = (Material<RS>*)m;
      if(active)
         update();
      }

   template <RenderSystem RS>
   void Actor<RS>::setMaterial(const String& name)
      {
      setMaterial(MaterialManager<RS>::getPtr()->getResource(name));
      }

   template <RenderSystem RS>
   void Actor<RS>::activate()
      {
      if(node && mesh && mat && !active)
         {
         update();
         ActorManager<RS>::getPtr()->activateObject(this);
         active = true;
         }
      else
         LOG("Only inactive actors attached to a node, mesh and material can become active...");
      }

   template <RenderSystem RS>
   void Actor<RS>::deactivate()
      {
      if(active)
         {
         ActorManager<RS>::getPtr()->deactivateObject(this);
         active = false;
         }
      }

   template <RenderSystem RS>
   void Actor<RS>::update()
      {
      uint32 i = node->getIndex();
      buffer.fill((byte*)&i);
      }

#if (EMP_USE_OPENGL == ON)
   template class Actor<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Actor<RS_DX11>;
#endif
   }
