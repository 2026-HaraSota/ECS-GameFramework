#include <DirectXMath.h>

#include "CameraSystemBase.h"
#include "Input.h"

#include "CameraDccSystem.h"

namespace HaraProject::Framework {

/**
* @brief 操作状態
*/
enum CameraDCCKind
{
	CAM_DCC_NONE = 0,
	CAM_DCC_ORBIT,
	CAM_DCC_TRACK,
	CAM_DCC_DOLLY,
	CAM_DCC_FLIGHT,
};

/**
* @brief コンストラクタ
*/
CameraDccSystem::CameraDccSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: CameraSystemBase(entityOperator, systemDistributor, chunkProvider)
	, m_state(CAM_DCC_NONE)
	, m_old_position{ 0, 0 }
{
}

void CameraDccSystem::UpdateSystem(float deltaTime)
{
	UpdateState();
	if (m_state == CAM_DCC_NONE) return;

	CameraInfomation camera_infomation;
	// マウス移動量
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	camera_infomation.mouseMove = DirectX::XMFLOAT2((float)cursorPos.x - m_old_position.x, (float)cursorPos.y - m_old_position.y);

	m_old_position = cursorPos;
	// カメラ情報
	DirectX::XMFLOAT3 front = GetFront();
	DirectX::XMFLOAT3 side = GetRight();
	DirectX::XMFLOAT3 up(0.0f, 1.0f, 0.0f);
	DirectX::XMFLOAT3 look = GetLook();
	camera_infomation.vCamFront = DirectX::XMLoadFloat3(&front);
	camera_infomation.vCamSide = DirectX::XMLoadFloat3(&side);
	camera_infomation.vCamPos = DirectX::XMLoadFloat3(&m_position);
	camera_infomation.vCamLook = DirectX::XMLoadFloat3(&look);
	camera_infomation.vCamUp = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(camera_infomation.vCamFront, camera_infomation.vCamSide));

	switch (m_state)
	{
	case CAM_DCC_ORBIT:		UpdateOrbit(camera_infomation);	break;
	case CAM_DCC_TRACK:		UpdateTrack(camera_infomation);	break;
	case CAM_DCC_DOLLY:		UpdateDolly(camera_infomation);	break;
	case CAM_DCC_FLIGHT:	UpdateFlight(camera_infomation);	break;
	}
}

void CameraDccSystem::UpdateState()
{
	CameraDCCKind prev = (CameraDCCKind)m_state;
	if (IsKeyPress(VK_MENU))
	{
		m_state = CAM_DCC_NONE;
		if (IsKeyPress(VK_LBUTTON)) m_state = CAM_DCC_ORBIT;
		if (IsKeyPress(VK_MBUTTON)) m_state = CAM_DCC_TRACK;
		if (IsKeyPress(VK_RBUTTON)) m_state = CAM_DCC_DOLLY;
	}
	else if (IsKeyPress(VK_RBUTTON))
	{
		m_state = CAM_DCC_FLIGHT;
	}
	else
	{
		m_state = CAM_DCC_NONE;
	}
	if (prev != m_state)
	{
		GetCursorPos(&m_old_position);
	}
}

void CameraDccSystem::UpdateOrbit(CameraInfomation& cameraInfomation)
{
	// マウスの移動量 / 画面サイズ の比率から、画面全体でどれだけ回転するか指定する
	float angleX = 360.0f * cameraInfomation.mouseMove.x / 1280.0f;
	float angleY = 180.0f * cameraInfomation.mouseMove.y / 720.0f;

	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		DirectX::XMVectorSet(0, 1, 0, 0), DirectX::XMConvertToRadians(angleX)
	);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	DirectX::XMVECTOR vAxisX = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	vAxisX = DirectX::XMVector3Rotate(vAxisX, qRotate);
	quat = DirectX::XMQuaternionRotationAxis(vAxisX, DirectX::XMConvertToRadians(angleY));
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	DirectX::XMStoreFloat4(&m_quaternion, qRotate);

	// 注視点からカメラの後方へフォーカス距離だけ移動させる
	DirectX::XMFLOAT3 dir = GetFront();
	DirectX::XMVECTOR vDir = DirectX::XMLoadFloat3(&dir);
	vDir = DirectX::XMVectorScale(vDir, -GetFocus());
	DirectX::XMVECTOR vPos = DirectX::XMVectorAdd(cameraInfomation.vCamLook, vDir);
	DirectX::XMStoreFloat3(&m_position, vPos);
}

