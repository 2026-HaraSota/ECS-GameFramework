/**
* @file   CollisionResult.h
* @brief�@�����蔻�茋��
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COLLISION_RESULT_H_
#define _COLLISION_RESULT_H_

#include <DirectXMath.h>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

class CollisionResult : public ComponentDataBase
{
public:
	/**
	* @brief �Փˏ��
	*/
	struct CollisionInfo
	{
		/**
		* @brief �Փ˂����G���e�B�e�B��ID
		*/
		uint32_t entityId;

		/**
		* @brief �Փ˂��N�������W
		*/
		DirectX::XMFLOAT3 collisionPoint;

		/**
		* @brief �Փ˕���
		*/
		DirectX::XMFLOAT3 collisionNormal;
	};

	/**
	* @brief �R���|�[�l���g��"CollisionResult"
	*/
	static constexpr const char* COLLISION_RESULT_NAME = "CollisionResult";

	/**
	* @brief �e�v���p�e�B�L�^�p�̖��O
	*/
	static constexpr const char* COLLISION_RESULT_COLLIDED_ENTITIES_NAME = "collidedEntities";
	static constexpr const char* COLLISION_RESULT_COLLISION_COUNT_NAME = "collisionCount";
	static constexpr const char* COLLIDED_ENTITY_ID = "entityId";
	static constexpr const char* COLLIDED_COLLISION_POINT = "collisionPoint";
	static constexpr const char* COLLIDED_COLLISION_NORMAL = "collisionNormal";

	/**
	* @brief �Փˏ���ێ��ł���ő吔
	*/
	static constexpr uint8_t MAX_COLLISIONS = 8;

	/**
	* @brief �R���X�g���N�^
	*/
	CollisionResult();

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] base Transform�����������N���X�|�C���^
	*/
	CollisionResult(ComponentDataBase* base);

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	void SetDataFromJson(nlohmann::json jsonData)override{}

	/**
	* @brief �Փˏ����N���A
	*/
	void Clear();

	/**
	* @brief �Փˏ���ǉ�
	*/
	void AddCollidedEntity(uint32_t id, DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 normal);

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	nlohmann::json WriteDataToJson()override 
	{ 
		nlohmann::json def{}; 
		def[COLLISION_RESULT_NAME] = "no save"; 
		return def; 
	}

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* collision_result_name = guiManager->CreateGuiTreeNode(COLLISION_RESULT_NAME, "id");
		collision_result_name->AddChild(guiManager->CreateGuiText(COLLIDED_ENTITY_ID));

		return collision_result_name;
	};
#endif // _DEBUG

	/**
	* @brief �Փˏ��
	*/
	CollisionInfo collidedDatas[MAX_COLLISIONS]{};

	/**
	* @brief �Փ˃G���e�B�e�B��
	*/
	uint32_t collisionCount;

	/**
	* @brief �Փ˂���������
	*/
	bool isCollided;
};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_RESULT_H_