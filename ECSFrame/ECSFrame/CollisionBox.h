/**
* @file   Transform.h
* @brief�@�����蔻��p�{�b�N�X
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COLLISION_BOX_H_
#define _COLLISION_BOX_H_

#include <DirectXMath.h>

#include "ComponentDataBase.h"

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

namespace HaraProject::Framework
{

class CollisionBox : public ComponentDataBase
{
public:
	/**
	* @brief �R���|�[�l���g��"CollisionjBox"
	*/
	static constexpr const char* COLLISION_BOX_NAME = "CollisionBox";

	/**
	* @brief �e�v���p�e�B�L�^�p�̖��O
	*/
	static constexpr const char* COLLISION_BOX_CENTER_NAME = "center";
	static constexpr const char* COLLISION_BOX_SIZE_NAME = "size";

	/**
	* @brief �f�t�H���g�R���X�g���N�^
	*/
	CollisionBox() = default;

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] base Transform�����������N���X�|�C���^
	*/
	CollisionBox(ComponentDataBase* base);

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	void SetDataFromJson(nlohmann::json jsonData)override;

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[COLLISION_BOX_NAME][COLLISION_BOX_CENTER_NAME] = { center.x,center.y,center.z };
		jsonData[COLLISION_BOX_NAME][COLLISION_BOX_SIZE_NAME] = { size.x,size.y,size.z };

		return jsonData;
	}

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(COLLISION_BOX_NAME, "id");
		transform_gui->AddChildren(
			guiManager->CreateGuiInputDragFloat3(COLLISION_BOX_CENTER_NAME, "id", &center, 0.1f),
			guiManager->CreateGuiInputDragFloat3(COLLISION_BOX_SIZE_NAME, "id", &size, 0.1f)
		);
		return transform_gui;
	};
#endif // _DEBUG

	/**
	* @brief ���[�J����Ԃł̒����ʒu
	*/
	DirectX::XMFLOAT3 center;

	/**
	* @brief �T�C�Y
	*/
	DirectX::XMFLOAT3 size;

#if _DEBUG
	/**
	* @brief �I������Ă��邩
	*/
	bool isSelect;
#endif
};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_BOX_H_