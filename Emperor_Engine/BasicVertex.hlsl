Texture1D _nodes : register(t0);
SamplerState _nSamp : register(s0);

float4x4 getTransform(uint actorID)
   {
   uint rp = actorID * 4;
   float4x4 tout;
   tout._11_21_31_41 = _nodes.SampleLevel(_nSamp, rp / 16384.0f, 0);
   tout._12_22_32_42 = _nodes.SampleLevel(_nSamp, (rp + 1) / 16384.0f, 0);
   tout._13_23_33_43 = _nodes.SampleLevel(_nSamp, (rp + 2)/ 16384.0f, 0);
   tout._14_24_34_44 = _nodes.SampleLevel(_nSamp, (rp + 3)/ 16384.0f, 0);
   return tout;
   }

cbuffer projMat : register(b0)
   {
   float4x4 projMat;
   }

struct Light
   {
   float4 diffuse;
   float4 specular;
   float4 attenuation;
   float3 spot;
   uint nID;
   uint type;
   uint3 padding;
   };

cbuffer singleLight : register(b1)
   {
   Light light;
   }

cbuffer actor : register(b2)
   {
   uint nodeID;
   uint3 padding;
   }

struct BasicVSInput
   {
   float3 position : POSITION;
   float3 normal : NORMAL;
   float2 uv : TEXCOORD0;
   };

struct BasicVSOutput
   {
   float4 position : SV_POSITION;
   float3 normal : NORMAL;
   float2 uv : TEXCOORD0;
   float4 fragPos : TEXCOORD1;
   float3 toLight : TEXCOORD2;
   };

BasicVSOutput BasicVertexShader(BasicVSInput vin)
   {
   BasicVSOutput vout = (BasicVSOutput)0;

   float4x4 worldView = getTransform(nodeID);
   float4x4 lightMat = getTransform(light.nID);

   vout.fragPos = mul(worldView, float4(vin.position, 1.0f));
   vout.position = mul(projMat,vout.fragPos);

   vout.toLight = lightMat._14_24_34 - vout.fragPos.xyz;


   vout.normal = mul((float3x3)worldView, vin.normal);

   vout.uv = vin.uv;

   return vout;
   }

struct PrePassVSOutput
   {
   float4 position : SV_POSITION;
   };

PrePassVSOutput PrePassVertexShader(BasicVSInput vin)
   {
   PrePassVSOutput vout;

   vout.position = mul(projMat, mul(getTransform(nodeID), float4(vin.position, 1.0f)));
   return vout;
   }