#ifndef __EMP_I_CAMERA_HPP__
#define __EMP_I_CAMERA_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "iSceneObject.hpp"

namespace Emperor
   {
   class iCamera : public iSceneObject
      {
      private:
      protected:
         iCamera() {}
         virtual ~iCamera() {}
      public:
         virtual void setFOV(float) = 0;
         virtual float getFOV() const = 0;

         virtual void setAspect(float) = 0;
         virtual float getAspect() const = 0;

         virtual void setNearClipping(float) = 0;
         virtual float getNearClipping() const = 0;

         virtual void setFarClipping(float) = 0;
         virtual float getFarClipping() const = 0;

         virtual void setRasterState(const RasterizerStateDescription& a) = 0;
      };
   }

#endif