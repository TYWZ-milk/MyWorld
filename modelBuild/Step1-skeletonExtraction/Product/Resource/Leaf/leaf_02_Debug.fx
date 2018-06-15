
#define SMAP_SIZE 1024
#define SHADOW_EPSILON 0.001f

#define g_fDotNum 0.7f
#define g_f1 1.0f
#define g_fLightAmbient g_fDotNum

float4 g_vLightAmbient = float4( g_fLightAmbient, g_fLightAmbient, g_fLightAmbient, 1.0f );
float4 g_vLightDiffuse = float4( 1.0f, 1.0f, 1.0f, 1.0f );  // Light diffuse color

texture BackTex < string name = "back.bmp";>;
texture FrontTex < string name = "front.bmp";>;
texture HeightTex < string name = "height.bmp";>;
texture SpecularTex < string name = "Modelsspecular.bmp";>;
texture TransparentTex < string name = "translucency.bmp";>;

texture ShadowmapTex < string name = "ShadowMap";>;

float4x4 WorldView : worldview;
float4x4 Proj : projection;

float4x4 matViewToLightProj : ViewToLightProj;
float3 g_vLightPosition : lightposition;
float3 g_vLightDir : lightdirection;
float4 g_camerapos : cameraposition;

struct VS_OUTPUT
{
    float4 Pos : POSITION;
    float4 Spec : COLOR0;
    float2 tex : TEXCOORD0;
    float4 vPos : TEXCOORD1;
    float3 vNor : TEXCOORD2;
    float4 vPosLightProj : TEXCOORD3;
};

float3 CalcSpecular(float3 Position, float3 Normal)
{
    float3 EyeToVertex = normalize(Position);
    float3 R = normalize(reflect(g_vLightDir, Normal));
    return float3(0.1f, 0.1f, 0.1f) * pow(max(0, dot(R, -EyeToVertex)), 1);
}

VS_OUTPUT VS_Front(
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
    
    o.Spec.rgb = CalcSpecular(o.vPos, o.vNor);
    o.Spec.a = 1;
    
    return o;
}

VS_OUTPUT VS_Back(
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
    
    o.Spec.rgb = CalcSpecular(o.vPos, -o.vNor);
    o.Spec.a = 1;
    
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

sampler HeightMap = sampler_state
{
    texture = <HeightTex>;
    AddressU  = WRAP;
    AddressV  = WRAP;
    AddressW  = WRAP;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
};

sampler SpecularMap = sampler_state
{
    texture = <SpecularTex>;
    AddressU  = WRAP;
    AddressV  = WRAP;
    AddressW  = WRAP;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
};

sampler TransparentMap = sampler_state
{
    texture = <TransparentTex>;
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
    float4 front_color = tex2D(FrontMap, input.tex);
    float4 alpha_color = tex2D(TransparentMap, input.tex);

    alpha_color *= 1.7;

    col.rgb = front_color.rgb;
    col.a = (alpha_color.r + alpha_color.g + alpha_color.b)/3;
	
    return col;
};

float4 PS_LeafBack(VS_OUTPUT input) : COLOR
{
    float4 col;
    
    // sample front texture
    float4 back_color = tex2D(BackMap, input.tex);
    float4 alpha_color = tex2D(TransparentMap, input.tex);

    alpha_color *= 1.7;

    col.rgb = back_color.rgb;
    col.a = (alpha_color.r + alpha_color.g + alpha_color.b)/3;

   
    return col;
};


technique tec0
{
    pass p0
    {
        VertexShader = compile vs_2_0 VS_Front();
        PixelShader = compile ps_2_0 PS_LeafFront();

        FogEnable = false;
        ZEnable = true;
        ZWriteEnable = true;
        
        CullMode = CCW;
        
        // enable alpha blending
        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 0x80;
    }

    pass p1
    {
        VertexShader = compile vs_2_0 VS_Back();
        PixelShader = compile ps_2_0 PS_LeafBack();

        FogEnable = false;
        ZEnable = true;
        ZWriteEnable = true;
        
        CullMode = CW;
        
        // enable alpha blending
        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 0x80;
    }

}
