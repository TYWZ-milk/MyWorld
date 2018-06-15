
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

		col = col + input.Spec;
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
    float4 back_color = tex2D(BackMap, input.tex);
    float4 alpha_color = tex2D(TransparentMap, input.tex);

    alpha_color *= 1.7;

    col.rgb = back_color.rgb;
    col.a = (alpha_color.r + alpha_color.g + alpha_color.b)/3;

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

		col = col + input.Spec;
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
