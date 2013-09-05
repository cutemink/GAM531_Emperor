#ifndef __EMP_CAMERA_HPP__
#define __EMP_CAMERA_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "SceneObject.hpp"
#include "RasterizerState.hpp"
#include "iCamera.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   class Camera : public SceneObject<RS,iCamera>
      {
      private:
         Matrix<float,4> projMatrix;

         float fov;
         float aspect;
         float nearClip;
         float farClip;

         RasterizerState<RS> rend;

         void _updateProjection();
      protected:
         virtual ~Camera() {}

         void update();
      public:
         Camera();

         void destroy();

         void setFOV(float);
         float getFOV() const {return fov;}

         void setAspect(float);
         float getAspect() const {return aspect;}

         void setNearClipping(float);
         float getNearClipping() const {return nearClip;}

         void setFarClipping(float);
         float getFarClipping() const {return farClip;}

         void setRasterState(const RasterizerStateDescription& a) 
            {
            try
               {
               rend.initRasterState(a);
               }
            catch(DeviceFailureException e)
               {
               LOG(e.what());//Can't really do anything about this...
               }
            }

         void activate();
         void deactivate();

         void _bindRenderer() {rend.bindRenderer();}
      };
   }

#endif