void CameraDccSystem::UpdateTrack(CameraInfomation& cameraInfomation)
{
	float fClip = GetFar();

	// 高さA、底辺Bとする三角形について tanΘ = A / Bが成り立つ
	// 上記式をもとに割り出した遠景の高さを、移動量 / 画面サイズ の比率から、移動量として求める
	float width = GetFovy();
	float farScreenHeight = tanf(width * 0.5f) * fClip;
	float screenRateW = cameraInfomation.mouseMove.x / 640.0f;
	float screenRateH = cameraInfomation.mouseMove.y / 360.0f;
	float farMoveX = -farScreenHeight * screenRateW * GetAspect();
	float farMoveY = farScreenHeight * screenRateH;

	// カメラの姿勢をもとに移動
	float rate = GetFocus() / fClip;
	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(cameraInfomation.vCamSide, farMoveX * rate));
	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(cameraInfomation.vCamUp, farMoveY * rate));
	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(cameraInfomation.vCamPos, vCamMove));
}

void CameraDccSystem::UpdateDolly(CameraInfomation& cameraInfomation)
{
	float focus = GetFocus();
	float fClip = GetFar();
	float nClip = GetNear();

	// フォーカス位置とクリップ面の位置に応じて補正移動量を計算
	float clipDistance = fClip - nClip;
	float rate = (focus - nClip) / clipDistance;

	// 移動量
	float move = rate * (cameraInfomation.mouseMove.x + cameraInfomation.mouseMove.y) * fClip * 0.01f;
	focus = std::min(fClip, std::max(nClip, focus - move));

	// カメラ位置更新
	DirectX::XMVECTOR vMove = DirectX::XMVectorScale(cameraInfomation.vCamFront, -focus);
	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(cameraInfomation.vCamLook, vMove));
	m_focus = focus;
}

void CameraDccSystem::UpdateFlight(CameraInfomation& cameraInfomation)
{
	// マウスの移動量 / 画面サイズ の比率から、画面全体でどれだけ回転するか指定する。
	float angleX = 360.0f * cameraInfomation.mouseMove.x / 1280.0f;
	float angleY = 180.0f * cameraInfomation.mouseMove.y / 720.0f;

	// 横回転
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quaternion);
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
		cameraInfomation.vCamUp, DirectX::XMConvertToRadians(angleX)
	);
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// 縦回転
	DirectX::XMVECTOR vAxis = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	vAxis = DirectX::XMVector3Rotate(vAxis, qRotate);
	quat = DirectX::XMQuaternionRotationAxis(vAxis, DirectX::XMConvertToRadians(angleY));
	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);

	// 回転の更新
	DirectX::XMStoreFloat4(&m_quaternion, qRotate);

	// 軸の取得
	DirectX::XMFLOAT3 front = GetFront();
	DirectX::XMFLOAT3 side = GetRight();
	cameraInfomation.vCamFront = DirectX::XMLoadFloat3(&front);
	cameraInfomation.vCamSide = DirectX::XMLoadFloat3(&side);

	// キー入力で移動
	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
	if (IsKeyPress('W')) vCamMove = DirectX::XMVectorAdd(vCamMove, cameraInfomation.vCamFront);
	if (IsKeyPress('S')) vCamMove = DirectX::XMVectorSubtract(vCamMove, cameraInfomation.vCamFront);
	if (IsKeyPress('A')) vCamMove = DirectX::XMVectorSubtract(vCamMove, cameraInfomation.vCamSide);
	if (IsKeyPress('D')) vCamMove = DirectX::XMVectorAdd(vCamMove, cameraInfomation.vCamSide);
	if (IsKeyPress('Q')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	if (IsKeyPress('E')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f));
	vCamMove = DirectX::XMVectorScale(vCamMove, GetFar() * 0.02f);

	// 更新
	DirectX::XMVECTOR vCamPos = DirectX::XMVectorAdd(cameraInfomation.vCamPos, vCamMove);
	DirectX::XMStoreFloat3(&m_position, vCamPos);
}
}// namespace HaraProject::Framework

