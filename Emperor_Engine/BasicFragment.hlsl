struct Light
   {
   float4 diffuse;
   float4 specular;
   float4 attenuation;
   float3 spot;
   uint nID;
   uint type;
   };

cbuffer singleLight : register(b1)
   {
   Light light;
   }

Texture2D diff1 : register(t1);
Texture2D amb1 : register(t2);
Texture2D spec1 : register(t3);
SamplerState samp1 : register(s1);

struct BasicFSInput
   {
   float4 position : SV_POSITION;
   float3 normal : NORMAL;
   float2 uv : TEXCOORD0;
   float4 fragPos : TEXCOORD1;
   float3 toLight : TEXCOORD2;
   };

cbuffer material : register(b3)
   {
   float specular;
   float shininess;
   }

float4 BasicFragmentShader(BasicFSInput fin) : SV_Target
   {
   float4 dTexel = diff1.Sample(samp1, fin.uv);
   float4 aTexel = amb1.Sample(samp1, fin.uv);
   float4 sTexel = spec1.Sample(samp1, fin.uv);

   float3 lightDir = normalize(fin.toLight);
   float3 n = normalize(fin.normal);
   float NdotL = max(dot(n, lightDir),0.0);
   float4 col = mul(NdotL, light.diffuse);
   float4 ambContrib = aTexel;
   float4 diffContrib = dTexel * col;

   float3 refl = mul(2.0 * NdotL, n) + lightDir;
   float NdotR = max(dot(normalize(refl), normalize(-fin.fragPos.xyz)),0.0);
   float4 specContrib = mul(sTexel, specular * pow(NdotR, shininess));

   return ambContrib + diffContrib + specContrib;
   }


struct PrePassFSInput
   {
   float4 position : SV_POSITION;
   };

float4 PrePassFragmentShader(PrePassFSInput fin) : SV_Target
   {
   return float4(0,0,0,1);
   }
