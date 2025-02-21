#include "Velocity.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
Velocity::Velocity()
	: linearVelocity(0.0f,0.0f,0.0f)
	, angularVelocity(0.0f,0.0f,0.0f)
{
}

/**
* @brief コピーコンストラクタ
* @param[in] base Velocityが入った基底クラスポインタ
*/
Velocity::Velocity(ComponentDataBase* base)
{
	auto* value = dynamic_cast<Velocity*>(base);
	linearVelocity = value->linearVelocity;
	angularVelocity = value->angularVelocity;
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void Velocity::SetDataFromJson(nlohmann::json jsonData)
{
	linearVelocity = DirectX::XMFLOAT3(
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][0],
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][1],
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][2]
	);
	angularVelocity = DirectX::XMFLOAT3(
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][0],
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][1],
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][2]
	);
}
}//!HaraProject::Framework