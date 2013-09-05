#ifndef __EMP_I_SCENE_CONTROLLER_HPP__
#define __EMP_I_SCENE_CONTROLLER_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   class iActor;
   class iCamera;
   class iLight;
   class iNode;

   class iSceneController
      {
      private:
      protected:
         iSceneController() {}
         virtual ~iSceneController() {}
      public:
         virtual iActor* createActor() = 0;
         virtual iCamera* createCamera() = 0;
         virtual iLight* createLight() = 0;
         virtual iNode* createNode() = 0;
      };

   }

#endif