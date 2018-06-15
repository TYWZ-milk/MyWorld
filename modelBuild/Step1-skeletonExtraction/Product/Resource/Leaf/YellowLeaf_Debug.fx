
#define SMAP_SIZE 1024
#define SHADOW_EPSILON 0.0005f

#define g_fDotNum 0.7f
#define g_f1 1.0f
#define g_fLightAmbient g_fDotNum

float4 g_vLightAmbient = float4( g_fLightAmbient, g_fLightAmbient, g_fLightAmbient, 1.0f );
float4 g_vLightDiffuse = float4( 1.0f, 1.0f, 1.0f, 1.0f );  // Light diffuse color

texture BackTex < string name = "YellowLeafBack.jpg";>;
texture FrontTex < string name = "YellowLeafFront.jpg";>;

texture ShadowmapTex < string name = "ShadowMap";>;

float4x4 WorldView : worldview;
float4x4 Proj : projection;

float4x4 matViewToLightProj : ViewToLightProj;
float3 g_vLightPosition : lightposition;
float3 g_vLightDir : lightdirection;

struct VS_OUTPUT
{
    float4 Pos : POSITION;
    float2 tex : TEXCOORD0;
    float4 vPos : TEXCOORD1;
    float3 vNor : TEXCOORD2;
    float4 vPosLightProj : TEXCOORD3;
};

VS_OUTPUT VS_Default(
    float4 pos : POSITION, 
    float3 nor : NORMAL, 
    float2 tex : TEXCOORD0)
{
    VS_OUTPUT o;

    o.vPos = mul(pos, WorldView);
    o.Pos = mul(o.vPos, Proj);
    o.tex = tex;
    o.vNor = mul(nor, (float3x3)WorldView);
    o.vPosLightProj = mul(o.vPos, matViewToLightProj);
    
    return o;
}

sampler BackMap = sampler_state
{
    texture = <BackTex>;
    AddressU  = WRAP;
    AddressV  = WRAP;
    AddressW  = WRAP;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
};

sampler FrontMap = sampler_state
{
    texture = <FrontTex>;
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

float4 PS_LeafFront(VS_OUTPUT input) : COLOR
{
    float4 col;
    
    // sample front texture
    col = tex2D(FrontMap, input.tex);
    col.a = 0.95;

    return col;
};

float4 PS_LeafBack(VS_OUTPUT input) : COLOR
{
    float4 col;
    
    // sample front texture
    col = tex2D(BackMap, input.tex);
    col.a = 0.95;

    return col;
};


technique tec0
{
    pass p0
    {
        VertexShader = compile vs_2_0 VS_Default();
        PixelShader = compile ps_2_0 PS_LeafFront();

        FogEnable = false;
        ZEnable = true;
        ZWriteEnable = true;
        
        CullMode = CCW;
        
        // enable alpha blending
        AlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        
        AlphaTestEnable = false;
        AlphaFunc = GreaterEqual;
        AlphaRef = 0x80;
    }

    pass p1
    {
        VertexShader = compile vs_2_0 VS_Default();
        PixelShader = compile ps_2_0 PS_LeafBack();

        FogEnable = false;
        ZEnable = true;
        ZWriteEnable = true;
        
        CullMode = CW;
        
        // enable alpha blending
        AlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        
        AlphaTestEnable = false;
        AlphaFunc = GreaterEqual;
        AlphaRef = 0x80;
    }

}
