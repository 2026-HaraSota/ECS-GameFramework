/**
* @file   Velocity.h
* @brief  ���x�R���|�[�l���g�f�[�^��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _VELOCITY_H_
#define _VELOCITY_H_

#include <DirectXMath.h>

#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

#include "MathUtil.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework{
/**
* @brief ���x�R���|�[�l���g�f�[�^
*/
class Velocity : public ComponentDataBase
{
public:
	/**
	* @brief �f�[�^��
	*/
	static constexpr const char* VELOCITY_NAME = "Velocity";
	static constexpr const char* VELOCITY_LINEAR_VELOCITY_NAME = "linearVelocity";
	static constexpr const char* VELOCITY_ANGULAR_VELOCITY_NAME = "angularVelocity";

	/**
	* @brief �ړ����x
	*/
	DirectX::XMFLOAT3 linearVelocity;

	/**
	* @brief ��]���x
	*/
	DirectX::XMFLOAT3 angularVelocity;

	/**
	* @brief �R���X�g���N�^
	*/
	Velocity();

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] base �R�s�[����Velocity
	*/
	Velocity(ComponentDataBase* base);

	/**
	* @brief �f�X�g���N�^
	*/
	~Velocity() = default;

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

		jsonData[VELOCITY_NAME][VELOCITY_LINEAR_VELOCITY_NAME] = { linearVelocity.x,linearVelocity.y,linearVelocity.z };
		jsonData[VELOCITY_NAME][VELOCITY_ANGULAR_VELOCITY_NAME] = { angularVelocity.x,angularVelocity.y,angularVelocity.z };

		return jsonData;
	}

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(VELOCITY_NAME, "id");
		transform_gui->AddChildren(
			guiManager->CreateGuiInputDragFloat3(VELOCITY_LINEAR_VELOCITY_NAME, "id", &linearVelocity, 0.1f),
			guiManager->CreateGuiInputDragFloat3(VELOCITY_ANGULAR_VELOCITY_NAME, "id", &angularVelocity, 0.1f)
		);
		return transform_gui;
	}
#endif // _DEBUG
};

}// !namespace HaraProject::Framework

#endif // !_VELOCITY_H_