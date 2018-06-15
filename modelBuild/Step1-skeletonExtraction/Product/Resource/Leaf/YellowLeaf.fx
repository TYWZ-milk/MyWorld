
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

    // vLight is the unit vector from the light to this pixel
    float3 vLight = normalize( float3( input.vPos - g_vLightPosition ) );

    if ( dot( vLight, g_vLightDir ) > 0 ) // Light must face the pixel
    {
        // Pixel is in lit area. Find out if it's
        // in shadow using 2x2 percentage closest filtering

        //transform from RT space to texture space.
        float2 ShadowTexC = 0.5 * input.vPosLightProj.xy / input.vPosLightProj.w + float2( 0.5, 0.5 );
        ShadowTexC.y = 1.0f - ShadowTexC.y;
        
        // transform to texel space
        float2 texelpos = SMAP_SIZE * ShadowTexC;

        // Determine the lerp amounts
        float2 lerps = frac( texelpos );

        //read in bilerp stamp, doing the shadow checks
        float sourcevals[4];
        sourcevals[0] = (tex2D( ShadowMap, ShadowTexC ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;
        sourcevals[1] = (tex2D( ShadowMap, ShadowTexC + float2(1.0/SMAP_SIZE, 0) ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;
        sourcevals[2] = (tex2D( ShadowMap, ShadowTexC + float2(0, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;
        sourcevals[3] = (tex2D( ShadowMap, ShadowTexC + float2(1.0/SMAP_SIZE, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;

        // lerp between the shadow values to calculate our light amount
        float LightAmount = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
                                  lerp( sourcevals[2], sourcevals[3], lerps.x ),
                                  lerps.y );

        // Light it
        col = col * ( 
			saturate( dot( -vLight, normalize( input.vNor ) ) )  * 
			LightAmount * ( 1 - g_vLightAmbient ) + g_vLightAmbient
			);
    }
    else
    {
		col = col * g_vLightAmbient;
    }
    
    return col;
};

float4 PS_LeafBack(VS_OUTPUT input) : COLOR
{
    float4 col;
    
    // sample front texture
    col = tex2D(BackMap, input.tex);
    col.a = 0.95;

    // vLight is the unit vector from the light to this pixel
    float3 vLight = normalize( float3( input.vPos - g_vLightPosition ) );

    if ( dot( vLight, g_vLightDir ) > 0 ) // Light must face the pixel
    {
        // Pixel is in lit area. Find out if it's
        // in shadow using 2x2 percentage closest filtering

        //transform from RT space to texture space.
        float2 ShadowTexC = 0.5 * input.vPosLightProj.xy / input.vPosLightProj.w + float2( 0.5, 0.5 );
        ShadowTexC.y = 1.0f - ShadowTexC.y;
        
        // transform to texel space
        float2 texelpos = SMAP_SIZE * ShadowTexC;

        // Determine the lerp amounts
        float2 lerps = frac( texelpos );

        //read in bilerp stamp, doing the shadow checks
        float sourcevals[4];
        sourcevals[0] = (tex2D( ShadowMap, ShadowTexC ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;
        sourcevals[1] = (tex2D( ShadowMap, ShadowTexC + float2(1.0/SMAP_SIZE, 0) ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;
        sourcevals[2] = (tex2D( ShadowMap, ShadowTexC + float2(0, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;
        sourcevals[3] = (tex2D( ShadowMap, ShadowTexC + float2(1.0/SMAP_SIZE, 1.0/SMAP_SIZE) ) + SHADOW_EPSILON < input.vPosLightProj.z / input.vPosLightProj.w)? 0.0f: 1.0f;

        // lerp between the shadow values to calculate our light amount
        float LightAmount = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
                                  lerp( sourcevals[2], sourcevals[3], lerps.x ),
                                  lerps.y );

        // Light it
        col = col * ( 
			saturate( dot( -vLight, normalize( input.vNor ) ) )  * 
			LightAmount * ( 1 - g_vLightAmbient ) + g_vLightAmbient
			);
    }
    else
    {
		col = col * g_vLightAmbient;
    }

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
