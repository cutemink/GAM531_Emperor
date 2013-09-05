#ifndef __EMP_ACTOR_HPP__
#define __EMP_ACTOR_HPP__

#include "Common.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "SceneObject.hpp"
#include "iActor.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Actor : public SceneObject<RS, iActor>
      {
      private:
         Material<RS>* mat;
         Mesh<RS>* mesh;

      protected:
         virtual ~Actor() {}

         void update();
      public:
         Actor();

         void destroy();

         void setMesh(const iMesh*);
         void setMesh(const String&);
         iMesh* getMesh() {return mesh;}

         void setMaterial(const iMaterial*);
         void setMaterial(const String&);
         iMaterial* getMaterial() {return mat;}

         void activate();
         void deactivate();
      };
   }

#endif