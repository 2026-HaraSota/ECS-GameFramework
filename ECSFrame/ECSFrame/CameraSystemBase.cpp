#include <DirectXMath.h>

#include "CameraSystemBase.h"
#include "SystemBase.h"
#include "Transform.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
CameraSystemBase::CameraSystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
	, m_is_3d(true)
	, m_fovy(FOVY_DEFAULT), m_width(WIDTH_DEFAULT)
	, m_aspect(ASPECT_DEFAULT), m_near(NEAR_DEFAULT), m_far(FAR_DEFAULT)
	, m_focus(FOCUS_DEFAULT)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_quaternion(0.0f, 0.0f, 0.0f, 1.0f)
{
}

/**
* @brief デストラクタ
*/
CameraSystemBase::~CameraSystemBase()
{
}

/**
* @brief ビュー変換行列取得
*/
DirectX::XMFLOAT4X4 CameraSystemBase::GetViewMatrix(bool isTranspose)
{
	DirectX::XMFLOAT3 pos = m_position;
	DirectX::XMFLOAT3 look = GetLook();
	DirectX::XMFLOAT3 up(0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR vLook = DirectX::XMLoadFloat3(&look);
	DirectX::XMVECTOR vUp = DirectX::XMLoadFloat3(&up);
	DirectX::XMMATRIX mat = DirectX::XMMatrixLookAtLH(vPos, vLook, vUp);
	if (isTranspose)
		mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fmat;
	DirectX::XMStoreFloat4x4(&fmat, mat);
	return fmat;
}

/**
* @brief プロジェクション変換行列取得
*/
DirectX::XMFLOAT4X4 CameraSystemBase::GetProjectionMatrix(bool isTranspose)
{
	DirectX::XMMATRIX mat;
	if (m_is_3d) {
		mat = DirectX::XMMatrixPerspectiveFovLH(GetFovy(), m_aspect, m_near, m_far);
	}
	else {
		mat = DirectX::XMMatrixOrthographicLH(m_width, m_width / m_aspect, m_near, m_far);
	}
	if (isTranspose)
		mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fmat;
	DirectX::XMStoreFloat4x4(&fmat, mat);
	return fmat;
}

/**
* @brief 注視点取得
*/
DirectX::XMFLOAT3 CameraSystemBase::GetLook()
{
	// 位置の取得
	DirectX::XMFLOAT3 pos = m_position;
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&pos);

	// 前方ベクトル取得
	DirectX::XMFLOAT3 front = GetFront();
	DirectX::XMVECTOR vFront = DirectX::XMLoadFloat3(&front);

	// カメラの位置からフォーカス距離まで進んだ位置を注視点とする
	vFront = DirectX::XMVectorScale(vFront, m_focus);
	DirectX::XMVECTOR vLook = DirectX::XMVectorAdd(vPos, vFront);

	DirectX::XMStoreFloat3(&pos, vLook);
	return pos;
}

/**
* @brief 前方ベクトル取得
*/
DirectX::XMFLOAT3 CameraSystemBase::GetFront()
{
	DirectX::XMVECTOR vFront = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	vFront = DirectX::XMVector3Rotate(vFront, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vFront));
	return dir;
}

/**
* @brief 右方向ベクトル取得
*/
DirectX::XMFLOAT3 CameraSystemBase::GetRight()
{
	DirectX::XMVECTOR vRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	vRight = DirectX::XMVector3Rotate(vRight, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vRight));
	return dir;
}

/**
* @brief 上方向ベクトル取得
*/
DirectX::XMFLOAT3 CameraSystemBase::GetUp()
{
	DirectX::XMVECTOR vUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	vUp = DirectX::XMVector3Rotate(vUp, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, vUp);
	return dir;
}

}// namespace HaraProject::Framework
