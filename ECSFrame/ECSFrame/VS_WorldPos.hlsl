// VS_Object.hlsl

// �C���v�b�g���C�A�E�g
// CPU����n����钸�_�̏����`��������
struct VS_IN
{
	float3 pos : POSITION0;		// �Z�}���e�B�N�X
	float3 normal : NORMAL0;	// �f�[�^�̗p�r���`����
	float2 uv : TEXCOORD0;
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�֑���f�[�^�̒�`
struct VS_OUT
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : TEXCOORD1;
};

// �萔�o�b�t�@
// CPU��GPU�ł���肷��A���_�ȊO�̃f�[�^���i�[�����
cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	// ���[�J�����W���X�N���[�����W�֕ϊ�
	vout.pos = float4(vin.pos, 1.0f);	// ���[�J�����W
	vout.pos = mul(vout.pos, world);	// ���[���h���W
	vout.worldPos = vout.pos;
	vout.pos = mul(vout.pos, view);		// �r���[���W
	vout.pos = mul(vout.pos, proj);		// �v���W�F�N�V�������W

	// �s�N�Z���V�F�[�_�[�ŗ��p����UV���W��n��
	vout.uv = vin.uv;

	// float3x3 �́A�g�k���l�����Ȃ��@���̌v�Z
	vout.normal = mul(vin.normal, (float3x3)world);
	// x,y,z�ł��ꂼ��Ⴄ�g�k�̏ꍇ�A��L�̌v�Z�ł͐������@�����v�Z�ł��Ȃ��B
	// ��CPU�Ŏ��O�Ɍv�Z���ēn���K�v������B
	// �Ⴆ�Ή��ɐL�΂��g����s�����Ƃ��A�΂ߕ����̖@���͉��ɐL�т�̂ł͂Ȃ��A
	// �c�ɐL�тȂ���΂��������B
	// ���ɒ[�Șb�A�����ɉ��ɉ��΂��Ώ�����������ʂɂȂ�͂��B
	// �����ŁA�g�k�̂ݍs��̐�����ł������t�s��Ƃ��邱�ƂŐ������@�����v�Z�ł���
	// �菇�j
	// �P�D��]�Ɗg�k���܂܂ꂽ�s��̋t�s����v�Z����B
	// �Q�D�P�Ōv�Z���ꂽ�t�s���]�u����B
	// �����s��̋t�s��͓]�u�s��̌��ʂƓ������B
	

	return vout;
}