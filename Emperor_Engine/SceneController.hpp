#ifndef __EMP_SCENE_CONTROLLER_HPP__
#define __EMP_SCENE_CONTROLLER_HPP__

#include "iSceneController.hpp"
#include "Managers.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class SceneController : public iSceneController
      {
      private:
      protected:
      public:
         ActorManager<RS> actMan;
         CameraManager<RS> camMan;
         LightManager<RS> lgtMan;
         NodeManager<RS> nodMan;

         iActor* createActor()
            {return new Actor<RS>();}
         iCamera* createCamera()
            {return new Camera<RS>();}
         iLight* createLight()
            {return new Light<RS>();}
         iNode* createNode()
            {return new Node<RS>(0);}
      };

   }

#endif