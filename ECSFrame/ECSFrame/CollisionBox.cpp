#include "CollisionBox.h"

namespace HaraProject::Framework
{

/**
* @brief コピーコンストラクタ
* @param[in] base Transformが入った基底クラスポインタ
*/
CollisionBox::CollisionBox(ComponentDataBase* base)
{
	CollisionBox* value = dynamic_cast<CollisionBox*>(base);
	center = value->center;
	size = value->size;
#if _DEBUG
	isSelect = value->isSelect;
#endif
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void CollisionBox::SetDataFromJson(nlohmann::json jsonData)
{
	center = DirectX::XMFLOAT3(
		jsonData[COLLISION_BOX_CENTER_NAME][0],
		jsonData[COLLISION_BOX_CENTER_NAME][1],
		jsonData[COLLISION_BOX_CENTER_NAME][2]
	);
	size = DirectX::XMFLOAT3(
		jsonData[COLLISION_BOX_SIZE_NAME][0],
		jsonData[COLLISION_BOX_SIZE_NAME][1],
		jsonData[COLLISION_BOX_SIZE_NAME][2]
	);
}

}