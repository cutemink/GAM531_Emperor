#ifndef __EMP_I_ACTOR_HPP__
#define __EMP_I_ACTOR_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "iSceneObject.hpp"

namespace Emperor
   {

   class iMesh;
   class iMaterial;

   class iActor : public iSceneObject
      {
      private:
      protected:
         iActor() {}
         virtual ~iActor() {}
      public:
         virtual void setMesh(const String& name) = 0;
         virtual void setMesh(const iMesh* mesh) = 0;
         virtual const iMesh* getMesh() = 0;

         virtual void setMaterial(const String& name) = 0;
         virtual void setMaterial(const iMaterial* mat) = 0;
         virtual iMaterial* getMaterial() = 0;
      };

   }

#endif