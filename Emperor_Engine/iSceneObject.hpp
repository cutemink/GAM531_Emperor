#ifndef __EMP_I_SCENE_OBJECT_HPP__
#define __EMP_I_SCENE_OBJECT_HPP__

namespace Emperor
   {

   class iNode;

   class iSceneObject
      {
      private:
      protected:
         iSceneObject() {}
         virtual ~iSceneObject() {}

         virtual void update() = 0;
      public:
         virtual void attachTo(const iNode* node) = 0;
         virtual const iNode* getNode() const = 0;

         virtual bool isActive() = 0;
         virtual void activate() = 0;
         virtual void deactivate() = 0;

         virtual void destroy() = 0;
      };

   }

#endif