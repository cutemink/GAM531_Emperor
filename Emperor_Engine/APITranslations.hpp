#ifndef __EMP_API_UTILITIES_HPP__
#define __EMP_API_UTILITIES_HPP__
#include "Common.hpp"
#include "Engine.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   static D3D11_BLEND_OP _dxTranOp(BlendOperation b)
      {
      switch(b)
         {
         case BO_ADD:
            return D3D11_BLEND_OP_ADD;
         case BO_SUBTRACT:
            return D3D11_BLEND_OP_SUBTRACT;
         case BO_REV_SUBTRACT:
            return D3D11_BLEND_OP_REV_SUBTRACT;
         case BO_MIN:
            return D3D11_BLEND_OP_MIN;
         case BO_MAX:
            return D3D11_BLEND_OP_MAX;
         }
      LOG("Blend operation outside of range, using default...");
      return D3D11_BLEND_OP_ADD;
      }

   static D3D11_BLEND _dxTranBl(BlendOption b)
      {
      switch(b)
         {
         case BO_ZERO:
            return D3D11_BLEND_ZERO;
         case BO_ONE:
            return D3D11_BLEND_ONE;
         case BO_SRC_COLOR:
            return D3D11_BLEND_SRC_COLOR;
         case BO_INV_SRC_COLOR:
            return D3D11_BLEND_INV_SRC_COLOR;
         case BO_SRC_ALPHA:
            return D3D11_BLEND_SRC_ALPHA;
         case BO_INV_SRC_ALPHA:
            return D3D11_BLEND_INV_SRC_ALPHA;
         case BO_DEST_ALPHA:
            return D3D11_BLEND_DEST_ALPHA;
         case BO_INV_DEST_ALPHA:
            return D3D11_BLEND_INV_DEST_ALPHA;
         case BO_DEST_COLOR:
            return D3D11_BLEND_DEST_COLOR;
         case BO_INV_DEST_COLOR:
            return D3D11_BLEND_INV_DEST_COLOR;
         case BO_SRC_ALPHA_SAT:
            return D3D11_BLEND_SRC_ALPHA_SAT;
         case BO_BLEND_FACTOR:
            return D3D11_BLEND_BLEND_FACTOR;
         case BO_INV_BLEND_FACTOR:
            return D3D11_BLEND_INV_BLEND_FACTOR;
         case BO_SRC1_COLOR:
            return D3D11_BLEND_SRC1_COLOR;
         case BO_INV_SRC1_COLOR:
            return D3D11_BLEND_INV_SRC1_COLOR;
         case BO_SRC1_ALPHA:
            return D3D11_BLEND_SRC1_ALPHA;
         case BO_INV_SRC1_ALPHA:
            return D3D11_BLEND_SRC1_ALPHA;
         }
      LOG("Blend option outside of range, using default...");
      return D3D11_BLEND_SRC_COLOR;
      }

   static D3D11_CULL_MODE _dxTranCull(CullMode c)
      {
      switch(c)
         {
         case CL_NONE:
            return D3D11_CULL_NONE;
         case CL_FRONT:
            return D3D11_CULL_FRONT;
         case CL_BACK:
            return D3D11_CULL_BACK;
         }
      LOG("Cull mode outside of range, using default...");
      return D3D11_CULL_NONE;
      }

   static D3D11_FILL_MODE _dxTranFill(FillMode f)
      {
      switch(f)
         {
         case FM_SOLID:
            return D3D11_FILL_SOLID;
         case FM_WIREFRAME:
            return D3D11_FILL_WIREFRAME;
         }
      LOG("Fill mode outside of range, using default...");
      return D3D11_FILL_SOLID;
      }
   static void _dxTranVertex(const ArrayList<InputElement>& a ,D3D11_INPUT_ELEMENT_DESC** p)
      {
      *p = new D3D11_INPUT_ELEMENT_DESC[a.size()];

      uint32 c = 0;
      for(auto i = a.begin(), end = a.end(); i < end; i++, c++)
         {
         (*p)[c].AlignedByteOffset = (*i).aligned;
         (*p)[c].Format = Engine<RS_DX11>::getPtr()->_getPlatformDevice().translateFormat(((*i).format));
         (*p)[c].InputSlot = (*i).input;
         (*p)[c].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
         (*p)[c].InstanceDataStepRate = (*i).bsize;
         (*p)[c].SemanticIndex = (*i).semCount;
         (*p)[c].SemanticName = &(*(*i).sem.begin());
         }
      }

   static D3D11_FILTER _dxTranFilter(const TextureFilter& tf)
      {
      unsigned int rep =  1 * tf.linearMin + 2 * tf.linearMag + 4 * tf.linearMip
         + 8 * tf.anisotropic + 16 * tf.comparison;

      D3D11_FILTER out = D3D11_FILTER_MIN_MAG_MIP_POINT;

      switch(rep)
         {
         case 0:
            out = D3D11_FILTER_MIN_MAG_MIP_POINT;
            break;
         case 1:
            out = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
            break;
         case 2:
            out = D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
            break;
         case 3:
            out = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
            break;
         case 4:
            out = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
            break;
         case 5:
            out = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
            break;
         case 6:
            out = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
            break;
         case 7:
            out = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            break;
         case 8:
         case 9:
         case 10:
         case 11:
         case 12:
         case 13:
         case 14:
         case 15:
            out = D3D11_FILTER_ANISOTROPIC;
            break;
         case 16:
            out = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
            break;
         case 17:
            out = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
            break;
         case 18:
            out = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
            break;
         case 19:
            out = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
            break;
         case 20:
            out = D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
            break;
         case 21:
            out = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
            break;
         case 22:
            out = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
            break;
         case 23:
            out = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
            break;
         case 24:
         case 25:
         case 26:
         case 27:
         case 28:
         case 29:
         case 30:
         case 31:
            out = D3D11_FILTER_COMPARISON_ANISOTROPIC;
            break;
         default:
            LOG("Could not determine texture filter, using default...");
         }
      return out;
      }

   static D3D11_TEXTURE_ADDRESS_MODE _dxTranAddress(TextureAddressMode t)
      {
      switch(t)
         {
         case TA_WRAP:
            return D3D11_TEXTURE_ADDRESS_WRAP;
         case TA_MIRROR:
            return D3D11_TEXTURE_ADDRESS_MIRROR;
         case TA_CLAMP:
            return D3D11_TEXTURE_ADDRESS_CLAMP;
         case TA_BORDER:
            return D3D11_TEXTURE_ADDRESS_BORDER;
         case TA_MIRROR_ONCE:
            return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
         }
      LOG("Texture address mode outside of range, using default...");
      return D3D11_TEXTURE_ADDRESS_WRAP;
      }

   static D3D11_COMPARISON_FUNC _dxTranCompare(TextureComparisonMethod t)
      {
      switch(t)
         {
         case TC_NEVER:
            return D3D11_COMPARISON_NEVER;
         case TC_LESS:
            return D3D11_COMPARISON_LESS;
         case TC_EQUAL:
            return D3D11_COMPARISON_EQUAL;
         case TC_LESS_EQUAL:
            return D3D11_COMPARISON_LESS_EQUAL;
         case TC_GREATER:
            return D3D11_COMPARISON_GREATER;
         case TC_NOT_EQUAL:
            return D3D11_COMPARISON_NOT_EQUAL;
         case TC_GREATER_EQUAL:
            return D3D11_COMPARISON_GREATER_EQUAL;
         case TC_ALWAYS:
            return D3D11_COMPARISON_ALWAYS;
         }
      LOG("Comparison func outside of range, using default...");
      return D3D11_COMPARISON_NEVER;
      }

   static D3D11_PRIMITIVE_TOPOLOGY _dxTranPrim(PrimitiveTopologyEnum p)
      {
      switch(p)
         {
         case PT_POINT_LIST:
            return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
         case PT_LINE_LIST:
            return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
         case PT_LINE_STRIP:
            return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
         case PT_TRIANGLE_LIST:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
         case PT_TRIANGLE_STRIP:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
         case PT_LINE_LIST_ADJ:
            return D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;
         case PT_LINE_STRIP_ADJ:
            return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;
         case PT_TRIANGLE_LIST_ADJ:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;
         case PT_TRIANGLE_STRIP_ADJ:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;
         }
      LOG("Primitive topology out of range, using default...");
      return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
      }
