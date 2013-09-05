#include "APIShader.hpp"
#include "Engine.hpp"
#include "APITranslations.hpp"

namespace Emperor
   {
#if EMP_USE_DIRECTX
   APIVertexShader<RS_DX11>::~APIVertexShader()
      {
      if(vs)
         vs->Release();
      if(layout)
         layout->Release();
      }

   void APIVertexShader<RS_DX11>::init(const String& fileName, const String& function, const Vertex& v)
      {/*
      ID3D10Blob* sh = 0;
      ID3D10Blob* em = 0;

      if(FAILED(D3DX11CompileFromFile((fileName + ".hlsl").c_str(), 0, 0, function.c_str(),
         "vs_5_0", 1 << 15, 0, 0, &sh, &em, 0)))
         {
         EMP_DEVICE_ERROR((String("Shader Compilation failed for ") + fileName + "::" + function +
            " with vs_5_0\n  Error Message: " + String((char*)em->GetBufferPointer()) + "\n").c_str());
         }

      EMP_DEVICE_ASSERT_DX("create vertex shader", CreateVertexShader(sh->GetBufferPointer(), sh->GetBufferSize(), 0, &vs));

      D3D11_INPUT_ELEMENT_DESC* desc;
      auto ia = v.getVertexDescription();
      _dxTranVertex(ia, &desc);

      EMP_DEVICE_ASSERT_DX("construct vertex layout", CreateInputLayout(desc, ia.size(), sh->GetBufferPointer(), sh->GetBufferSize(), &layout));
      */
      }

   void APIVertexShader<RS_DX11>::initFromDef(const String& def, const String& function, const Vertex& v)
      {
      /*
      ID3D10Blob* sh = 0;
      ID3D10Blob* em = 0;

      if(FAILED(D3DX11CompileFromMemory(&(def.front()), def.size(), function.c_str(), 0, 0, function.c_str(),
         "vs_5_0", 1 << 15, 0, 0, &sh, &em, 0)))
         {
         EMP_DEVICE_ERROR((String("Shader Compilation failed for ") + function + "::" + function +
            " with vs_5_0\n  Error Message: " + String((char*)em->GetBufferPointer()) + "\n").c_str());
         }

      EMP_DEVICE_ASSERT_DX("create vertex shader", CreateVertexShader(sh->GetBufferPointer(), sh->GetBufferSize(), 0, &vs));

      D3D11_INPUT_ELEMENT_DESC* desc;
      auto ia = v.getVertexDescription();
      _dxTranVertex(ia, &desc);

      EMP_DEVICE_ASSERT_DX("construct vertex layout", CreateInputLayout(desc, ia.size(), sh->GetBufferPointer(), sh->GetBufferSize(), &layout));
      */
      }

   void APIVertexShader<RS_DX11>::bind()
      {
      /*
      Engine<RS_DX11>::getPtr()->_getPlatformDevice()._exposeContext()->VSSetShader(
         vs, 0, 0);
      Engine<RS_DX11>::getPtr()->_getPlatformDevice()._exposeContext()->IASetInputLayout(
         layout);
      */
      }

   APIFragmentShader<RS_DX11>::~APIFragmentShader()
      {
      if(fs)
         fs->Release();
      }

   void APIFragmentShader<RS_DX11>::init(const String& fileName, const String& function)
      {
      /*
      ID3D10Blob* sh = 0;
      ID3D10Blob* em = 0;

      if(FAILED(D3DX11CompileFromFile((fileName + ".hlsl").c_str(), 0, 0, function.c_str(),
         "ps_5_0", 1 << 15, 0, 0, &sh, &em, 0)))
         {
         EMP_DEVICE_ERROR((String("Shader Compilation failed for ") + fileName + "::" + function +
            " with ps_5_0\n  Error Message: " + String((char*)em->GetBufferPointer()) + "\n").c_str());
         }

      EMP_DEVICE_ASSERT_DX("construct fragment shader", CreatePixelShader(sh->GetBufferPointer(), sh->GetBufferSize(), 0, &fs));
      */
      }

   void APIFragmentShader<RS_DX11>::initFromDef(const String& def, const String& function)
      {
      /*
      ID3D10Blob* sh = 0;
      ID3D10Blob* em = 0;
      if(FAILED(D3DX11CompileFromMemory(def.c_str(), def.size(), function.c_str(), 0, 0, function.c_str(),
         "ps_5_0", 1 << 15, 0, 0, &sh, &em, 0)))
         {
         EMP_DEVICE_ERROR((String("Shader Compilation failed for ") + function + "::" + function +
            " with ps_5_0\n  Error Message: " + String((char*)em->GetBufferPointer()) + "\n").c_str());
         }

      EMP_DEVICE_ASSERT_DX("construct fragment shader", CreatePixelShader(sh->GetBufferPointer(), sh->GetBufferSize(), 0, &fs));
      */}

   void APIFragmentShader<RS_DX11>::bind()
      {
      /*Engine<RS_DX11>::getPtr()->_getPlatformDevice()._exposeContext()->PSSetShader(
         fs, 0, 0);*/
      }
#endif

#if EMP_USE_OPENGL
   static inline String _loadShader(const String& fn)
      {
      
      String shaderString;/*
      File vShader(fn + ".glsl", READFILE);
      if(!vShader)
         EMP_DEVICE_ERROR(String("Unable to open ") + fn + " for reading, using default...");
      
      String ts;
      while(vShader)
         {
         getLine(vShader, ts);
         shaderString += ts + "\n";
         }
      vShader.close();*/
      return shaderString;
      
      }

   void APIVertexShader<RS_GL43>::init(const String& fn, const String& fnc, const Vertex& v)
      {
      initFromDef(_loadShader(fn), fnc, v, fn);
      }

   void APIVertexShader<RS_GL43>::initFromDef(const String& def, const String& fnc, const Vertex& v, const String& fn)
      {/*
      //replace the function's name with main
      String nDef = def;
      findReplace(nDef, fnc, "main");

      vs = glCreateShader(GL_VERTEX_SHADER);

      auto c = nDef.c_str();
      glShaderSource(vs, 1, &c, 0);
      glCompileShader(vs);

      GLint r = GL_TRUE, l = 0;
      glGetShaderiv(vs, GL_COMPILE_STATUS, &r);
      glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &l);
      
      if(r != GL_TRUE)
         {
         String error;
         error.resize(l + 1);
         glGetShaderInfoLog(vs, l, 0, &error.front());
         EMP_DEVICE_ERROR((String("Shader Compilation failed for ") + fn + "::" + fnc +
            " with vs compiler\n  Error Message: " + error));
         }*/
      }

   void APIVertexShader<RS_GL43>::bind()
      {
      }

   void APIFragmentShader<RS_GL43>::init(const String& fn, const String& fnc)
      {
      //initFromDef(_loadShader(fn), fnc, fn);
      }

   void APIFragmentShader<RS_GL43>::initFromDef(const String& def, const String& fnc, const String& fn)
      {/*
      //replace the function's name with main
      String nDef = def;
      findReplace(nDef, fnc, "main");

      fs = glCreateShader(GL_FRAGMENT_SHADER);

      auto c = nDef.c_str();
      glShaderSource(fs, 1, &c, 0);
      glCompileShader(fs);

      GLint r = GL_TRUE, l = 0;
      glGetShaderiv(fs, GL_COMPILE_STATUS, &r);
      glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &l);
      
      if(r != GL_TRUE)
         {
         String error;
         error.resize(l + 1);
         glGetShaderInfoLog(fs, l, 0, &error.front());
         EMP_DEVICE_ERROR((String("Shader Compilation failed for ") + fn + "::" + fnc +
            " with fs compiler\n  Error Message: " + error));
         }
         */
      }

   void APIFragmentShader<RS_GL43>::bind()
      {

      }
#endif
   }
