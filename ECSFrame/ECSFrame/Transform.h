/**
* @file   Transform.h
* @brief  �ʒu�A��]�A�g�k�R���|�[�l���g�f�[�^��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <DirectXMath.h>
#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputDragFloat3.h"
#endif // _DEBUG

#include "MathUtil.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

/**
* @brief �ʒu�A��]�A�g�k�R���|�[�l���g�f�[�^
*/
class Transform : public ComponentDataBase {
public:
    /**
    * @brief �f�[�^��
    */
    static constexpr const char* TRANSFORM_NAME = "Transform";
    static constexpr const char* TRANSFORM_POSITION_NAME = "position";
    static constexpr const char* TRANSFORM_ROTATION_NAME = "rotation";
    static constexpr const char* TRANSFORM_SCALE_NAME = "scale";

    /**
    * @brief �ʒu���W
    */
    DirectX::XMFLOAT3 position;

    /**
    * @brief ��]
    */
    DirectX::XMFLOAT3 rotation;

    /**
    * @brief �g�k
    */
    DirectX::XMFLOAT3 scale;

    /**
    * @brief �R���X�g���N�^
    */
    Transform();

    /**
    * @brief �R�s�[�R���X�g���N�^
    * @param[in] base Transform�����������N���X�|�C���^
    */
    Transform(ComponentDataBase* base);

    /**
    * @brief �f�X�g���N�^
    */
    ~Transform() = default;

    /**
    * @brief Json�f�[�^����l��ݒ肷��
    * @param[in] json json�I�u�W�F�N�g
    */
    void SetDataFromJson(nlohmann::json jsonData) override;

    /**
    * @brief ���[���h�ϊ��s����쐬
    */
    DirectX::XMFLOAT4X4& CaluculateWorldMatrix();

    /**
    * @brief == �I�[�o�[���[�h
    */
    bool operator==(const Transform& other) const;

    /**
    * @brief != �I�[�o�[���[�h
    */
    bool operator!=(const Transform& other) const;

#ifdef _DEBUG
    /**
    * @brief ���݂̒l��Json�f�[�^�ɕϊ�����
    */
    nlohmann::json WriteDataToJson() override
    {
        nlohmann::json jsonData;

        jsonData[TRANSFORM_NAME][TRANSFORM_POSITION_NAME] = { position.x, position.y, position.z };
        jsonData[TRANSFORM_NAME][TRANSFORM_ROTATION_NAME] = { rotation.x, rotation.y, rotation.z };
        jsonData[TRANSFORM_NAME][TRANSFORM_SCALE_NAME] = { scale.x, scale.y, scale.z };

        return jsonData;
    }

    /**
    * @brief �C���X�y�N�^�\�\���쐬
    */
    GuiItemBase* CreateDetailContent(GuiManager* guiManager) override
    {
        GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(TRANSFORM_NAME, "id");
        transform_gui->AddChildren(
            guiManager->CreateGuiInputDragFloat3(TRANSFORM_POSITION_NAME, "id", &position, 0.1f),
            guiManager->CreateGuiInputDragFloat3(TRANSFORM_ROTATION_NAME, "id", &rotation, 0.1f),
            guiManager->CreateGuiInputDragFloat3(TRANSFORM_SCALE_NAME, "id", &scale, 0.1f));
        return transform_gui;
    }
#endif // _DEBUG
};

} // namespace HaraProject::Framework

#endif // !_TRANSFORM_H_
