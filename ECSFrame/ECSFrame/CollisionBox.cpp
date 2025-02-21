#include "CollisionBox.h"

namespace HaraProject::Framework
{

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base Transform�����������N���X�|�C���^
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
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
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