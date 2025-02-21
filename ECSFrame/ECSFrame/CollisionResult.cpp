#include "CollisionResult.h"

namespace HaraProject::Framework
{

/**
* @brief コンストラクタ
*/
CollisionResult::CollisionResult()
	:isCollided(false), collisionCount(0) 
{}

/**
* @brief コピーコンストラクタ
* @param[in] base Transformが入った基底クラスポインタ
*/
CollisionResult::CollisionResult(ComponentDataBase * base)
{
	auto* value = dynamic_cast<CollisionResult*>(base);
	for (int i = 0; i < MAX_COLLISIONS; ++i)
	{
		collidedDatas[i] = value->collidedDatas[i];
	}
	collisionCount = value->collisionCount;
}

/**
* @brief 衝突情報をクリア
*/
void CollisionResult::Clear()
{
	for (int i = 0; i < MAX_COLLISIONS; ++i)
	{
		collidedDatas[i] = CollisionInfo();
	}
	collisionCount = 0;
	isCollided = false;
}

/**
* @brief 衝突情報を追加
*/
void CollisionResult::AddCollidedEntity(uint32_t id, DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 normal)
{
	isCollided = true;
	if (collisionCount < MAX_COLLISIONS)
	{
		collidedDatas[collisionCount] = CollisionInfo(id, point, normal);
		++collisionCount;
	}
}

}