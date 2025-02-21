/**
* @file   CameraSystemBase.h
* @brief  カメラシステム基底クラス定義.
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
	* @brief デフォルトの縦視野角
	*/
	static constexpr float FOVY_DEFAULT = 60.0f;

	/**
	* @brief デフォルトのビュー横幅
	*/
	static constexpr float WIDTH_DEFAULT = 20.0f;

	/**
	* @brief デフォルトのアスペクト比
	*/
	static constexpr float ASPECT_DEFAULT = 16.0f / 9.0f;

	/**
	* @brief デフォルトの境界前面
	*/
	static constexpr float NEAR_DEFAULT = 0.2f;

	/**
	* @brief デフォルトの境界後方
	*/
	static constexpr float FAR_DEFAULT = 10000.0f;

	/**
	* @brief デフォルトの焦点距離
	*/
	static constexpr float FOCUS_DEFAULT = 1.0f;

	/**
	* @brief コンストラクタ
	*/
	CameraSystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);
	
	/**
	* @brief デストラクタ
	*/
	~CameraSystemBase();

	/**
	* @brief ビュー変換行列取得
	*/
	DirectX::XMFLOAT4X4 GetViewMatrix(bool isTranspose = true);

	/**
	* @brief プロジェクション変換行列取得
	*/
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool isTranspose = true);

	/**
	* @brief 注視点取得
	*/
	DirectX::XMFLOAT3 GetLook();

	/**
	* @brief 前方ベクトル取得
	*/
	DirectX::XMFLOAT3 GetFront();

	/**
	* @brief 右方向ベクトル取得
	*/
	DirectX::XMFLOAT3 GetRight();

	/**
	* @brief 上方向ベクトル取得
	*/
	DirectX::XMFLOAT3 GetUp();

	/**
	* @brief 3D用か
	*/
	bool Is3D() {
		return m_is_3d;
	}

	/**
	* @brief 視野角取得
	*/
	float GetFovy() {
		return DirectX::XMConvertToRadians(m_fovy);
	}

	/**
	* @brief 横幅取得
	*/
	float GetWidth() {
		return m_width;
	}

	/**
	* @brief 最前面取得
	*/
	float GetNear() {
		return m_near;
	}

	/**
	* @brief 最奥面取得
	*/
	float GetFar() {
		return m_far;
	}

	/**
	* @brief アスペクト比取得
	*/
	float GetAspect() {
		return m_aspect;
	}

	/**
	* @brief 焦点距離取得
	*/
	float GetFocus() {
		return m_focus;
	}

	/**
	* @brief 位置取得
	*/
	DirectX::XMFLOAT3 GetPosition() {
		return m_position;
	}

	/**
	* @brief 位置設定
	* @param[in] position 座標
	*/
	void SetPosition(DirectX::XMFLOAT3 position) {
		m_position = position;
	}

	/**
	* @brief プロジェクション設定
	* @param[in] is3D 透視投影か
	*/
	void SetIs3D(bool is3D) {
		m_is_3d = is3D;
	}

protected:
	/**
	* @brief 3D用カメラか
	*/
	bool m_is_3d;

	/**
	* @brief 縦方向の視野角
	*/
	float m_fovy;

	/**
	* @brief ビュー幅
	*/
	float m_width;

	/**
	* @brief アスペクト比（幅/高さ）
	*/
	float m_aspect;

	/**
	* @brief 前面の境界
	*/
	float m_near;

	/**
	* @brief 後面の境界
	*/
	float m_far;

	/**
	* @brief 焦点距離
	*/
	float m_focus;

	/**
	* @brief 位置
	*/
	DirectX::XMFLOAT3 m_position;

	/**
	* @brief 回転
	*/
	DirectX::XMFLOAT4 m_quaternion;
};
}// namespace HaraProject::Framework

#endif // !_CAMERA_SYSTEM_BASE_H_