// PS_RimLight.hlsl

struct PS_IN
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 worldPos : TEXCOORD1;
};

// テクスチャを受け取る
Texture2D tex : register(t0);
SamplerState samp : register(s0); // テクスチャの繰り返し設定

// 定数バッファ
cbuffer LightBuf : register(b0)
{
    float4 lightDir; // xyz: 光の方向, w: 環境光の強さ
    float4 lightColor;
};

cbuffer CameraBuf : register(b1)
{
    float3 cameraPos;
    float camDummy;
};

float4 main(PS_IN pin) : SV_TARGET
{
    float ambientForce = lightDir.w;
    
    // 各ベクトルの正規化
    float3 L = normalize(-lightDir.xyz); // 光の方向を反転
    float3 N = normalize(pin.normal);
    float3 V = normalize(cameraPos - pin.worldPos.xyz); // 視線方向
    float3 R = reflect(-L, N); // 反射ベクトル

    // リムライトの計算
    float power1 = 1.0f - max(0.0f, dot(L, N));
    float power2 = 1.0f - max(0.0f, dot(V, N));
    float rimPower = pow(power1 * power2, 1.3f);
    float3 rimColor = rimPower * lightColor.rgb * 0.5f; // リムライトを調整

    // 鏡面反射の計算
    float specularStrength = max(0.0f, dot(R, V));
    specularStrength = pow(specularStrength, 7.0f);
    float3 specularLig = lightColor.rgb * specularStrength;

    // 拡散反射の計算
    float diffuseStrength = max(0.0f, dot(N, L));
    float3 diffuseLig = lightColor.rgb * diffuseStrength;

    // 環境光の適用
    float3 ambientLig = float3(ambientForce, ambientForce, ambientForce);

    // 最終的な光の合成
    float3 finalLig = diffuseLig + ambientLig + specularLig + rimColor;

    // テクスチャ適用
    float4 finalColor = tex.Sample(samp, pin.uv);
    finalColor.xyz *= finalLig;

    return finalColor;
}
