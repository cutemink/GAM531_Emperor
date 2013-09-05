#ifndef __EMP_I_LIGHT_HPP__
#define __EMP_I_LIGHT_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "iSceneObject.hpp"

namespace Emperor
   {

   class iLight : public iSceneObject
      {
      private:
      protected:
         iLight() {}
         virtual ~iLight() {}
      public:
         virtual void setLightType(LightType) = 0;
         virtual LightType getLightType() const = 0;

         virtual void setDiffuse(const Color&) = 0;
         virtual Color getDiffuse() const = 0;

         virtual void setSpecular(const Color&) = 0;
         virtual Color getSpecular() const = 0;

         virtual void setAttenuation(const Vector<float, 4>&) = 0;
         virtual Vector<float, 4> getAttenuation() const = 0;

         virtual void setSpot(const Vector<float, 3>&) = 0;
         virtual Vector<float, 3> getSpot() const = 0;
      };

   }

#endif