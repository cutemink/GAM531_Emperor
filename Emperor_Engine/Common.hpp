#ifndef __EMPEROR_COMMON_HPP__
#define __EMPEROR_COMMON_HPP__


#include <cstdint>
#include <string>
#include <stdarg.h>
#include <vector>
#include <list>
#include <tuple>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <queue>

#include "Utilities.hpp"
#include "Errors.hpp"
#include "Defaults.hpp"

namespace Emperor
   {

   //handy typedefs
   typedef std::string String;
   typedef std::stringstream StringStream;
   typedef uint32_t uint32;
   typedef uint16_t uint16;
   typedef uint8_t uint8;
   typedef uint8 byte;
   typedef std::fstream File;

   //handy defines
#define HashMap std::map
#define Pair std::pair
#define ArrayList std::vector
#define Queue std::queue
#define LinkedList std::list
#define searchList std::find
#define sortList std::sort
#define getLine std::getline
#define boolText std::boolalpha
#define boolInt std::noboolalpha
#define NEWFILE std::ios_base::in | std::ios_base::out | std::ios_base::trunc
#define READFILE std::ios::in

   //handy macros
#define NO_VIRT(type, ptr, fnc) ((type*)(ptr))->type::fnc

#define MAX_NODES 4096
#define NODE_SIZE 64

   //handy enums
   enum RenderSystem
      {
      RS_DX11,
      RS_GL43
      };
   
   }//end of namespace
   //File names and locations
#define EMP_SETTINGS_FILE "settings.ini"


   //Basic and temporary log system
#define LOG(m) std::cout << m << std::endl

#define EMP_ERROR(m) throw(Exception(m))
#define EMP_FATAL_ERROR(m) throw(FatalException(m))
#define EMP_DEVICE_ERROR(m) throw(DeviceFailureException(m))
#define EMP_INIT_ERROR(m) throw(DeviceInitFailureException(m))
#define EMP_RESOURCE_ERROR(m) throw(ResourceLoadFailException(m))
#define EMP_NOT_IMP_ERROR(m) throw(NotImplementedException(m))

   //Specialized Errors
#define EMP_DEVICE_ASSERT_DX(d, f) {HRESULT er;\
   if(FAILED(er = Engine<RS_DX11>::getPtr()->_getPlatformDevice()._exposeDevice()->f))\
   throw(DeviceFailureException(String("Failed to ") + d + \
   " in DirectX 11\n   Error code: " + std::to_string(er)));}

#define EMP_CONTEXT_ASSERT_DX(d, f) {HRESULT er;\
   if(FAILED(er = Engine<RS_DX11>::getPtr()->_getPlatformDevice()._exposeContext()->f))\
   throw(DeviceFailureException(String("Failed to ") + d + \
   " in DirectX 11\n   Error code: " + std::to_string(er)));}

#define EMP_INIT_ASSERT_DX(d, f) {HRESULT er;\
   if(FAILED(er = f))\
   throw(DeviceInitFailureException(String("Failed to ") + d + \
   " in DirectX 11\n   Error code: " + std::to_string(er)));}

#define EMP_INIT_ASSERT_GL(d, f) {GLenum er = f;\
   if(f != GLEW_OK)\
   throw(DeviceInitFailureException(String("Failed to ") + d + \
   " in OpenGL 4.3\n   Error code: " + (char*)glewGetErrorString(er)));}

#include "Vector.hpp"

#define ON 1
#define OFF 0

   //Platform Specification
   //Defined in project

   //Graphics Backend
   //Defined in project

#if EMP_USE_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include "PlatformMS.hpp"
#endif

// TODO this needs to be removed at some point
//#define PLATFORM_UVW(uvw) uvw.y() = 1 - uvw.y();
#if EMP_USE_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#endif

#if EMP_USE_OPENGL
#include "GL/glew.h"
#include "GL/wglew.h"
#include "SOIL/SOIL.h"

#endif
#endif
