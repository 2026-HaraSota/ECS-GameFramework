/**
* @file  CameraDccSystem.h
* @brief  DCC���J�����i�ҏW�p�J�����j
* @author Hara Sota.
* @date    2024/10/30.
*/
#ifndef _CAMERA_DCC_SYSTEM_H_
#define _CAMERA_DCC_SYSTEM_H_

#include <windows.h>
#include <DirectXMath.h>

#include "SystemBase.h"
#include "CameraSystemBase.h"
#include "Transform.h"
#include "IEntityOperator.h"
#include "IChunkProvider.h"

class SystemManager;

namespace HaraProject::Framework {

class CameraDccSystem : public CameraSystemBase
{
public:
	/**
	* @brief �J�������
	*/
	struct CameraInfomation
	{
		/**
		* @brief �J�����ړ���
		*/
		DirectX::XMFLOAT2 mouseMove;

		/**
		* @brief �J�����O���x�N�g��
		*/
		DirectX::XMVECTOR vCamFront;

		/**
		* @brief �J�����E�x�N�g��
		*/
		DirectX::XMVECTOR vCamSide;

		/**
		* @brief �J��������x�N�g��
		*/
		DirectX::XMVECTOR vCamUp;

		/**
		* @brief �J�����ʒu�x�N�g��
		*/
		DirectX::XMVECTOR vCamPos;

		/**
		* @brief �J���������_�x�N�g��
		*/
		DirectX::XMVECTOR vCamLook;
	};

	/**
	* @brief �o�^�p�V�X�e����
	*/
	static constexpr const char* CAMERA_DCC_SYSTEM = "CameraDccSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	CameraDccSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;

private:
	void UpdateState();
	void UpdateOrbit(CameraInfomation& cameraInfomation);
	void UpdateTrack(CameraInfomation& cameraInfomation);
	void UpdateDolly(CameraInfomation& cameraInfomation);
	void UpdateFlight(CameraInfomation& cameraInfomation);

private:
	int m_state;
	POINT m_old_position;
};
}// namespace HaraProject::Framework


#endif // !_CAMERA_DCC_SYSTEM_H_
