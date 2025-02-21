/**
* @file  CameraDccSystem.h
* @brief  DCC風カメラ（編集用カメラ）
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
	* @brief カメラ情報
	*/
	struct CameraInfomation
	{
		/**
		* @brief カメラ移動量
		*/
		DirectX::XMFLOAT2 mouseMove;

		/**
		* @brief カメラ前方ベクトル
		*/
		DirectX::XMVECTOR vCamFront;

		/**
		* @brief カメラ右ベクトル
		*/
		DirectX::XMVECTOR vCamSide;

		/**
		* @brief カメラ上方ベクトル
		*/
		DirectX::XMVECTOR vCamUp;

		/**
		* @brief カメラ位置ベクトル
		*/
		DirectX::XMVECTOR vCamPos;

		/**
		* @brief カメラ注視点ベクトル
		*/
		DirectX::XMVECTOR vCamLook;
	};

	/**
	* @brief 登録用システム名
	*/
	static constexpr const char* CAMERA_DCC_SYSTEM = "CameraDccSystem";

	/**
	* @brief コンストラクタ
	*/
	CameraDccSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
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
