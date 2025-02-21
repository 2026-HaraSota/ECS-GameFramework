#include "CollisionResult.h"

namespace HaraProject::Framework
{

/**
* @brief �R���X�g���N�^
*/
CollisionResult::CollisionResult()
	:isCollided(false), collisionCount(0) 
{}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base Transform�����������N���X�|�C���^
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
* @brief �Փˏ����N���A
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
* @brief �Փˏ���ǉ�
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