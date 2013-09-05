#version 430

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

struct BasicFSInput
   {
   vec4 position;
   vec3 normal;
   vec2 uv;
   vec4 fragPos;
   vec3 toLight;
   };

layout(binding = 1) uniform sampler2D diff1;
layout(binding = 2) uniform sampler2D amb1;
layout(binding = 3) uniform sampler2D spec1;

layout (location = 0) in BasicFSInput fin;
layout (location = 0) out vec4 color;

layout(std140, binding = 10) uniform material
   {
   float specular;
   float shininess;
   };

void BasicFragmentShader()
   {
   vec4 dTexel = texture(diff1, fin.uv).rgba;
   vec4 aTexel = texture(amb1, fin.uv).rgba;
   vec4 sTexel = texture(spec1,fin.uv).rgba;

   vec3 lightDir = normalize(fin.toLight);
   vec3 n = normalize(fin.normal);
   float NdotL = max(dot(n, lightDir),0.0);
   vec4 col = NdotL * light.diffuse;
   vec4 ambContrib = aTexel;
   vec4 diffContrib = dTexel * col;

   vec3 refl = 2.0 * NdotL * n + lightDir;
   float NdotR = max(dot(normalize(refl), normalize(-fin.fragPos.xyz)),0.0);
   float specContrib = sTexel * specular * pow(NdotR, shininess);

   color = ambContrib + diffContrib + specContrib;
   }

void PrePassFragmentShader() 
   {
   color = vec4(0,0,0,1);
   }
