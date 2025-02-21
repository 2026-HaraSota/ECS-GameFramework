#include "CollisionCircle2D.h"

namespace HaraProject::Framework
{

/**
* @brief コピーコンストラクタ
* @param[in] base Transformが入った基底クラスポインタ
*/
CollisionCircle2D::CollisionCircle2D(ComponentDataBase* base)
{
	CollisionCircle2D* value = dynamic_cast<CollisionCircle2D*>(base);
	center = value->center;
	radius = value->radius;
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void CollisionCircle2D::SetDataFromJson(nlohmann::json jsonData)
{
	center = DirectX::XMFLOAT2(
		jsonData[COLLISION_CIRCLE_2D_CENTER_NAME][0],
		jsonData[COLLISION_CIRCLE_2D_CENTER_NAME][1]
	);
	radius = jsonData[COLLISION_CIRCLE_2D_RADIUS_NAME];
}

}