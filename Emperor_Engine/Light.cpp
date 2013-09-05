#include "Light.hpp"
#include "Engine.hpp"

namespace Emperor
   {
   template <RenderSystem RS>
   Light<RS>::Light() : type(LT_DIRECTIONAL), diffuse(0.0f, 0.0f, 0.0f, 0.0f), 
      specular(0.0f,0.0f, 0.0f, 0.0f), attenuation(0.0f), spot(0.0f)
      {

      }

   template <RenderSystem RS>
   void Light<RS>::setLightType(LightType t)
      {
      type = t;
      if(active)
         update();
      }

   template <RenderSystem RS>
   void Light<RS>::setDiffuse(const Color& c)
      {
      diffuse  = c;
      if(active)
         update();
      }

   template <RenderSystem RS>
   void Light<RS>::setSpecular(const Color& c)
      {
      specular = c;
      if(active)
         update();
      }

   template <RenderSystem RS>
   void Light<RS>::setAttenuation(const Vector<float, 4>& a)
      {
      attenuation = a;
      if(active)
         update();
      }


   template <RenderSystem RS>
   void Light<RS>::setSpot(const Vector<float, 3>& s)
      {
      spot = s;
      if(active)
         update();
      }

   template <RenderSystem RS>
   void Light<RS>::activate()
      {
      }

   template <RenderSystem RS>
   void Light<RS>::deactivate()
      {
      }

   template <RenderSystem RS>
   void Light<RS>::destroy()
      {

      }


   template <RenderSystem RS>
   void Light<RS>::update()
      {
      auto data = new byte[buffer.getByteSize()];
      uint32 s = 0, t = 0, i = node->getIndex();

      memcpy(data + s, diffuse.data, t = sizeof(Vector<float,4>));
      s += t;
      memcpy(data + s, specular.data, t = sizeof(Vector<float,4>));
      s += t;
      memcpy(data + s, attenuation.data, t = sizeof(Vector<float,4>));
      s += t;
      memcpy(data + s, spot.data, t = sizeof(Vector<float,3>));
      s += t;
      memcpy(data + s, &i, t = sizeof(uint32));
      s += t;
      memcpy(data + s, &type, t = sizeof(LightType));

      buffer.fill(data);

      delete [] data;
      }

#if (EMP_USE_OPENGL == ON)
   template class Light<RS_GL43>;
#endif

#if (EMP_USE_DIRECTX == ON)
   template class Light<RS_DX11>;
#endif
   }