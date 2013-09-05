#include "Device.hpp"
#include "APITranslations.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   Device<RS_DX11>::~Device()
      {
      release();

      }

   void Device<RS_DX11>::init(Window* w)
      {
      DXGI_SWAP_CHAIN_DESC d;
      ZeroMemory(&d, sizeof(DXGI_SWAP_CHAIN_DESC));

 

      active = true;
      }

   void Device<RS_DX11>::renderStart()
      {

      }

   void Device<RS_DX11>::renderEnd()
      {

      }

   void Device<RS_DX11>::setFullScreen(bool b)
      {

      }

   void Device<RS_DX11>::release()
      {


      }

   void Device<RS_DX11>::draw(uint32 size, uint32 offset)
      {

      }

   void Device<RS_DX11>::drawIndexed(uint32 size, uint32 iOffset, uint32 vOffset)
      {

      }

   void Device<RS_DX11>::bindPrimitive(const PrimitiveTopology& p)
      {

      }

   DXGI_FORMAT Device<RS_DX11>::translateFormat(StructureFormat sf)
      {
      switch(sf)
         {
         case SF_UNKNOWN_FORMAT:
            return DXGI_FORMAT_UNKNOWN;
         case SF_4X4BYTE_TYPELESS:
            return DXGI_FORMAT_R32G32B32A32_TYPELESS;
         case SF_4X4BYTE_FLOAT:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
         case SF_4X4BYTE_UINT:
            return DXGI_FORMAT_R32G32B32A32_UINT;
         case SF_4X4BYTE_SINT:
            return DXGI_FORMAT_R32G32B32A32_SINT;
         case SF_3X4BYTE_TYPELESS:
            return DXGI_FORMAT_R32G32B32_TYPELESS;
         case SF_3X4BYTE_FLOAT:
            return DXGI_FORMAT_R32G32B32_FLOAT;
         case SF_3X4BYTE_UINT:
            return DXGI_FORMAT_R32G32B32_UINT;
         case SF_3X4BYTE_SINT:
            return DXGI_FORMAT_R32G32B32_SINT;
         case SF_2X4BYTE_TYPELESS:
            return DXGI_FORMAT_R32G32_TYPELESS;
         case SF_2X4BYTE_FLOAT:
            return DXGI_FORMAT_R32G32_FLOAT;
         case SF_2X4BYTE_UINT:
            return DXGI_FORMAT_R32G32_UINT;
         case SF_2X4BYTE_SINT:
            return DXGI_FORMAT_R32G32_SINT;
         case SF_1X4BYTE_TYPELESS:
            return DXGI_FORMAT_R32_TYPELESS;
         case SF_1X4BYTE_FLOAT:
            return DXGI_FORMAT_R32_FLOAT;
         case SF_1X4BYTE_UINT:
            return DXGI_FORMAT_R32_UINT;
         case SF_1X4BYTE_SINT:
            return DXGI_FORMAT_R32_SINT;
         case SF_4X2BYTE_TYPELESS:
            return DXGI_FORMAT_R16G16B16A16_TYPELESS;
         case SF_4X2BYTE_FLOAT:
            return DXGI_FORMAT_R16G16B16A16_FLOAT;
         case SF_4X2BYTE_UINT:
            return DXGI_FORMAT_R16G16B16A16_UINT;
         case SF_4X2BYTE_SINT:
            return DXGI_FORMAT_R16G16B16A16_SINT;
         case SF_2X2BYTE_TYPELESS:
            return DXGI_FORMAT_R16G16_TYPELESS;
         case SF_2X2BYTE_FLOAT:
            return DXGI_FORMAT_R16G16_FLOAT;
         case SF_2X2BYTE_UINT:
            return DXGI_FORMAT_R16G16_UINT;
         case SF_2X2BYTE_SINT:
            return DXGI_FORMAT_R16G16_SINT;
         case SF_1X2BYTE_TYPELESS:
            return DXGI_FORMAT_R16_TYPELESS;
         case SF_1X2BYTE_FLOAT:
            return DXGI_FORMAT_R16_FLOAT;
         case SF_1X2BYTE_UINT:
            return DXGI_FORMAT_R16_UINT;
         case SF_1X2BYTE_SINT:
            return DXGI_FORMAT_R16_SINT;
         case SF_4X1BYTE_TYPELESS:
            return DXGI_FORMAT_R16_TYPELESS;
         case SF_4X1BYTE_UINT:
            return DXGI_FORMAT_R8G8B8A8_UINT;
         case SF_4X1BYTE_SINT:
            return DXGI_FORMAT_R8G8B8A8_SINT;
         case SF_2X1BYTE_TYPELESS:
            return DXGI_FORMAT_R8G8_TYPELESS;
         case SF_2X1BYTE_UINT:
            return DXGI_FORMAT_R8G8_UINT;
         case SF_2X1BYTE_SINT:
            return DXGI_FORMAT_R8G8_SINT;
         case SF_1X1BYTE_TYPELESS:
            return DXGI_FORMAT_R8_TYPELESS;
         case SF_1X1BYTE_UINT:
            return DXGI_FORMAT_R8_UINT;
         case SF_1X1BYTE_SINT:
            return DXGI_FORMAT_R8_SINT;
         }
      LOG("Structure format outside of range, using default...");
      return DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
#endif

#if EMP_USE_OPENGL
   Device<RS_GL43>::~Device()
      {
      release();
      }

   void Device<RS_GL43>::init(Window* win)
      {

      }

   void Device<RS_GL43>::release()
      {
      }

   void Device<RS_GL43>::renderStart()
      {
      
      }

   void Device<RS_GL43>::renderEnd()
      {
      
      }


   void Device<RS_GL43>::setFullScreen(bool b)
      {

      }

   void Device<RS_GL43>::bindPrimitive(const PrimitiveTopology& a)
      {
      prim = _glTranPrim(a.pte);
      }

   void Device<RS_GL43>::draw(uint32 size, uint32 offset)
      {

      }

   void Device<RS_GL43>::drawIndexed(uint32 size, uint32 iOffset, uint32 vOffset)
      {

      }
#endif
   }