#endif

#if EMP_USE_OPENGL
   static GLuint _glTranOp(BlendOperation b)
      {
      switch(b)
         {
         case BO_ADD:
            return GL_FUNC_ADD;
         case BO_SUBTRACT:
            return GL_FUNC_SUBTRACT;
         case BO_REV_SUBTRACT:
            return GL_FUNC_REVERSE_SUBTRACT;
         case BO_MIN:
            return GL_MIN;
         case BO_MAX:
            return GL_MAX;
         }
      LOG("Blend operation outside of range, using default...");
      return GL_FUNC_ADD;
      }

   static GLuint _glTranBl(BlendOption b)
      {
      switch(b)
         {
         case BO_ZERO:
            return GL_ZERO;
         case BO_ONE:
            return GL_ONE;
         case BO_SRC_COLOR:
            return GL_SRC_COLOR;
         case BO_INV_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
         case BO_SRC_ALPHA:
            return GL_SRC_ALPHA;
         case BO_INV_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
         case BO_DEST_ALPHA:
            return GL_DST_ALPHA;
         case BO_INV_DEST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
         case BO_DEST_COLOR:
            return GL_DST_COLOR;
         case BO_INV_DEST_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
         case BO_SRC_ALPHA_SAT:
            return GL_SRC_ALPHA_SATURATE;
         case BO_BLEND_FACTOR:
            return GL_CONSTANT_COLOR;//probably wrong
         case BO_INV_BLEND_FACTOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;//this too, don't use
         case BO_SRC1_COLOR:
            return GL_SRC1_COLOR;
         case BO_INV_SRC1_COLOR:
            return GL_ONE_MINUS_SRC1_COLOR;
         case BO_SRC1_ALPHA:
            return GL_SRC1_ALPHA;
         case BO_INV_SRC1_ALPHA:
            return GL_ONE_MINUS_SRC1_ALPHA;
         }
      LOG("Blend option outside of range, using default...");
      return GL_SRC_COLOR;
      }

   static GLuint _glExtractFormat(StructureFormat str, uint32& cnt)
      {
      switch(str)
         {
         case SF_4X4BYTE_FLOAT:
            cnt = 4;
            return GL_FLOAT;
         case SF_4X4BYTE_UINT:
            cnt = 4;
            return GL_UNSIGNED_INT;
         case SF_4X4BYTE_SINT:
            cnt = 4;
            return GL_INT;
         case SF_3X4BYTE_FLOAT:
            cnt = 3;
            return GL_FLOAT;
         case SF_3X4BYTE_UINT:
            cnt = 3;
            return GL_UNSIGNED_INT;
         case SF_3X4BYTE_SINT:
            cnt = 3;
            return GL_INT;
         case SF_2X4BYTE_FLOAT:
            cnt = 2;
            return GL_FLOAT;
         case SF_2X4BYTE_UINT:
            cnt = 2;
            return GL_UNSIGNED_INT;
         case SF_2X4BYTE_SINT:
            cnt = 2;
            return GL_INT;
         case SF_1X4BYTE_FLOAT:
            cnt = 1;
            return GL_FLOAT;
         case SF_1X4BYTE_UINT:
            cnt = 1;
            return GL_UNSIGNED_INT;
         case SF_1X4BYTE_SINT:
            cnt = 1;
            return GL_INT;
         case SF_4X2BYTE_FLOAT:
            cnt = 4;
            return GL_HALF_FLOAT;
         case SF_4X2BYTE_UINT:
            cnt = 4;
            return GL_UNSIGNED_SHORT;
         case SF_4X2BYTE_SINT:
            cnt = 4;
            return GL_SHORT;
         case SF_2X2BYTE_FLOAT:
            cnt = 2;
            return GL_HALF_FLOAT;
         case SF_2X2BYTE_UINT:
            cnt = 2;
            return GL_UNSIGNED_SHORT;
         case SF_2X2BYTE_SINT:
            cnt = 2;
            return GL_SHORT;
         case SF_1X2BYTE_FLOAT:
            cnt = 1;
            return GL_HALF_FLOAT;
         case SF_1X2BYTE_UINT:
            cnt = 1;
            return GL_UNSIGNED_SHORT;
         case SF_1X2BYTE_SINT:
            cnt = 1;
            return GL_SHORT;
         case SF_4X1BYTE_UINT:
            cnt = 4;
            return GL_UNSIGNED_BYTE;
         case SF_4X1BYTE_SINT:
            cnt = 4;
            return GL_BYTE;
         case SF_2X1BYTE_UINT:
            cnt = 2;
            return GL_UNSIGNED_BYTE;
         case SF_2X1BYTE_SINT:
            cnt = 2;
            return GL_BYTE;
         case SF_1X1BYTE_UINT:
            cnt = 1;
            return GL_UNSIGNED_BYTE;
         case SF_1X1BYTE_SINT:
            cnt = 1;
            return GL_BYTE;
         }
      LOG("Structure format outside of range, using default...");
            cnt = 4;
            return GL_FLOAT;
      }

   static GLint _glTranslateFormat(StructureFormat sf, GLuint& format, GLuint& type)
      {
      switch(sf)
         {
         case SF_4X4BYTE_FLOAT:
            format = GL_RGBA;
            type = GL_FLOAT;
            return GL_RGBA32F;
         case SF_4X4BYTE_UINT:
            format = GL_RGBA_INTEGER;
            type = GL_UNSIGNED_INT;
            return GL_RGBA32UI;
         case SF_4X4BYTE_SINT:
            format = GL_RGBA_INTEGER;
            type = GL_INT;
            return GL_RGBA32I;
         case SF_3X4BYTE_FLOAT:
            format = GL_RGB;
            type = GL_FLOAT;
            return GL_RGB32F;
         case SF_3X4BYTE_UINT:
            format = GL_RGB_INTEGER;
            type = GL_UNSIGNED_INT;
            return GL_RGB32UI;
         case SF_3X4BYTE_SINT:
            format = GL_RGB_INTEGER;
            type = GL_INT;
            return GL_RGB32I;
         case SF_2X4BYTE_FLOAT:
            format = GL_RG;
            type = GL_FLOAT;
            return GL_RG32F;
         case SF_2X4BYTE_UINT:
            format = GL_RG_INTEGER;
            type = GL_UNSIGNED_INT;
            return GL_RG32UI;
         case SF_2X4BYTE_SINT:
            format = GL_RG_INTEGER;
            type = GL_INT;
            return GL_RG32I;
         case SF_1X4BYTE_FLOAT:
            format = GL_RED;
            type = GL_FLOAT;
            return GL_R32F;
         case SF_1X4BYTE_UINT:
            format = GL_RED_INTEGER;
            type = GL_UNSIGNED_INT;
            return GL_R32UI;
         case SF_1X4BYTE_SINT:
            format = GL_RED_INTEGER;
            type = GL_INT;
            return GL_R32I;
         case SF_4X2BYTE_UINT:
            format = GL_RGBA_INTEGER;
            type = GL_UNSIGNED_SHORT;
            return GL_RGBA16UI;
         case SF_4X2BYTE_SINT:
            format = GL_RGBA_INTEGER;
            type = GL_SHORT;
            return GL_RGBA16I;
         case SF_2X2BYTE_UINT:
            format = GL_RG_INTEGER;
            type = GL_UNSIGNED_SHORT;
            return GL_RG16UI;
         case SF_2X2BYTE_SINT:
            format = GL_RG_INTEGER;
            type = GL_SHORT;
            return GL_RG16I;
         case SF_1X2BYTE_UINT:
            format = GL_RED_INTEGER;
            type = GL_UNSIGNED_SHORT;
            return GL_R16UI;
         case SF_1X2BYTE_SINT:
            format = GL_RED_INTEGER;
            type = GL_SHORT;
            return GL_R16I;
         case SF_4X1BYTE_UINT:
            format = GL_RGBA_INTEGER;
            type = GL_UNSIGNED_BYTE;
            return GL_RGBA8UI;
         case SF_4X1BYTE_SINT:
            format = GL_RGBA_INTEGER;
            type = GL_BYTE;
            return GL_RGBA8I;
         case SF_2X1BYTE_UINT:
            format = GL_RG_INTEGER;
            type = GL_UNSIGNED_BYTE;
            return GL_RG8UI;
         case SF_2X1BYTE_SINT:
            format = GL_RG_INTEGER;
            type = GL_BYTE;
            return GL_RG8I;
         case SF_1X1BYTE_UINT:
            format = GL_RED_INTEGER;
            type = GL_UNSIGNED_BYTE;
            return GL_R8UI;
         case SF_1X1BYTE_SINT:
            format = GL_RED_INTEGER;
            type = GL_BYTE;
            return GL_R8I;
         case SF_DEPTH_STENCIL:
            format = GL_DEPTH_STENCIL;
            type = GL_FLOAT;
            return GL_DEPTH_STENCIL;
         case SF_DEPTH:
            format = GL_DEPTH_COMPONENT;
            type = GL_FLOAT;
            return GL_DEPTH;
         case SF_STENCIL:
            format = GL_STENCIL;
            type = GL_UNSIGNED_INT;
            return GL_DEPTH_STENCIL;
         }
      LOG("Structure format outside of range, using default...");
      format = GL_RGBA;
      type = GL_FLOAT;
      return GL_RGBA32F;
      }

   static GLuint _glTranFill(FillMode f)
      {
      switch(f)
         {
         case FM_SOLID:
            return GL_FILL;
         case FM_WIREFRAME:
            return GL_LINE;
         case FM_POINT:
            return GL_POINT;
         }
      LOG("Fill mode outside of range, using default...");
      return GL_FILL;
      }

   static GLuint _glTranAddress(TextureAddressMode t)
      {
      switch(t)
         {
         case TA_WRAP:
            return GL_REPEAT;
         case TA_MIRROR:
            return GL_MIRRORED_REPEAT;
         case TA_CLAMP:
            return GL_CLAMP_TO_EDGE;
         case TA_BORDER:
            return GL_CLAMP_TO_BORDER;
         case TA_MIRROR_ONCE:
            return GL_MIRROR_CLAMP_TO_EDGE;
         }
      LOG("Texture address mode outside of range, using default...");
      return GL_REPEAT;
      }

   static GLuint _glTranFilter(const TextureFilter& tf)
      {
      if(tf.linearMin)
         {
         if(tf.linearMip)
            return GL_LINEAR_MIPMAP_LINEAR;
         else
            return GL_LINEAR_MIPMAP_NEAREST;
         }
      else
         {
         if(tf.linearMip)
            return GL_NEAREST_MIPMAP_LINEAR;
         else
            return GL_NEAREST_MIPMAP_NEAREST;
         }
      }

   static GLuint _glTranCompare(TextureComparisonMethod t)
      {
      switch(t)
         {
         case TC_NEVER:
            return GL_NEVER;
         case TC_LESS:
            return GL_LESS;
         case TC_EQUAL:
            return GL_EQUAL;
         case TC_LESS_EQUAL:
            return GL_LEQUAL;
         case TC_GREATER:
            return GL_GREATER;
         case TC_NOT_EQUAL:
            return GL_NOTEQUAL;
         case TC_GREATER_EQUAL:
            return GL_GEQUAL;
         case TC_ALWAYS:
            return GL_ALWAYS;
         }
      LOG("Comparison func outside of range, using default...");
      return GL_NEVER;
      }

   static GLuint _glTranPrim(PrimitiveTopologyEnum p)
      {
      switch(p)
         {
         case PT_POINT_LIST:
            return GL_POINTS;
         case PT_LINE_LIST:
            return GL_LINES;
         case PT_LINE_STRIP:
            return GL_LINE_STRIP;
         case PT_TRIANGLE_LIST:
            return GL_TRIANGLES;
         case PT_TRIANGLE_STRIP:
            return GL_TRIANGLE_STRIP;
         case PT_LINE_LIST_ADJ:
            return GL_LINES_ADJACENCY;
         case PT_LINE_STRIP_ADJ:
            return GL_LINE_STRIP_ADJACENCY;
         case PT_TRIANGLE_LIST_ADJ:
            return GL_TRIANGLES_ADJACENCY;
         case PT_TRIANGLE_STRIP_ADJ:
            return GL_TRIANGLE_STRIP_ADJACENCY;
         }
      LOG("Primitive topology out of range, using default...");
      return GL_TRIANGLES;
      }
#endif
   }
#endif
