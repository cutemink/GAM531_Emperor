#ifndef __EMP_SCENE_OBJECT_HPP__
#define __EMP_SCENE_OBJECT_HPP__

#include "Common.hpp"
#include "Buffers.hpp"
#include "iSceneObject.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Node;

   template <RenderSystem RS, class I = iSceneObject>
   class SceneObject : public I
      {
      private:
      protected:
         bool active;
         Node<RS>* node;
         UniformBuffer<RS> buffer;

         SceneObject() : active(false), node(0) {}
         virtual ~SceneObject()
            {

            }

      public:
         void attachTo(const iNode* n)
            {

            }
         const iNode* getNode() const {return node;}

         bool isActive() {return active;}

         inline void _bindVertex(uint32 slot) {}
         inline void _bindFragment(uint32 slot) {}
      };
   }

#endif