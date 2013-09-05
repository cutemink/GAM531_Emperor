#include "Camera.hpp"
#include "Engine.hpp"
#include "Managers.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   Camera<RS>::Camera() : fov(0.9f), aspect(1.6f), nearClip(1.0f), farClip(1000.0f) 
      {
      projMatrix.identity();
      _updateProjection();

      buffer.addType<Matrix<float,4> >();//projection
      }

   template <RenderSystem RS>
   void Camera<RS>::_updateProjection()
      {

      }

   template <RenderSystem RS>
   void Camera<RS>::activate()
      {
      if(node && !active)
         {
         update();
         CameraManager<RS>::getPtr()->activateObject(this);
         active = true;
         }
      else
         LOG("Only inactive cameras attached to a node can become active...");
      }

   template <RenderSystem RS>
   void Camera<RS>::deactivate()
      {
      if(active)
         {
         CameraManager<RS>::getPtr()->deactivateObject(this);
         active = false;
         }
      }

   template <RenderSystem RS>
   void Camera<RS>::setFOV(float f)
      {
      fov = f;
      _updateProjection();
      }

   template <RenderSystem RS>
   void Camera<RS>::setAspect(float a)
      {
      aspect = a;
      _updateProjection();
      }

   template <RenderSystem RS>
   void Camera<RS>::setNearClipping(float n)
      {
      nearClip = n;
      _updateProjection();
      }

   template <RenderSystem RS>
   void Camera<RS>::setFarClipping(float f)
      {
      farClip = f;
      _updateProjection();
      }

   template <RenderSystem RS>
   void Camera<RS>::destroy()
      {
      deactivate();
      CameraManager<RS>::getPtr()->removeObject(this);
      delete this;
      }

   template <RenderSystem RS>
   void Camera<RS>::update()
      {
      buffer.fill((byte*)projMatrix.data);
      }

#if (EMP_USE_OPENGL == ON)
   template class Camera<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Camera<RS_DX11>;
#endif
   }
