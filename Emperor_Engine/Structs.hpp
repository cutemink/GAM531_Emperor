#ifndef __EMP_STRUCTS_HPP__
#define __EMP_STRUCTS_HPP__

#include "Common.hpp"
#include "Types.hpp"
#include "Vertex.hpp"

namespace Emperor
   {
   struct MaterialPassDescription
      {
      uint32 loopCount;
      bool loopThroughLights;
      bool loopThroughOneLightType;
      LightType lightLoopType;

      MaterialPassDescriptionOptions useCamera;
      uint32 cameraSlot;
      MaterialPassDescriptionOptions useActor;
      uint32 actorSlot;
      MaterialPassDescriptionOptions useSingleLight;
      uint32 singleLightSlot;
      MaterialPassDescriptionOptions useMaterialBuffer;
      uint32 materialSlot;

      ArrayList<String> textures;
      ArrayList<MaterialPassDescriptionOptions> textureOptions;

      ArrayList<String> samplers;
      ArrayList<MaterialPassDescriptionOptions> samplerOptions;

      String blendState;

      String vertexFilename;
      String vertexFunction;

      String fragmentFilename;
      String fragmentFunction;

      Vertex vertexDef;
      };
   }

#endif