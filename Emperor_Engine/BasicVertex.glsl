#version 430

layout(binding = 0) uniform sampler1D _nodes;

mat4 getTransform(uint actorID)
   {
   uint rp = actorID * 4;
   mat4 tout = mat4(texture(_nodes, rp /  16384.0f).rgba,
      texture(_nodes, (rp + 1) /  16384.0f).rgba,
      texture(_nodes, (rp + 2) /  16384.0f).rgba,
      texture(_nodes, (rp + 3) /  16384.0f).rgba);

   return tout;
   }

layout (std140, binding = 8) uniform projMatUniform
   {
   mat4 projMat;
   };

struct Light
   {
   vec4 diffuse;
   vec4 specular;
   vec4 attenuation;
   vec3 spot;
   uint nID;
   uint type;
   };

layout (std140, binding = 9) uniform singleLight
   {
   Light light;
   };

layout (std140, binding = 10) uniform actor
   {
   uint nodeID;
   };

struct BasicVSOutput
   {
   vec4 position;
   vec3 normal;
   vec2 uv;
   vec4 fragPos;
   vec3 toLight;
   };

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(location = 0) out BasicVSOutput vout;

void BasicVertexShader() 
   {
   mat4 worldView = getTransform(nodeID);
   mat4 lightMat = getTransform(light.nID);

   vout.fragPos = worldView * vec4(position.x, position.y, position.z, 1.0f);
   vout.position = vout.fragPos * projMat;

   vout.toLight = lightMat[3].xyz - vout.fragPos.xyz;

   vout.normal = mat3(worldView) * normal;

   vout.uv = uv;

   gl_Position = vout.position;
   }

void PrePassVertexShader()
   {
   vout.position = getTransform(nodeID) * vec4(position.x, position.y, position.z, 1.0f) * projMat;
   gl_Position = vout.position;
   }

