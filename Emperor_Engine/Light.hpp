#ifndef __EMP_LIGHT_HPP__
#define __EMP_LIGHT_HPP__

#include "Common.hpp"
#include "SceneObject.hpp"
#include "iLight.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Light : public SceneObject<RS,iLight>
      {
      private:
         LightType type;
         Color  diffuse;
         Color specular;
         Vector<float,4> attenuation;
         Vector<float,3> spot;
      protected:
         virtual ~Light() {}

         void update();
      public:
         Light();

         void setLightType(LightType);
         LightType getLightType() const {return type;}

         void setDiffuse(const Color&);
         Color getDiffuse() const {return diffuse;}

         void setSpecular(const Color&);
         Color getSpecular() const {return specular;}

         void setAttenuation(const Vector<float, 4>&);
         Vector<float, 4> getAttenuation() const {return attenuation;}

         void setSpot(const Vector<float, 3>&);
         Vector<float, 3> getSpot() const {return spot;}

         void activate();
         void deactivate();

         void destroy();
      };
   }

#endif