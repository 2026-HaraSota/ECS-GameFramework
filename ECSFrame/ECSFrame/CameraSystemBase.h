/**
* @file   CameraSystemBase.h
* @brief  �J�����V�X�e�����N���X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _CAMERA_SYSTEM_BASE_H_
#define _CAMERA_SYSTEM_BASE_H_

#include <DirectXMath.h>

#include "SystemBase.h"
#include "Transform.h"
#include "IEntityOperator.h"
#include "IChunkProvider.h"

namespace HaraProject::Framework {
class ISystemDistributor;
class CameraSystemBase : public SystemBase
{
public:
	/**
	* @brief �f�t�H���g�̏c����p
	*/
	static constexpr float FOVY_DEFAULT = 60.0f;

	/**
	* @brief �f�t�H���g�̃r���[����
	*/
	static constexpr float WIDTH_DEFAULT = 20.0f;

	/**
	* @brief �f�t�H���g�̃A�X�y�N�g��
	*/
	static constexpr float ASPECT_DEFAULT = 16.0f / 9.0f;

	/**
	* @brief �f�t�H���g�̋��E�O��
	*/
	static constexpr float NEAR_DEFAULT = 0.2f;

	/**
	* @brief �f�t�H���g�̋��E���
	*/
	static constexpr float FAR_DEFAULT = 10000.0f;

	/**
	* @brief �f�t�H���g�̏œ_����
	*/
	static constexpr float FOCUS_DEFAULT = 1.0f;

	/**
	* @brief �R���X�g���N�^
	*/
	CameraSystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);
	
	/**
	* @brief �f�X�g���N�^
	*/
	~CameraSystemBase();

	/**
	* @brief �r���[�ϊ��s��擾
	*/
	DirectX::XMFLOAT4X4 GetViewMatrix(bool isTranspose = true);

	/**
	* @brief �v���W�F�N�V�����ϊ��s��擾
	*/
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool isTranspose = true);

	/**
	* @brief �����_�擾
	*/
	DirectX::XMFLOAT3 GetLook();

	/**
	* @brief �O���x�N�g���擾
	*/
	DirectX::XMFLOAT3 GetFront();

	/**
	* @brief �E�����x�N�g���擾
	*/
	DirectX::XMFLOAT3 GetRight();

	/**
	* @brief ������x�N�g���擾
	*/
	DirectX::XMFLOAT3 GetUp();

	/**
	* @brief 3D�p��
	*/
	bool Is3D() {
		return m_is_3d;
	}

	/**
	* @brief ����p�擾
	*/
	float GetFovy() {
		return DirectX::XMConvertToRadians(m_fovy);
	}

	/**
	* @brief �����擾
	*/
	float GetWidth() {
		return m_width;
	}

	/**
	* @brief �őO�ʎ擾
	*/
	float GetNear() {
		return m_near;
	}

	/**
	* @brief �ŉ��ʎ擾
	*/
	float GetFar() {
		return m_far;
	}

	/**
	* @brief �A�X�y�N�g��擾
	*/
	float GetAspect() {
		return m_aspect;
	}

	/**
	* @brief �œ_�����擾
	*/
	float GetFocus() {
		return m_focus;
	}

	/**
	* @brief �ʒu�擾
	*/
	DirectX::XMFLOAT3 GetPosition() {
		return m_position;
	}

	/**
	* @brief �ʒu�ݒ�
	* @param[in] position ���W
	*/
	void SetPosition(DirectX::XMFLOAT3 position) {
		m_position = position;
	}

	/**
	* @brief �v���W�F�N�V�����ݒ�
	* @param[in] is3D �������e��
	*/
	void SetIs3D(bool is3D) {
		m_is_3d = is3D;
	}

protected:
	/**
	* @brief 3D�p�J������
	*/
	bool m_is_3d;

	/**
	* @brief �c�����̎���p
	*/
	float m_fovy;

	/**
	* @brief �r���[��
	*/
	float m_width;

	/**
	* @brief �A�X�y�N�g��i��/�����j
	*/
	float m_aspect;

	/**
	* @brief �O�ʂ̋��E
	*/
	float m_near;

	/**
	* @brief ��ʂ̋��E
	*/
	float m_far;

	/**
	* @brief �œ_����
	*/
	float m_focus;

	/**
	* @brief �ʒu
	*/
	DirectX::XMFLOAT3 m_position;

	/**
	* @brief ��]
	*/
	DirectX::XMFLOAT4 m_quaternion;
};
}// namespace HaraProject::Framework

#endif // !_CAMERA_SYSTEM_BASE_H_