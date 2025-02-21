// PS_RimLight.hlsl

struct PS_IN
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 worldPos : TEXCOORD1;
};

// �e�N�X�`�����󂯎��
Texture2D tex : register(t0);
SamplerState samp : register(s0); // �e�N�X�`���̌J��Ԃ��ݒ�

// �萔�o�b�t�@
cbuffer LightBuf : register(b0)
{
    float4 lightDir; // xyz: ���̕���, w: �����̋���
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
    
    // �e�x�N�g���̐��K��
    float3 L = normalize(-lightDir.xyz); // ���̕����𔽓]
    float3 N = normalize(pin.normal);
    float3 V = normalize(cameraPos - pin.worldPos.xyz); // ��������
    float3 R = reflect(-L, N); // ���˃x�N�g��

    // �������C�g�̌v�Z
    float power1 = 1.0f - max(0.0f, dot(L, N));
    float power2 = 1.0f - max(0.0f, dot(V, N));
    float rimPower = pow(power1 * power2, 1.3f);
    float3 rimColor = rimPower * lightColor.rgb * 0.5f; // �������C�g�𒲐�

    // ���ʔ��˂̌v�Z
    float specularStrength = max(0.0f, dot(R, V));
    specularStrength = pow(specularStrength, 7.0f);
    float3 specularLig = lightColor.rgb * specularStrength;

    // �g�U���˂̌v�Z
    float diffuseStrength = max(0.0f, dot(N, L));
    float3 diffuseLig = lightColor.rgb * diffuseStrength;

    // �����̓K�p
    float3 ambientLig = float3(ambientForce, ambientForce, ambientForce);

    // �ŏI�I�Ȍ��̍���
    float3 finalLig = diffuseLig + ambientLig + specularLig + rimColor;

    // �e�N�X�`���K�p
    float4 finalColor = tex.Sample(samp, pin.uv);
    finalColor.xyz *= finalLig;

    return finalColor;
}
