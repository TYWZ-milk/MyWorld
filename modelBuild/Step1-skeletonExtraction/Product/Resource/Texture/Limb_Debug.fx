
#define SMAP_SIZE 1024
#define SHADOW_EPSILON 0.0005f

#define g_fDotNum 0.7f
#define g_f1 1.0f
#define g_fLightAmbient g_fDotNum

float4 g_vLightAmbient = float4( g_fLightAmbient, g_fLightAmbient, g_fLightAmbient, 1.0f );
float4 g_vLightDiffuse = float4( 1.0f, 1.0f, 1.0f, 1.0f );  // Light diffuse color

texture BarkTex < string name = "Tree-Bark-00042.jpg";>;
texture ShadowmapTex < string name = "ShadowMap";>;

float4x4 WorldView : worldview;
float4x4 Proj : projection;

float4x4 matViewToLightProj : ViewToLightProj;
float3 g_vLightPosition : lightposition;
float3 g_vLightDir : lightdirection;

struct VS_OUTPUT
{
    float4 Pos : POSITION;
    float4 diffuse : COLOR0;
    float2 tex : TEXCOORD0;
    float4 vPos : TEXCOORD1;
    float3 vNor : TEXCOORD2;
    float4 vPosLightProj : TEXCOORD3;
};

VS_OUTPUT VS_Default(
    float4 pos    : POSITION, 
    float3 nor    : NORMAL, 
    float4 vColor : COLOR0,
    float2 tex    : TEXCOORD0
    )
{
    VS_OUTPUT o;

    o.vPos = mul(pos, WorldView);
    o.Pos = mul(o.vPos, Proj);
    o.tex = tex;
    o.vNor = mul(nor, (float3x3)WorldView);
    o.vPosLightProj = mul(o.vPos, matViewToLightProj);
    o.diffuse = vColor;

    return o;
}

sampler LimbMap = sampler_state
{
    texture = <BarkTex>;
    AddressU  = WRAP;
    AddressV  = WRAP;
    AddressW  = WRAP;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
};

sampler ShadowMap = sampler_state
{
    texture = <ShadowmapTex>;
    AddressU  = clamp;
    AddressV  = clamp;
    AddressW  = clamp;
    MIPFILTER = point;
    MINFILTER = point;
    MAGFILTER = point;
};

float4 PS_Limb(VS_OUTPUT input) : COLOR
{
    float4 col;
    
    //texture
    col = tex2D(LimbMap, input.tex);

    if (input.diffuse.z < 0.9)
    {
        col = input.diffuse + col;
    }

    return col;
};


technique tec0
{
    pass p0
    {
        VertexShader = compile vs_2_0 VS_Default();
        PixelShader = compile ps_2_0 PS_Limb();

        FogEnable = false;
        ZEnable = true;
        ZWriteEnable = true;
        
        CullMode = CCW;
        AlphaBlendEnable = false;
        AlphaTestEnable = false;
    }
}
