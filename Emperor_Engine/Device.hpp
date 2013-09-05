#ifndef __EMP_DEVICE_DX_HPP__
#define __EMP_DEVICE_DX_HPP__

#include "Common.hpp"
#include "Types.hpp"

namespace Emperor
   {

   template <RenderSystem RS>
   class VertexShader;

   template <RenderSystem RS>
   class FragmentShader;

   template <RenderSystem RS>
   class Device {};

#if EMP_USE_DIRECTX
   template <>
   class Device<RS_DX11>
      {
      private:
         IDXGISwapChain* swap;
         ID3D11Device* dev;
         ID3D11DeviceContext* con;

         ID3D11RenderTargetView* backbuffer;
         ID3D11DepthStencilView* depthBuffer;


         bool active;
      protected:
      public:
         Device() : swap(0), dev(0), con(0), active(false) {}
         virtual ~Device();

         void init(Window*);
         void release();

         void renderStart();
         void renderEnd();

         void setFullScreen(bool);

         bool isActive() {return active;}

         //May want to move this...
         void bindPrimitive(const PrimitiveTopology&);

         void draw(uint32, uint32);
         void drawIndexed(uint32, uint32, uint32);

         IDXGISwapChain* _exposeSwap() {return swap;}
         ID3D11Device* _exposeDevice() {return dev;}
         ID3D11DeviceContext* _exposeContext() {return con;}

         static DXGI_FORMAT translateFormat(StructureFormat sf);

      };
#endif

#if EMP_USE_OPENGL
   template<>
   class Device<RS_GL43>
      {
      private:
         HGLRC context;
         HDC hdc;
         HWND wh;
         GLuint prim;
         Window* window;

         bool active;
      protected:
      public:
         Device() : context(0), hdc(0), active(false), window(0) {}
         virtual ~Device();

         void init(Window*);
         void release();

         void renderStart();
         void renderEnd();

         void setFullScreen(bool);

         bool isActive() {return active;}

         //May want to move this...
         void bindPrimitive(const PrimitiveTopology&);

         void draw(uint32, uint32);
         void drawIndexed(uint32, uint32, uint32);

      };
#endif
   }

#endif