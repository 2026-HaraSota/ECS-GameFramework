#include "CollisionCircle2D.h"

namespace HaraProject::Framework
{

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base Transform�����������N���X�|�C���^
*/
CollisionCircle2D::CollisionCircle2D(ComponentDataBase* base)
{
	CollisionCircle2D* value = dynamic_cast<CollisionCircle2D*>(base);
	center = value->center;
	radius = value->radius;
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
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